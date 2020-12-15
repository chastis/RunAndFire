#pragma once
#include <Engine/EventSystem/EventChannel.hpp>
#include <Engine/EventSystem/Event.hpp>


class Entity;
class BaseComponent;

class GameEventChannel : public EventChannelSingleton<GameEventChannel> {};

namespace GameEvents
{
    class TakeDamageEvent : public Event
    {
    public:
        DECLARE_DYNAMIC_TYPE(TakeDamageEvent, Event)
        float damage = 0.f;
        Entity* dealer = nullptr;
    };
}
