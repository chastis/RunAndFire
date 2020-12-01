#include <Game/Managers/GameManager.hpp>
#include <Engine/InputSystem/InputEvent.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/Factories/DynamicTypeFactory.hpp>
#include <Engine/Managers/FileManager.hpp>
#include <Engine/Managers/EntityManager.hpp>
#include <Engine/InputSystem/InputManager.hpp>

void GameManager_Impl::Initialize()
{
    DynamicTypeFactory::CreateInstance();
    FileManager::CreateInstance();
    GameManager::CreateInstance();
    EntityManager::CreateInstance();
    InputManager::CreateInstance();

    FileManager::GetInstanceRef().SetWorkingDirectory(WORKING_DIRECTORY);
    InputManager::GetInstanceRef().Initialize("action_maps.xml");

    m_engineEventHandler.JoinChannel<EngineEventChannel>();
    m_engineEventHandler.ConnectHandler(this, &GameManager_Impl::OnInputEvent);
}

void GameManager_Impl::Destroy()
{
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
