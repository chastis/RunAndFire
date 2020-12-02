#include <Engine/InputSystem/InputManager.hpp>
#include <Engine/InputSystem/InputClient.hpp>
#include <Engine/InputSystem/InputEvent.hpp>
#include <Engine/Managers/FileManager.hpp>
#include <Utility/Debugging/Assert.hpp>

InputManager_Impl::InputManager_Impl()
{
    m_eventHandler.JoinChannel<InputSystemEventChannel>();
    m_eventHandler.ConnectHandler(this, &InputManager_Impl::OnInputSystemEvent);
}

InputManager_Impl::~InputManager_Impl()
{
    m_eventHandler.DisconnectAll();
    m_eventHandler.LeaveAll();
}

void InputManager_Impl::Initialize(const std::string& inputFilePath)
{
    auto& file_manager = FileManager::GetInstanceRef();
    auto action_maps_config = file_manager.OpenFile(inputFilePath);
    M42_ASSERT(action_maps_config.is_open(), "Failed to open action maps config file");

    pugi::xml_document actionMapsDoc;
    actionMapsDoc.load(action_maps_config);
    LoadActionMaps(actionMapsDoc);
}

void InputManager_Impl::PushActionMap(const std::string& actionMap)
{
    auto actionMapIt = m_actionMaps.find(actionMap);
    M42_ASSERT(actionMapIt != m_actionMaps.end(), "No such action map");
    m_actionMapStack.push_back(actionMapIt->second);
}

void InputManager_Impl::PopActionMap()
{
    M42_ASSERT(!m_actionMapStack.empty(), "Action Map Push/Pop mismatch");
    m_actionMapStack.pop_back();
}

void InputManager_Impl::AddListener(InputClient* client)
{
    m_clients.push_back(client);
}

void InputManager_Impl::RemoveListener(InputClient* client)
{
    auto listener = std::find(m_clients.begin(), m_clients.end(), client);
    if (listener != m_clients.end())
    {
        auto erased = m_clients.erase(listener);
    }
}

void InputManager_Impl::DispatchSignalToListeners(ActionSignal signal)
{
    for (auto listener : m_clients)
    {
        listener->HandleInput(signal);
    }
}

std::string InputManager_Impl::GetNativeInput(const ActionSignalInput& input)
{
    using namespace std::string_literals;
    std::string keyValue = "Unknown";
    if (input.value >= 0 && input.value < sf::Keyboard::Key::KeyCount)
    {
        keyValue = KeyValues[input.value];
    }
    return GetActionInputEventPrefix(input.type) + ":"s + keyValue;
}

void InputManager_Impl::OnInputSystemEvent(const InputSystemEvent& event)
{
    DispatchInput(event.m_input);
}

void InputManager_Impl::LoadActionMaps(const pugi::xml_document& file)
{
    M42_ASSERT(file.child("ActionMaps"), "Invalid XML document passed");
    for (auto actionMap : file.child("ActionMaps").children("ActionMap"))
    {
        ActionMap action_map;
        action_map.LoadFromXml(actionMap);
        m_actionMaps.insert({ action_map.GetName(), action_map });
    }
}

void InputManager_Impl::DispatchInput(const ActionSignalInput& input)
{
    for (auto head = m_actionMapStack.rbegin(); head != m_actionMapStack.rend(); ++head)
    {
        for (auto signal : head->GetSignals(GetNativeInput(input)))
        {
            DispatchSignalToListeners(signal);
        }
        // why we need this?
        if (!head->IsPassthrough()) break;
    }
}
