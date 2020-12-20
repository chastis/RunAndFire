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

void Engine::Initialize(sf::RenderTarget* renderTarget)
{
    m_renderTargetWeak = renderTarget;
    m_physicEngine.SetFramerate(1.f / 60.f);
    m_physicEngine.SetGravity(0, Const::G);

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

void Engine::ChangeGameMode(EGameMode newMode, const std::string& input)
{
    if (!input.empty())
    {
        InputManager::GetInstanceRef().PushActionMap(input);
    }
    auto scene = std::make_unique<Scene>();
    scene->Initialize(m_renderTargetWeak);
    m_scenes.push(std::move(scene));
}

void Engine::RequestChangeGameMode(EGameMode gameMode, const std::string& input, const std::string& map)
{
    RequestParam param;
    param.gameMode = gameMode;
    param.map = map;
    param.input = input;
    m_requestedData = param;
}

void Engine::Update(float deltaTime)
{
    if (m_requestedData.has_value())
    {
        ChangeGameMode(m_requestedData.value().gameMode, m_requestedData.value().input);
        if (m_requestedData.value().map != "" && GetCurrentScene())
        {
            GetCurrentScene()->InitFromPrototype(m_requestedData.value().map);
        }
        m_requestedData.reset();
    }
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

sf::RenderTarget* Engine::GetRenderTarget() const
{
    return m_renderTargetWeak;
}

void Engine::OnComponentCreatedEvent(EntityEvents::ComponentCreatedEvent& event)
{
    if (event.component->IsKindOf(PhysicBodyComponentBase::GetStaticType()))
    {
        auto physicComponent = static_cast<PhysicBodyComponentBase*>(event.component);
        physicComponent->BindToPhysicEngine(&m_physicEngine);
    }
}
