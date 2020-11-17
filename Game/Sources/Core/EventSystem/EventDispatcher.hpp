#pragma once

class Event;
class EventChannel;

namespace EventSystem
{
    void Broadcast(Event& event, EventChannel* channel);
}