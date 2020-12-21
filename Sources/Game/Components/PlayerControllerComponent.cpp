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
    m_eventHandler.ConnectHandler(this, &PlayerControllerComponent::OnPlayerCollisionStarted);
    m_eventHandler.ConnectHandler(this, &PlayerControllerComponent::OnPlayerCollisionStarted);
}

void PlayerControllerComponent::InitFromPrototypeSpecific()
{
    const auto& prototype = GetPrototype<PlayerControllerPrototype>();

    m_speed = prototype.GetSpeed();
    m_jumpForce = prototype.GetJumpForce();
}

void PlayerControllerComponent::Update(float deltaTime)
{
    UpdateMoving(deltaTime);
    UpdateTravelingTime(deltaTime);

    UpdateOutOfBounds();

    auto& engine = GameManager::GetInstanceRef().GetEngineInstanceRef();
    engine.GetCurrentScene()->UpdateViewport(GetOwnerRef().getPosition());
}

bool PlayerControllerComponent::HandleInput(const ActionSignal& signal)
{
    if (m_isTravelingTime)
    {
        return false;
    }
    if (signal == ActionSignal("player_attack"))
    {
        if (GetPlayingAnimationName() != "anim_attack")
        {
            ChangeAnimation("anim_attack");
            SetAnimationRepetition(1);
        }
    }
    else if (signal == ActionSignal("player_jump_start"))
    {
        if (CanJump())
        {
            Jump();
        }
        m_jumping = true;
    }
    else if (signal == ActionSignal("player_jump_stop"))
    {
        m_jumping = false;
    }
    else if (signal == ActionSignal("move_left"))
    {
        ChangeAnimation("anim_run");
        m_viewDirection = -1.f;
        m_direction += -1.f;
        SetPlayerFriction(0.f);
    }
    else if (signal == ActionSignal("move_right"))
    {
        ChangeAnimation("anim_run");
        m_viewDirection = 1.f;
        m_direction += 1.f;
        SetPlayerFriction(0.f);
    }
    else if (signal == ActionSignal("stop_move_left"))
    {
        ChangeAnimation("anim_idle");
        m_direction -= -1.f;
        SetPlayerFriction(m_friction);
    }
    else if (signal == ActionSignal("stop_move_right"))
    {
        ChangeAnimation("anim_idle");
        m_direction -= 1.f;
        SetPlayerFriction(m_friction);
    }
    else if (signal == ActionSignal("player_time_control"))
    {
        m_meshComponent->setColor(sf::Color::Blue);
        m_physicComponent->GetBody()->SetEnabled(false);
        m_isTravelingTime = true;
        auto& engine = GameManager::GetInstanceRef().GetEngineInstanceRef();
        engine.SetDeltaTimeModifier(2.f);
        ChangeAnimation("anim_idle");
        m_direction = 0.f;
        SetPlayerFriction(0.f);
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
    ControllerComponent::PostInitSpecific();
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

bool PlayerControllerComponent::CanJump() const
{
    float verticalSpeed = m_physicComponent->GetLinearVelocity().y;
    return m_isColliding && (std::abs(verticalSpeed) < 1e-6);
}

void PlayerControllerComponent::Jump()
{
    float force = m_physicComponent->GetMass() * m_jumpForce;
    m_physicComponent->ApplyImpulse(0, -force);
}

void PlayerControllerComponent::UpdateMoving(float deltaTime)
{
    auto velocity = m_physicComponent->GetLinearVelocity();
    velocity.x = m_speed.x * m_direction * deltaTime;

    if (velocity.y > 1e-6)
    {
        velocity.y += Const::G * (m_lowJumpMultiplier - 1) * deltaTime;
    }
    else if (velocity.y < -1e-6 && !m_jumping)
    {
        velocity.y += Const::G * (m_fallMultiplier - 1) * deltaTime;
    }

    m_physicComponent->SetLinearVelocity(velocity.x, velocity.y);
}

void PlayerControllerComponent::UpdateTravelingTime(float deltaTime)
{
    if (m_isTravelingTime)
    {
        m_timeTravelTime += deltaTime;
        if (m_timeTravelTime >= 2.f)
        {
            m_timeTravelTime = 0.f;
            m_physicComponent->GetBody()->SetEnabled(true);
            m_isTravelingTime = false;
            m_meshComponent->setColor(sf::Color::White);
            auto& engine = GameManager::GetInstanceRef().GetEngineInstanceRef();
            engine.SetDeltaTimeModifier(1.f);
        }
    }
}

void PlayerControllerComponent::UpdateOutOfBounds()
{
    if (GetOwnerRef().getPosition().y >= 1000.f)
    {
        auto& engine = GameManager::GetInstanceRef().GetEngineInstanceRef();
        engine.RequestChangeScene("Loose");
    }
}

void PlayerControllerComponent::OnPlayerCollisionStarted(EntityEvents::CollisionStartedEvent& event)
{
    volatile bool trueBool = true;
    m_isColliding = trueBool;
}

void PlayerControllerComponent::OnPlayerCollisionEnded(EntityEvents::CollisionEndedEvent& event)
{
    volatile bool falseBool = false;
    m_isColliding = falseBool;
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
