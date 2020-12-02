#pragma once

#include <Engine/EventSystem/EventChannel.hpp>
#include <Engine/EventSystem/Event.hpp>
#include <SFML/Graphics/Rect.hpp>

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
        DECLARE_DYNAMIC_TYPE(CollisionEntityEvent, EntityEvent)
        std::pair<Entity*, Entity*> collidedEntity;
        sf::FloatRect intersection;
    };
}