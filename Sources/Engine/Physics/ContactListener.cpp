#include <Engine/Physics/ContactListener.hpp>
#include <Engine/Entity/EntityEvents.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>

#include <Engine/Physics/Box2D/b2_contact.h>

void ContactListener::BeginContact(b2Contact* contact)
{
    auto entityA = (Entity*)(contact->GetFixtureA()->GetUserData().pointer);
    auto entityB = (Entity*)(contact->GetFixtureB()->GetUserData().pointer);

    {
        auto event = std::make_shared<EntityEvents::CollisionStartedEvent>();
        event->contacted_entity = entityB;
        event->contact = contact;
        EventSystem::Broadcast(std::move(event), entityA);
    }
    {
        auto event = std::make_shared<EntityEvents::CollisionStartedEvent>();
        event->contacted_entity = entityA;
        event->contact = contact;
        EventSystem::Broadcast(std::move(event), entityB);
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    auto entityA = (Entity*)(contact->GetFixtureA()->GetUserData().pointer);
    auto entityB = (Entity*)(contact->GetFixtureB()->GetUserData().pointer);

    {
        auto event = std::make_shared<EntityEvents::CollisionEndedEvent>();
        event->contacted_entity = entityB;
        event->contact = contact;
        EventSystem::Broadcast(std::move(event), entityA);
    }
    {
        auto event = std::make_shared<EntityEvents::CollisionEndedEvent>();
        event->contacted_entity = entityA;
        event->contact = contact;
        EventSystem::Broadcast(std::move(event), entityB);
    }
}
