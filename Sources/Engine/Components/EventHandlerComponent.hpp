#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/Prototypes/PhysicPrototype.hpp>

class Event;

class EventHandlerComponent : public BaseComponent, public IPrototypeable<PhysicPrototype>
{
    DECLARE_DYNAMIC_TYPE(EventHandlerComponent, BaseComponent)
public:
    void InitFromPrototype() override;
    void Update(float deltaTime) override;

    void DispatchEvent(Event& entityEvent);
};