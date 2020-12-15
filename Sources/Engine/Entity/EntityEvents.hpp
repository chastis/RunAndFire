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
        DECLARE_DYNAMIC_TYPE(EntityCreatedEvent, EntityEvent)
        Entity* entity = nullptr;
    };

    class ComponentCreatedEvent : public EntityEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(ComponentCreatedEvent, EntityEvent)
        BaseComponent* component = nullptr;
    };

    class CollisionStartedEvent : public EntityEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(CollisionStartedEvent, EntityEvent)
        Entity* contacted_entity = nullptr;
        b2Contact* contact = nullptr;
    };

    class CollisionEndedEvent : public EntityEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(CollisionEndedEvent, EntityEvent)
        Entity* contacted_entity = nullptr;
        b2Contact* contact = nullptr;
    };

    class AnimationNotifyEvent : public EntityEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(AnimationNotifyEvent, EntityEvent)
        std::string notify_name;
        std::string animation_name;
    };

    class AnimationEndedEvent : public EntityEvent
    {
    public:
        DECLARE_DYNAMIC_TYPE(AnimationEndedEvent, EntityEvent)
        std::string animation_name;
    };
}