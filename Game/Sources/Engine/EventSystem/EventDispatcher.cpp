#include <Engine/EventSystem/EventDispatcher.hpp>

#include <Engine/EventSystem/EventChannel.hpp>

void EventSystem::Broadcast(std::unique_ptr<Event> event, EventChannel* channel)
{
    if (event)
    {
        channel->DispatchEvent(*event);
    }
}
