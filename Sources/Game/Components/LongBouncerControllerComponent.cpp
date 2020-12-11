#include <Game/Components/LongBouncerControllerComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Game/Events/GameEvents.hpp>

LongBouncerControllerComponent::LongBouncerControllerComponent()
{
    m_eventHandler.ConnectHandler(this, &LongBouncerControllerComponent::OnTakeDamage);
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
