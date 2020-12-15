#include <Game/Components/LongBouncerControllerComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Game/Events/GameEvents.hpp>
#include "Engine/EventSystem/EventDispatcher.hpp"

LongBouncerControllerComponent::LongBouncerControllerComponent()
{
    m_eventHandler.ConnectHandler(this, &LongBouncerControllerComponent::OnTakeDamage);
    m_eventHandler.ConnectHandler(this, &LongBouncerControllerComponent::OnAnimationNotifyDamage);
}

void LongBouncerControllerComponent::Update(float deltaTime)
{
    if (m_alive)
    {
        const sf::Vector2f attackPoint = GetOwnerRef().getPosition() + sf::Vector2f(50.f * m_direction, 0.f);
        auto enemy = m_physicComponent->RayCastGetEntity(attackPoint, true);
        if (enemy && enemy->GetPrototype<EntityPrototype>().GetSID() == "PlayerPrototype")
        {
            if (GetPlayingAnimationName() != "long_bouncer_attack")
            {
                m_enemy = enemy;
                ChangeAnimation("long_bouncer_attack");
                SetAnimationRepetition(1);
            }
        }
        else if (GetPlayingAnimationName() != "long_bouncer_going")
        {
            ChangeAnimation("long_bouncer_going");
        }
        const sf::Vector2f tracePoint = GetOwnerRef().getPosition() + sf::Vector2f(0.f, 100.f);
        auto floor = m_physicComponent->RayCastGetEntity(tracePoint, true);
        if (!floor)
        {
            m_direction *= -1;
            SetMeshScale({m_direction, 1.f});
        }

        auto velocity = m_physicComponent->GetLinearVelocity();
        m_physicComponent->SetLinearVelocity(m_speed.x * m_direction * deltaTime, velocity.y);
    }
}

void LongBouncerControllerComponent::PostInitSpecific()
{
    m_physicComponent = GetOwnerRef().GetComponent<PhysicBodyComponent>();
    m_speed = sf::Vector2f(30.f, 0.f);
    m_physicComponent->SetGravityScale(0.f);
    m_direction = 1.f;
}

void LongBouncerControllerComponent::OnTakeDamage(GameEvents::TakeDamageEvent& gameEvent)
{
    m_alive = false;
    m_speed = {0.f, 0.f};
    m_physicComponent->SetGravityScale(1.f);
    auto meshComponent = GetOwnerRef().GetComponent<MeshComponent>();
    if (meshComponent)
    {
        meshComponent->setColor(sf::Color::Red);
    }
    SetAnimationRepetition(0);
}

void LongBouncerControllerComponent::OnAnimationNotifyDamage(EntityEvents::AnimationNotifyEvent& gameEvent)
{
    if (gameEvent.animation_name == "long_bouncer_attack" && gameEvent.notify_name == "HitNotify")
    {
        auto damageEvent = std::make_shared<GameEvents::TakeDamageEvent>();
        damageEvent->dealer = GetOwner();
        damageEvent->damage = 100.f;
        EventSystem::Broadcast(std::move(damageEvent), m_enemy);
    }
}
