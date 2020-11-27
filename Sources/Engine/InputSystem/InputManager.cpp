#include <Engine/InputSystem/InputManager.hpp>
#include <Engine/InputSystem/InputClient.hpp>
#include <Engine/InputSystem/InputEvent.hpp>
#include <Utility/Debugging/Assert.hpp>

std::map<std::string, ActionMap> InputManager::ms_actionMaps;

InputManager::InputManager()
{
    m_eventHandler.JoinChannel<InputSystemEventChannel>();
    m_eventHandler.ConnectHandler(this, &InputManager::OnInputSystemEvent);
}

InputManager::~InputManager()
{
    m_eventHandler.DisconnectAll();
    m_eventHandler.LeaveAll();
}

void InputManager::PushActionMap(const std::string& actionMap)
{
    auto actionMapIt = ms_actionMaps.find(actionMap);
    M42_ASSERT(actionMapIt != ms_actionMaps.end(), "No such action map");
    m_actionMapStack.push_back(actionMapIt->second);
}

void InputManager::PopActionMap()
{
    M42_ASSERT(!m_actionMapStack.empty(), "Action Map Push/Pop mismatch");
    m_actionMapStack.pop_back();
}

void InputManager::AddListener(InputClient* client)
{
    m_clients.push_back(client);
}

void InputManager::RemoveListener(InputClient* client)
{
    auto listener = std::find(m_clients.begin(), m_clients.end(), client);
    if (listener != m_clients.end())
    {
        auto erased = m_clients.erase(listener);
    }
}

void InputManager::DispatchSignalToListeners(ActionSignal signal)
{
    for (auto listener : m_clients)
    {
        listener->HandleInput(signal);
    }
}

std::string InputManager::GetNativeInput(const ActionSignalEvent& input)
{
    using namespace std::string_literals;
    return GetActionInputEventPrefix(input.type) + ":"s + std::to_string(input.value);
}

void InputManager::OnInputSystemEvent(const InputSystemEvent& event)
{
    DispatchInput(event.event);
}

void InputManager::LoadActionMaps(const pugi::xml_document& file)
{
    M42_ASSERT(file.child("ActionMaps"), "Invalid XML document passed");
    for (auto actionMap : file.child("ActionMaps").children("ActionMap"))
    {
        ActionMap action_map;
        action_map.LoadFromXml(actionMap);
        ms_actionMaps.insert({ action_map.GetName(), action_map });
    }
}

void InputManager::DispatchInput(const ActionSignalEvent& input)
{
    for (auto head = m_actionMapStack.rbegin(); head != m_actionMapStack.rend(); ++head)
    {
        for (auto signal : head->GetSignals(GetNativeInput(input)))
        {
            DispatchSignalToListeners(signal);
        }
        if (!(head->IsPassthrough())) break;
    }
}
