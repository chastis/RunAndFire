#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/Prototypes/PhysicPrototype.hpp>

class Event;

class EventHandlerComponent : public BaseComponent
{
    DECLARE_DYNAMIC_TYPE(EventHandlerComponent, BaseComponent)
public:
    void Update(float deltaTime) override;

    void DispatchEvent(Event& entityEvent);
};