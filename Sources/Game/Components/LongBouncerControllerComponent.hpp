#pragma once

#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/BaseComponent.hpp>

class PhysicBodyComponent;

namespace GameEvents
{
     class TakeDamageEvent;
}

class LongBouncerControllerComponent : public ControllerComponent
{
    DECLARE_DYNAMIC_TYPE(LongBouncerControllerComponent, ControllerComponent)
public:
    LongBouncerControllerComponent();
    void Update(float deltaTime) override;
private:
    void PostInitSpecific() override;
    void OnTakeDamage(GameEvents::TakeDamageEvent& gameEvent);
    void OnAnimationNotifyDamage(EntityEvents::AnimationNotifyEvent& gameEvent);

    PhysicBodyComponent* m_physicComponent = nullptr;
    sf::Vector2f m_speed;
    Entity* m_enemy = nullptr;
    float m_direction = 0.f;
    bool m_alive = true;
};
