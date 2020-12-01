#pragma once

#include <Engine/EventSystem/EventHandler.hpp>
#include <Engine/InputSystem/ActionMap.hpp>
#include <Engine/InputSystem/ActionInputEvent.hpp>
#include <Utility/Core/Singleton.hpp>
#include <Utility/XML/pugixml.hpp>

#include <vector>
#include <deque>
#include <map>


class InputClient;
class InputSystemEvent;

class InputManager_Impl
{
public:
    InputManager_Impl();
    ~InputManager_Impl();

    void Initialize(const std::string& inputFilePath);

    void LoadActionMaps(const pugi::xml_document& file);

    void DispatchInput(const ActionSignalInput& input);

    void PushActionMap(const std::string& actionMap);
    void PopActionMap();

private:
    friend class InputClient;

    void AddListener(InputClient* client);
    void RemoveListener(InputClient* client);

    void DispatchSignalToListeners(ActionSignal signal);
    std::string GetNativeInput(const ActionSignalInput& input);

    void OnInputSystemEvent(const InputSystemEvent& event);
    std::map<std::string, ActionMap> m_actionMaps;
    std::deque<ActionMap> m_actionMapStack;
    std::vector<InputClient*> m_clients;

    EventHandler m_eventHandler;
};

using InputManager = Singleton<InputManager_Impl>;