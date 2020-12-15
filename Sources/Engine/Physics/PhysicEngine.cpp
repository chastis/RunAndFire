#include <Engine/Physics/PhysicEngine.hpp>
#include <Engine/Physics/RayCasts.hpp>
#include <Utility/Debugging/Assert.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Static/Const.hpp>
#include <Engine/Components/MeshComponent.hpp>

#if defined(DEBUG)
#include <Engine/Debugging/EntityComponents_Debug.hpp>
#endif // DEBUG

PhysicEngine::PhysicEngine()
{
    m_world = new b2World(m_gravity);
    M42_ASSERT(m_world, "Failed to create b2World!");

    m_world->SetContactListener(&m_contactListener);
}

PhysicEngine::~PhysicEngine()
{
    delete m_world;
}

void PhysicEngine::SetFramerate(float framerate)
{
    m_framerate = framerate;
}

void PhysicEngine::SetGravity(float x, float y)
{
    m_gravity.x = x;
    m_gravity.y = y;

    m_world->SetGravity(m_gravity);
}

b2Body* PhysicEngine::CreateBody(const b2BodyDef& bodyDefinition)
{
    return m_world->CreateBody(&bodyDefinition);
}

void PhysicEngine::DestroyBody(b2Body* body)
{
    m_world->DestroyBody(body);
}

void PhysicEngine::Update(std::uint32_t velocityIterations, std::uint32_t positionIterations)
{
    m_world->Step(m_framerate, velocityIterations, positionIterations);
}

Entity* PhysicEngine::RayCastGetEntity(Entity* caster, sf::Vector2f start, sf::Vector2f finish) const
{
    if (!caster || !m_world)
    {
        M42_ASSERT(false, "there are some nullptr's right here");
        return nullptr;
    }
    EntityRayCastCallback callback(caster);

    const b2Vec2 b2start = {start.x / Const::PixelPerUnit, start.y /  Const::PixelPerUnit};
    const b2Vec2 b2finish = {finish.x / Const::PixelPerUnit, finish.y / Const::PixelPerUnit};
    m_world->RayCast(&callback, b2start, b2finish);

    return callback.m_data.entity;
}
