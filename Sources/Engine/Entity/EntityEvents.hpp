#pragma once

#include <Engine/EventSystem/EventChannel.hpp>
#include <Engine/EventSystem/Event.hpp>

class Entity;

class EntityEventChannel : public EventChannelSingleton<EntityEventChannel> {};

namespace EntityEvents
{
    class EntityEvent : public Event
    {
    public:
        DECLARE_DYNAMIC_TYPE(ApplicationEvent, Event)
    };

    class CollisionEntityEvent : public EntityEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(ApplicationEvent, Event)
        Entity* CollidedEntity;
    };
}