#include <Engine/InputSystem/InputClient.hpp>
#include <Engine/InputSystem/InputManager.hpp>
#include <Engine/GameManager.hpp>
#include <Engine/Engine.hpp>

InputClient::InputClient()
{
    auto& inputManager = GameManager::GetInstanceRef().GetEngineInstance()->GetPrimaryInputManagerRef();
    inputManager.AddListener(this);
}

InputClient::~InputClient()
{
    auto& inputManager = GameManager::GetInstanceRef().GetEngineInstance()->GetPrimaryInputManagerRef();
    inputManager.RemoveListener(this);
}
