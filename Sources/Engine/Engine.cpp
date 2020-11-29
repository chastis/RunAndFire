#include <Engine/Engine.hpp>
#include <Engine/InputSystem/InputClient.hpp>
#include <Engine/Managers/FileManager.hpp>
#include <Utility/Debugging/Assert.hpp>

#include <Engine/Factories/DynamicTypeFactory.hpp>

#if defined(DEBUG)
#include <Engine/Debugging/Engine_Debug.hpp>
#endif

Engine::Engine()
#if defined(DEBUG)
    : m_debug(*this)
#endif
{
}

Engine::~Engine()
{
}

void Engine::Initialize(const std::weak_ptr<sf::RenderTarget>& renderTarget)
{
    DynamicTypeFactory::CreateInstance();

    m_renderTargetWeak = renderTarget;
    InitializeInputManager();

#if defined(DEBUG)
    m_debug->Initialize();
#endif //DEBUG
}

void Engine::Shutdown()
{
#if defined(DEBUG)
    m_debug->Shutdown();
#endif //DEBUG

    DynamicTypeFactory::DestroyInstance();
}

void Engine::Update(float deltaTime)
{

#if defined(DEBUG)
    m_debug->Update(deltaTime);
#endif //DEBUG
}

InputManager& Engine::GetInputManagerRef()
{
    return m_inputManager;
}

void Engine::InitializeInputManager()
{
    auto& file_manager = FileManager::GetInstanceRef();
    auto action_maps_config = file_manager.OpenFile("action_maps.xml");
    M42_ASSERT(action_maps_config.is_open(), "Failed to open action maps config file");

    pugi::xml_document actionMapsDoc;
    actionMapsDoc.load(action_maps_config);
    InputManager::LoadActionMaps(actionMapsDoc);
}
