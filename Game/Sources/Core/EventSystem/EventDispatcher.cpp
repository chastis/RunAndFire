#include <Core/EventSystem/EventDispatcher.hpp>

#include <Core/EventSystem/EventChannel.hpp>

void EventSystem::Broadcast(std::unique_ptr<Event> event, EventChannel* channel)
{
    if (event)
    {
        channel->DispatchEvent(*event);
    }
}
