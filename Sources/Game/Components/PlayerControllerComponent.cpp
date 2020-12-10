#include <Game/Components/PlayerControllerComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Entity/Entity.hpp>

#include <Engine/Physics/Box2D/b2_fixture.h>

void PlayerControllerComponent::InitFromPrototype()
{
    const auto& prototype = GetPrototype();
 
    m_speed = prototype.GetSpeed();
    m_jumpForce = prototype.GetJumpForce();
}

void PlayerControllerComponent::Update(float deltaTime)
{
    auto velocity = m_physicComponent->GetLinearVelocity();
    m_physicComponent->SetLinearVelocity(m_speed.x * m_direction * deltaTime, velocity.y);
}

bool PlayerControllerComponent::HandleInput(const ActionSignal& signal)
{
    if (signal == ActionSignal("player_jump"))
    {
        Jump();
    }
    if (signal == ActionSignal("move_left"))
    {
        m_direction += -1.f;
        SetPlayerFriction(0.f);
    }
    if (signal == ActionSignal("move_right"))
    {
        m_direction += 1.f;
        SetPlayerFriction(0.f);
    }
    if (signal == ActionSignal("stop_move_left"))
    {
        m_direction -= -1.f;
        SetPlayerFriction(m_friction);
    }
    if (signal == ActionSignal("stop_move_right"))
    {
        m_direction -= 1.f;
        SetPlayerFriction(m_friction);
    }
    return false;
}

void PlayerControllerComponent::PostInitSpecific()
{
    m_physicComponent = GetOwnerRef().GetComponent<PhysicBodyComponent>();

    m_friction = m_physicComponent->GetFixtures()->GetFriction();
}

void PlayerControllerComponent::SetPlayerFriction(float friction)
{
    if (auto fixture = m_physicComponent->GetFixtures())
    {
        fixture->SetFriction(friction);
    }
}

void PlayerControllerComponent::Jump()
{
    float force = m_physicComponent->GetMass() * m_jumpForce;
    m_physicComponent->ApplyImpulse(0, -force);
}
