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
}

void FlyControllerComponent::PostInitSpecific()
{
    m_physicComponent = GetOwnerRef().GetComponent<PhysicBodyComponent>();
}

void FlyControllerComponent::OnTakeDamage(GameEvents::TakeDamageEvent& gameEvent)
{
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
