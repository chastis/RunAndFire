#include <Engine/Components/EventHandlerComponent.hpp>
#include <Engine/Entity/EntityEvents.hpp>
#include <Engine/Entity/Entity.hpp>

EventHandlerComponent::EventHandlerComponent()
{
    m_prototypeWrapper = std::move(std::make_unique<IPrototypeWrapper<EventHandlerPrototype>>());
}

void EventHandlerComponent::InitFromPrototypeSpecific()
{
    const auto& componentEventsInfo = GetPrototype<EventHandlerPrototype>().GetEventsInfo();
    for (const auto& eventInfo : componentEventsInfo)
    {
        for (const auto& eventId : eventInfo.second)
        {
            if (BaseComponent* component = GetOwnerRef().GetComponent(eventInfo.first))
            {
                component->ConnectEvent(eventId);
            }
        }
    }
}

void EventHandlerComponent::Update(float deltaTime)
{
}

void EventHandlerComponent::DispatchEvent(Event& entityEvent)
{
    m_channel.DispatchEvent(entityEvent);
}

void EventHandlerComponent::ConnectHandler(EventHandler& handler)
{
    handler.JoinChannel(&m_channel);
}
