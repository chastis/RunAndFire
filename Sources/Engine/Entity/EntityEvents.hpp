#pragma once

#include <Engine/EventSystem/EventChannel.hpp>
#include <Engine/EventSystem/Event.hpp>
#include <SFML/Graphics/Rect.hpp>

class Entity;
class BaseComponent;
class b2Contact;

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
        DECLARE_DYNAMIC_TYPE(EntityCreatedEvent, Event)
        Entity* entity = nullptr;
    };

    class ComponentCreatedEvent : public EntityEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(ComponentCreatedEvent, Event)
        BaseComponent* component = nullptr;
    };

    class CollisionStartedEvent : public EntityEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(CollisionStartedEvent, Event)
        Entity* contacted_entity = nullptr;
        b2Contact* contact = nullptr;
    };

    class CollisionEndedEvent : public EntityEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(CollisionEndedEvent, Event)
        Entity* contacted_entity = nullptr;
        b2Contact* contact = nullptr;
    };
}