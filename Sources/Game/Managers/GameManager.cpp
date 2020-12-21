#include <Game/Managers/GameManager.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/Factories/DynamicTypeFactory.hpp>
#include <Engine/Factories/ComponentFactory.hpp>
#include <Engine/Managers/EntityManager.hpp>
#include <Engine/Managers/AssetManager.hpp>
#include <Engine/InputSystem/InputEvent.hpp>
#include <Engine/InputSystem/InputManager.hpp>
#include <Engine/Prototypes/CollisionPrototype.hpp>
#include <Engine/Prototypes/EntityPrototype.hpp>
#include <Engine/Prototypes/PhysicBodyPrototype.hpp>
#include <Engine/Prototypes/MeshPrototype.hpp>
#include <Engine/Prototypes/EventHandlerPrototype.hpp>
#include <Engine/Prototypes/ScenePrototype.hpp>
#include <Game/Prototypes/PlayerControllerPrototype.hpp>
#include <Game/Prototypes/UITilePrototype.hpp>
#include <Game/Components/PlayerControllerComponent.hpp>
#include <Game/Components/ChestControllerComponent.hpp>
#include <Game/Components/LongBouncerControllerComponent.hpp>
#include <Game/Components/UITileComponent.hpp>
#include <Game/Components/FlyControllerComponent.hpp>

void GameManager_Impl::Initialize()
{
    DynamicTypeFactory::CreateInstance();
    FileManager::CreateInstance();
    GameManager::CreateInstance();
    EntityManager::CreateInstance();
    InputManager::CreateInstance();
    AssetManager::CreateInstance();

    FileManager::GetInstanceRef().SetWorkingDirectory(WORKING_DIRECTORY);
    InputManager::GetInstanceRef().Initialize("action_maps.xml");

    InitPrototypes<CollisionPrototypes>("Prototypes/collision_prototypes.xml");
    InitPrototypes<EntityPrototypes>("Prototypes/entity_prototypes.xml");
    InitPrototypes<PhysicBodyPrototypes>("Prototypes/physic_body_prototypes.xml");
    InitPrototypes<PlayerControllerPrototypes>("Prototypes/player_controller_prototypes.xml");
    InitPrototypes<MeshPrototypes>("Prototypes/mesh_prototypes.xml");
    InitPrototypes<EventHandlerPrototypes>("Prototypes/event_handler_prototypes.xml");
    InitPrototypes<ScenePrototypes>("Prototypes/scene_prototypes.xml");
    InitPrototypes<UITilePrototypes>("Prototypes/uitile_prototypes.xml");

    DynamicTypeFactory::GetInstanceRef().GetFactory<ComponentFactory>()->AddCustomType<PlayerControllerComponent>();
    DynamicTypeFactory::GetInstanceRef().GetFactory<ComponentFactory>()->AddCustomType<ChestControllerComponent>();
    DynamicTypeFactory::GetInstanceRef().GetFactory<ComponentFactory>()->AddCustomType<LongBouncerControllerComponent>();
    DynamicTypeFactory::GetInstanceRef().GetFactory<ComponentFactory>()->AddCustomType<UITileComponent>();
    DynamicTypeFactory::GetInstanceRef().GetFactory<ComponentFactory>()->AddCustomType<FlyControllerComponent>();

    m_engineEventHandler.JoinChannel<EngineEventChannel>();
    m_engineEventHandler.ConnectHandler(this, &GameManager_Impl::OnInputEvent);
}

void GameManager_Impl::Destroy()
{
    AssetManager::DestroyInstance();
    InputManager::DestroyInstance();
    EntityManager::DestroyInstance();
    FileManager::DestroyInstance();
    DynamicTypeFactory::DestroyInstance();
}

void GameManager_Impl::SetEngineInstance(Engine* instance)
{
    m_engineInstance = instance;
}

Engine& GameManager_Impl::GetEngineInstanceRef() const
{
    return *m_engineInstance;
}

void GameManager_Impl::OnInputEvent(EngineEvents::InputApplicationEvent& event)
{
    auto inputEvent = std::make_unique<InputSystemEvent>(event.event);
    EventSystem::Broadcast(std::move(inputEvent), InputSystemEventChannel::GetInstance());
}
