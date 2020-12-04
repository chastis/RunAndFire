#include <Engine/Physics/PhysicEngine.hpp>

#include <Utility/Debugging/Assert.hpp>

PhysicEngine::PhysicEngine()
{
    m_world = new b2World(m_gravity);
    M42_ASSERT(m_world, "Failed to create b2World!");
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
