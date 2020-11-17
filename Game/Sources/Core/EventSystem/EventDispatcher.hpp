#pragma once

#include <Core/EventSystem/Event.hpp>

#include <memory>

class Event;
class EventChannel;

namespace EventSystem
{
    void Broadcast(std::unique_ptr<Event> event, EventChannel* channel);
}