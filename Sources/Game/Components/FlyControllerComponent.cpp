#include <Game/Components/FlyControllerComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Game/Events/GameEvents.hpp>
#include "Engine/EventSystem/EventDispatcher.hpp"

FlyControllerComponent::FlyControllerComponent()
{
    m_eventHandler.ConnectHandler(this, &FlyControllerComponent::OnTakeDamage);
    m_eventHandler.ConnectHandler(this, &FlyControllerComponent::OnAnimationNotifyDamage);
}

void FlyControllerComponent::Update(float deltaTime)
{
    if (m_alive)
    {
        const auto velocity = m_physicComponent->GetLinearVelocity();
        m_physicComponent->SetLinearVelocity(velocity.x, 10.f * m_direction * deltaTime);
        m_movingTime += deltaTime;
        if (m_movingTime >= 2.f)
        {
            m_movingTime = 0.f;
            m_direction *= -1.f;
        }
    }
}

void FlyControllerComponent::PostInitSpecific()
{
    m_physicComponent = GetOwnerRef().GetComponent<PhysicBodyComponent>();
    m_physicComponent->SetGravityScale(0.f);
}

void FlyControllerComponent::OnTakeDamage(GameEvents::TakeDamageEvent& gameEvent)
{
    if (!m_alive)
    {
        return;
    }
    m_alive = false;
    m_physicComponent->SetGravityScale(1.f);
    m_physicComponent->GetBody()->SetType(b2BodyType::b2_staticBody);
    auto meshComponent = GetOwnerRef().GetComponent<MeshComponent>();
    if (meshComponent)
    {
        meshComponent->setColor(sf::Color::Red);
    }
    SetAnimationRepetition(0);
}

void FlyControllerComponent::OnAnimationNotifyDamage(EntityEvents::AnimationNotifyEvent& gameEvent)
{
    
}
