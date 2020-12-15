#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/Prototypes/EventHandlerPrototype.hpp>
#include <Engine/EventSystem/EventChannel.hpp>

class Event;

class EventHandlerComponent : public BaseComponent
{
    DECLARE_DYNAMIC_TYPE(EventHandlerComponent, BaseComponent)
public:
    EventHandlerComponent();

    void Update(float deltaTime) override;
    void DispatchEvent(Event& entityEvent);
    void ConnectHandler(EventHandler& handler);
private:
    void PostInitSpecific() override;
    EventChannel m_channel;
};