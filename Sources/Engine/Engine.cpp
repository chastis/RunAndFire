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
    m_physicEngine.SetGravity(0, 500);

    ChangeGameMode(EGameMode::Game);

#if defined(DEBUG)
    m_debug->Initialize();
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
        break;
    }
    case EGameMode::Menu: break;
    default: ;
    }
}

void Engine::Update(float deltaTime)
{
    m_physicEngine.Update();

    std::vector<Entity*> entities = EntityManager::GetInstanceRef().GetEntities();
    for (auto en : entities)
    {
        en->Update(deltaTime);
        if (const auto enMeshComp = en->GetComponent<MeshComponent>())
        {
            m_renderTargetWeak.lock()->draw(*enMeshComp, en->getTransform());
        }
    }
#if defined(DEBUG)
    m_debug->Update(deltaTime);
#endif //DEBUG
}

void Engine::OnComponentCreatedEvent(EntityEvents::ComponentCreatedEvent& event)
{
    if (event.component->IsKindOf(PhysicBodyComponent::GetStaticType()))
    {
        auto physicComponent = static_cast<PhysicBodyComponent*>(event.component);
        physicComponent->BindToPhysicEngine(&m_physicEngine);
    }
}
