#include <Engine/Components/EventHandlerComponent.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/EventSystem/EventChannel.hpp>
#include <Engine/Entity/Entity.hpp>

void EventSystem::Broadcast(std::shared_ptr<Event> event, EventChannel* channel)
{
    if (event && channel)
    {
        channel->DispatchEvent(*event);
    }
}

void EventSystem::Broadcast(std::shared_ptr<Event> event, Entity* entity)
{
    if (event && entity)
    {
        auto handlerComponent = entity->GetComponent<EventHandlerComponent>();
        if (handlerComponent)
        {
            handlerComponent->DispatchEvent(*event);   
        }
    }
}
