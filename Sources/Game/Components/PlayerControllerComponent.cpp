#include <Game/Components/PlayerControllerComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>

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
    auto meshComponent = GetOwnerRef().GetComponent<MeshComponent>();
    if (meshComponent)
    {
        meshComponent->ChangeAnimation("anim_idle");
    }
}

void PlayerControllerComponent::Jump()
{
    float force = m_physicComponent->GetMass() * m_jumpForce;
    m_physicComponent->ApplyImpulse(0, -force);
}
