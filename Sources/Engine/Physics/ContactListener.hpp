#pragma once

#include <Engine/Physics/Box2D/b2_world_callbacks.h>

class ContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
};
