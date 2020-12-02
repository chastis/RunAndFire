#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/Prototypes/EventHandlerPrototype.hpp>
#include <Engine/EventSystem/EventChannel.hpp>

class Event;

class EventHandlerComponent : public PrototypeableBaseComponent<EventHandlerPrototype>
{
    DECLARE_DYNAMIC_TYPE(EventHandlerComponent, PrototypeableBaseComponent<EventHandlerPrototype>)
public:
    void InitFromPrototype() override;
    void Update(float deltaTime) override;
    void DispatchEvent(Event& entityEvent);
    void ConnectHandler(EventHandler& handler);
private:
    EventChannel m_channel;
};