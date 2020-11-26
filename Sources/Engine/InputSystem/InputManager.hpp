#pragma once

#include <vector>

class InputClient;

class InputManager
{
public:
    InputManager() = default;

    //Dispatch(event) will look at current action map stack and dispatch events to all it`s listeners
    //AddListener(Client*) will add listener to list
    //PushActionMap(ActionMap) will push certain action map to action map stack
    //PopActionMap() will remove top action map from stack
    //RemoveListener(Client*) will remove listener from list (meant to be called from listener`s destructor)

private:
    friend class InputClient;

    void AddListener(InputClient* client);
    void RemoveListener(InputClient* client);
private:
    std::vector<InputClient*> m_clients;
};