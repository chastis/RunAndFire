#include <Game/Components/PlayerControllerComponent.hpp>
#include <Game/Events/GameEvents.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Physics/Box2D/box2d.h>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/Engine.hpp>
#include <Game/Managers/GameManager.hpp>

PlayerControllerComponent::PlayerControllerComponent()
{
    m_prototypeWrapper = std::move(std::make_unique<IPrototypeWrapper<PlayerControllerPrototype>>());
    m_eventHandler.ConnectHandler(this, &PlayerControllerComponent::OnAnimationNotify);
    m_eventHandler.ConnectHandler(this, &PlayerControllerComponent::OnTakeDamage);
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
    if (GetOwnerRef().getPosition().y >= 1000.f)
    {
        auto& engine = GameManager::GetInstanceRef().GetEngineInstanceRef();
        engine.RequestChangeScene("Loose");
    }
}

bool PlayerControllerComponent::HandleInput(const ActionSignal& signal)
{
    if (signal == ActionSignal("player_attack"))
    {
        if (GetPlayingAnimationName() != "anim_attack")
        {
            ChangeAnimation("anim_attack");
            SetAnimationRepetition(1);
        }
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
        SetPlayerFriction(0.f);
    }
    if (signal == ActionSignal("move_right"))
    {
        ChangeAnimation("anim_run");
        m_viewDirection = 1.f;
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

void PlayerControllerComponent::Attack()
{
    auto dealDamage = [&](const sf::Vector2f& attackPoint)
    {
        const auto enemy = m_physicComponent->RayCastGetEntity(attackPoint, true);
        if (enemy)
        {
            auto damageEvent = std::make_shared<GameEvents::TakeDamageEvent>();
            damageEvent->dealer = GetOwner();
            damageEvent->damage = 100.f;
            EventSystem::Broadcast(std::move(damageEvent), enemy);
            return true;
        }
        return false;
    };

    sf::Vector2f attackPoint = GetOwnerRef().getPosition() + sf::Vector2f(m_viewDirection, 0.f) * 42.f;
    if (!dealDamage(attackPoint))
    {
        if (!dealDamage(attackPoint + sf::Vector2f(0.f, 10.f)))
        {
            dealDamage(attackPoint + sf::Vector2f(0.f, -10.f));
        }
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

void PlayerControllerComponent::OnAnimationNotify(EntityEvents::AnimationNotifyEvent& event)
{
    if (event.animation_name == "anim_attack" && event.notify_name == "HitNotify")
    {
        Attack();
    }
}

void PlayerControllerComponent::OnTakeDamage(GameEvents::TakeDamageEvent& event)
{
    auto& engine = GameManager::GetInstanceRef().GetEngineInstanceRef();
    engine.RequestChangeScene("Loose");
}
