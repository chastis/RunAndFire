#pragma once

#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/BaseComponent.hpp>
#include <Engine/InputSystem/InputClient.hpp>
#include <Game/Prototypes/PlayerControllerPrototype.hpp>
#include <Engine/InputSystem/ActionMap.hpp>

class PhysicBodyComponent;

class PlayerControllerComponent : public PrototypeableControllerComponent<PlayerControllerPrototype>, public InputClient
{
    DECLARE_DYNAMIC_TYPE(PlayerControllerComponent, PrototypeableControllerComponent<PlayerControllerPrototype>)
public:
    void InitFromPrototype() override;
    void Update(float deltaTime) override;
    bool HandleInput(const ActionSignal& signal) override;
private:
    void PostInitSpecific() override;
    void SetPlayerFriction(float friction);

    void Jump();
private:
    sf::Vector2f m_speed;

    PhysicBodyComponent* m_physicComponent = nullptr;

    float m_direction = 0.f;
    float m_jumpForce = 0.f;
    float m_friction = 0.f;
};
