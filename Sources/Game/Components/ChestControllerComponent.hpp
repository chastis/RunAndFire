#pragma once

#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/BaseComponent.hpp>

namespace GameEvents
{
     class TakeDamageEvent;
}

class ChestControllerComponent : public ControllerComponent
{
    DECLARE_DYNAMIC_TYPE(ChestControllerComponent, ControllerComponent)
public:
    ChestControllerComponent();
private:
    void OnTakeDamage(GameEvents::TakeDamageEvent& gameEvent);
    void OnAnimationEnded(EntityEvents::AnimationEndedEvent& animationEvent);
};

