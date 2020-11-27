#pragma once

#include <Engine/EventSystem/EventHandler.hpp>
#include <Engine/InputSystem/ActionMap.hpp>
#include <Engine/InputSystem/ActionInputEvent.hpp>
#include <Utility/XML/pugixml.hpp>

#include <vector>
#include <deque>
#include <map>

class InputClient;
class InputSystemEvent;

class InputManager
{
public:
    InputManager();
    ~InputManager();

    static void LoadActionMaps(const pugi::xml_document& file);

    void DispatchInput(const ActionSignalEvent& input);

    void PushActionMap(const std::string& actionMap);
    void PopActionMap();

private:
    friend class InputClient;

    void AddListener(InputClient* client);
    void RemoveListener(InputClient* client);

    void DispatchSignalToListeners(ActionSignal signal);
    std::string GetNativeInput(const ActionSignalEvent& input);

    void OnInputSystemEvent(const InputSystemEvent& event);
private:
    static std::map<std::string, ActionMap> ms_actionMaps;
private:
    std::deque<ActionMap> m_actionMapStack;
    std::vector<InputClient*> m_clients;

    EventHandler m_eventHandler;
};