#include <Engine/Engine.hpp>
#include <Engine/InputSystem/InputManager.hpp>
#include <Engine/Factories/DynamicTypeFactory.hpp>
#include <Engine/Managers/EntityManager.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Entity/EntityEvents.hpp>
#include <Engine/Entity/Entity.hpp>

#if defined(DEBUG)
#include <Engine/Debugging/Engine_Debug.hpp>
#include <Engine/Debugging/Scene_Debug.hpp>
#endif

Engine::Engine()
#if defined(DEBUG)
    : m_debug(*this)
#endif
{
    m_eventHandler.JoinChannel<EntityEventChannel>();

    m_eventHandler.ConnectHandler(this, &Engine::OnComponentCreatedEvent);
}

Engine::~Engine()
{
    m_eventHandler.LeaveAll();
    m_eventHandler.DisconnectAll();
}

void Engine::Initialize(const std::weak_ptr<sf::RenderTarget>& renderTarget)
{
    m_renderTargetWeak = renderTarget;
    m_physicEngine.SetFramerate(1.f / 60.f);
    m_physicEngine.SetGravity(0, Const::G);

    ChangeGameMode(EGameMode::Game);

#if defined(DEBUG)
    m_debug->Initialize();
#endif //DEBUG
}

void Engine::Draw()
{
    m_scenes.top()->Draw();
#if defined(DEBUG)
    m_debug->Draw();
#endif //DEBUG
}

void Engine::Shutdown()
{
    EntityManager::GetInstanceRef().DeleteAllEntities();
#if defined(DEBUG)
    m_debug->Shutdown();
#endif //DEBUG
}

void Engine::ChangeGameMode(EGameMode newMode)
{
    switch (newMode)
    {
    case EGameMode::Game:
        {
            InputManager::GetInstanceRef().PushActionMap("game_input");
            auto scene = std::make_unique<Scene>();
            scene->Initialize(m_renderTargetWeak);
            m_scenes.push(std::move(scene));
        }
    case EGameMode::Menu: break;
    default: ;
    }
}

void Engine::Update(float deltaTime)
{
    m_physicEngine.Update();
    if (!m_scenes.empty())
    {
        m_scenes.top()->Update(deltaTime);
    }
#if defined(DEBUG)
    m_debug->Update(deltaTime);
#endif //DEBUG
}

Scene* Engine::GetCurrentScene()
{
    if (m_scenes.empty())
    {
        return nullptr;
    }
    return m_scenes.top().get();
}

void Engine::OnComponentCreatedEvent(EntityEvents::ComponentCreatedEvent& event)
{
    if (event.component->IsKindOf(PhysicBodyComponentBase::GetStaticType()))
    {
        auto physicComponent = static_cast<PhysicBodyComponentBase*>(event.component);
        physicComponent->BindToPhysicEngine(&m_physicEngine);
    }
}
