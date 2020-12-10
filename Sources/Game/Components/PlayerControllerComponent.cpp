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
    if (signal == ActionSignal("player_attack"))
    {
        Attack();
    }
    if (signal == ActionSignal("player_jump"))
    {
        Jump();
    }
    if (signal == ActionSignal("move_left"))
    {
        ChangeAnimation("anim_run");
        m_viewDirection = -1.f;
        m_direction += -1.f;
    }
    if (signal == ActionSignal("move_right"))
    {
        ChangeAnimation("anim_run");
        m_viewDirection = 1.f;
        m_direction += 1.f;
    }
    if (signal == ActionSignal("stop_move_left"))
    {
        ChangeAnimation("anim_idle");
        m_direction -= -1.f;
    }
    if (signal == ActionSignal("stop_move_right"))
    {
        ChangeAnimation("anim_idle");
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
    ChangeAnimation("anim_idle");
}

void PlayerControllerComponent::Attack()
{
    auto b = GetOwnerRef().getPosition();
    auto c = GetOwnerRef().getTransform().transformPoint(0.f, 0.f);
    auto d = GetOwnerRef().getPosition() - GetOwnerRef().getOrigin();
    sf::Vector2f attackPoint = GetOwnerRef().getPosition() + sf::Vector2f(m_viewDirection, 0.f) * 42.f;
    auto enemy = m_physicComponent->RayCastGetEntity(attackPoint);
    if (enemy)
    {
        std::cout << enemy->GetPrototype<EntityPrototype>().GetSID();
    }
}

void PlayerControllerComponent::Jump()
{
    float force = m_physicComponent->GetMass() * m_jumpForce;
    m_physicComponent->ApplyImpulse(0, -force);
}
