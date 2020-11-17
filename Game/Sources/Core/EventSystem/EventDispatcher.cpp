#include <Core/EventSystem/EventDispatcher.hpp>

#include <Core/EventSystem/EventChannel.hpp>

void EventSystem::Broadcast(Event& event, EventChannel* channel)
{
    channel->DispatchEvent(event);
}
