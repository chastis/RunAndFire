#pragma once

#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Entity/EntityEvents.hpp>
#include <Engine/InputSystem/InputClient.hpp>
#include <Engine/InputSystem/ActionMap.hpp>
#include <Game/Prototypes/PlayerControllerPrototype.hpp>

class PhysicBodyComponent;

class PlayerControllerComponent : public ControllerComponent, public InputClient
{
    DECLARE_DYNAMIC_TYPE(PlayerControllerComponent, ControllerComponent)
public:
    PlayerControllerComponent();

    void Update(float deltaTime) override;
    bool HandleInput(const ActionSignal& signal) override;
private:
    void InitFromPrototypeSpecific() override;
    void PostInitSpecific() override;
    void SetPlayerFriction(float friction);

    void Attack();
    void Jump();

    void OnPlayerCollisionStarted(EntityEvents::CollisionStartedEvent& event);
    void OnPlayerCollisionEnded(EntityEvents::CollisionEndedEvent& event);
    void OnAnimationNotify(EntityEvents::AnimationNotifyEvent& event);
private:

    PhysicBodyComponent* m_physicComponent = nullptr;

    sf::Vector2f m_speed;
    float m_direction = 0.f;
    float m_viewDirection = 1.f;
    float m_jumpForce = 0.f;
    float m_friction = 0.f;
};
