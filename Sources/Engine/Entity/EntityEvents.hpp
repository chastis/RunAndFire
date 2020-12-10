#pragma once

#include <Engine/EventSystem/EventChannel.hpp>
#include <Engine/EventSystem/Event.hpp>
#include <SFML/Graphics/Rect.hpp>

class Entity;
class BaseComponent;

class EntityEventChannel : public EventChannelSingleton<EntityEventChannel> {};

namespace EntityEvents
{
    class EntityEvent : public Event
    {
    public:
        DECLARE_DYNAMIC_TYPE(EntityEvent, Event)
    };

    class EntityCreatedEvent : public EntityEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(EntityCreatedEvent, EntityEvent)
        Entity* entity = nullptr;
    };

    class ComponentCreatedEvent : public EntityEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(ComponentCreatedEvent, EntityEvent)
        BaseComponent* component = nullptr;
    };
}