#include <Engine/InputSystem/InputClient.hpp>
#include <Engine/InputSystem/InputManager.hpp>
#include <Engine/Engine.hpp>

InputClient::InputClient()
{
    InputManager::GetInstanceRef().AddListener(this);
}

InputClient::~InputClient()
{
    InputManager::GetInstanceRef().RemoveListener(this);
}
