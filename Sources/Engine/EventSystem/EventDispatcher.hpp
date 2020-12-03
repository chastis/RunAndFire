#pragma once

#include <Engine/EventSystem/Event.hpp>

#include <memory>

class Event;
class EventChannel;
class Entity;

namespace EventSystem
{
    void Broadcast(std::shared_ptr<Event> event, EventChannel* channel);
    void Broadcast(std::shared_ptr<Event> event, Entity* entity);
}