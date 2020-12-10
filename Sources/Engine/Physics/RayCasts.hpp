#pragma once

#include <Engine/Physics/Box2D/box2d.h>
#include <SFML/System/Vector2.hpp>

class Entity;

struct EntityRayCastData
{
    Entity* entity = nullptr;
    sf::Vector2f point;
    sf::Vector2f normal;
    float fraction = 0.f;
};

class EntityRayCastCallback : public b2RayCastCallback
{
public:
    explicit EntityRayCastCallback(Entity* owner);
    ~EntityRayCastCallback() = default;
    float ReportFixture(b2Fixture* fixture, const b2Vec2& point,
        const b2Vec2& normal, float fraction) override;

    EntityRayCastData m_data;
private:
    Entity* m_owner;
};