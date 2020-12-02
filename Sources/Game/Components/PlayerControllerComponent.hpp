#pragma once

#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/BaseComponent.hpp>
#include <Engine/InputSystem/InputClient.hpp>
#include <Game/Prototypes/PlayerControllerPrototype.hpp>
#include <Engine/InputSystem/ActionMap.hpp>

class PlayerControllerComponent : public PrototypeableControllerComponent<PlayerControllerPrototype>, public InputClient
{
    DECLARE_DYNAMIC_TYPE(PlayerControllerComponent, PrototypeableControllerComponent<PlayerControllerPrototype>)
public:
    void InitFromPrototype() override;
    void Update(float deltaTime) override;
    bool HandleInput(const ActionSignal& signal) override;
protected:
    sf::Vector2f m_speed;
    sf::Vector2f m_direction;
};
