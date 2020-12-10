#include <Game/Components/PlayerControllerComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Entity/Entity.hpp>

void PlayerControllerComponent::InitFromPrototype()
{
    const auto& prototype = GetPrototype();
 
    m_speed = prototype.GetSpeed();
    m_jumpForce = prototype.GetJumpForce();
}

void PlayerControllerComponent::Update(float deltaTime)
{
    auto velocity = m_physicComponent->GetLinearVelocity();
    const auto delta = m_speed * m_direction * deltaTime;
    velocity.x = delta.x;
    m_physicComponent->SetLinearVelocity(velocity.x, velocity.y);
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
    }
    if (signal == ActionSignal("move_right"))
    {
        m_direction += 1.f;
    }
    if (signal == ActionSignal("stop_move_left"))
    {
        m_direction -= -1.f;
    }
    if (signal == ActionSignal("stop_move_right"))
    {
        m_direction -= 1.f;
    }
    return false;
}

void PlayerControllerComponent::PostInitSpecific()
{
    m_physicComponent = GetOwnerRef().GetComponent<PhysicBodyComponent>();
}

void PlayerControllerComponent::Jump()
{
    float force = m_physicComponent->GetMass() * m_jumpForce;
    m_physicComponent->ApplyImpulse(0, -force);
}
