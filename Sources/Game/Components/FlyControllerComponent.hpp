#pragma once

#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/BaseComponent.hpp>

class PhysicBodyComponent;

namespace GameEvents
{
     class TakeDamageEvent;
}

class FlyControllerComponent : public ControllerComponent
{
    DECLARE_DYNAMIC_TYPE(FlyControllerComponent, ControllerComponent)
public:
    FlyControllerComponent();
    void Update(float deltaTime) override;
private:
    void PostInitSpecific() override;
    void OnTakeDamage(GameEvents::TakeDamageEvent& gameEvent);
    void OnAnimationNotifyDamage(EntityEvents::AnimationNotifyEvent& gameEvent);

    PhysicBodyComponent* m_physicComponent = nullptr;
};
