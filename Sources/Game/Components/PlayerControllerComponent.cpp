#include <Game/Components/PlayerControllerComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Physics/Box2D/box2d.h>

PlayerControllerComponent::PlayerControllerComponent()
{
    m_prototypeWrapper = std::move(std::make_unique<IPrototypeWrapper<PlayerControllerPrototype>>());
}

void PlayerControllerComponent::InitFromPrototypeSpecific()
{
    const auto& prototype = GetPrototype<PlayerControllerPrototype>();
 
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
        ChangeAnimation("anim_run");
        m_direction += -1.f;
        SetPlayerFriction(0.f);
    }
    if (signal == ActionSignal("move_right"))
    {
        ChangeAnimation("anim_run");
        m_direction += 1.f;
        SetPlayerFriction(0.f);
    }
    if (signal == ActionSignal("stop_move_left"))
    {
        ChangeAnimation("anim_idle");
        m_direction -= -1.f;
        SetPlayerFriction(m_friction);
    }
    if (signal == ActionSignal("stop_move_right"))
    {
        ChangeAnimation("anim_idle");
        m_direction -= 1.f;
        SetPlayerFriction(m_friction);
    }

    if (m_direction > 0)
    {
        SetMeshScale(1.f, 1.f);
    }
    else if (m_direction < 0)
    {
        SetMeshScale(-1.f, 1.f);
    }

    return false;
}

void PlayerControllerComponent::PostInitSpecific()
{
    m_physicComponent = GetOwnerRef().GetComponent<PhysicBodyComponent>();
    m_friction = m_physicComponent->GetFixtures()->GetFriction();
    ChangeAnimation("anim_idle");
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

void PlayerControllerComponent::OnPlayerCollisionStarted(EntityEvents::CollisionStartedEvent& event)
{
}

void PlayerControllerComponent::OnPlayerCollisionEnded(EntityEvents::CollisionEndedEvent& event)
{
}
