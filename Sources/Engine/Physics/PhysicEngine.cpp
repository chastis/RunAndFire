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

Entity* PhysicEngine::RayCastGetEntity(Entity* caster, sf::Vector2f point) const
{
    if (!caster || !m_world)
    {
        M42_ASSERT(false, "there are some nullptr's right here");
        return nullptr;
    }
    EntityRayCastCallback callback(caster);
    const sf::Vector2f casterOriginPosition = caster->getPosition() - caster->getOrigin();
    sf::Vector2f meshStart = casterOriginPosition;
    point -= caster->getOrigin();
    if (const auto meshComponent = caster->GetKindOfComponent<MeshComponentBase>())
    {
        meshStart += meshComponent->getOrigin();
        point += meshComponent->getOrigin();
        //point  += meshComponent->getPosition() + meshComponent->getOrigin();
    }
    #if defined(DEBUG)
    if (!caster->GetComponent<DebugInfoComponent>())
    {
        caster->AddComponent<DebugInfoComponent>();   
    }
    if (auto debugComponent = caster->GetComponent<DebugInfoComponent>())
    {
        debugComponent->shape.setFillColor(sf::Color::Red);
        debugComponent->shape.setOutlineColor(sf::Color::Red);
        debugComponent->shape.setPointCount(3);
        debugComponent->shape.setPosition(0.f, 0.f);
        //debugComponent->shape.setPoint(0, meshStart - caster->getPosition());
        debugComponent->shape.setPoint(0, {0.f, 0.f});
        //debugComponent->shape.setPoint(1, point - caster->getPosition());
        debugComponent->shape.setPoint(1, point - casterOriginPosition);
        //debugComponent->shape.setPoint(2, meshStart - caster->getPosition() - sf::Vector2f(2.f, 2.f));
        debugComponent->shape.setPoint(2, - sf::Vector2f(2.f, 2.f));
    }
    #endif //DEBUG

    const b2Vec2 start = {meshStart.x / Const::PixelPerUnit, meshStart.y /  Const::PixelPerUnit};
    const b2Vec2 finish = {point.x / Const::PixelPerUnit, point.y / Const::PixelPerUnit};
    m_world->RayCast(&callback, start, finish);
    if (callback.m_data.entity)
    {
        auto hitted = callback.m_data.entity;
        if (!hitted->GetComponent<DebugInfoComponent>())
        {
            hitted->AddComponent<DebugInfoComponent>();   
        }
        if (auto debugComponent = hitted->GetComponent<DebugInfoComponent>())
        {
            debugComponent->shape.setFillColor(sf::Color::Blue);
            debugComponent->shape.setOutlineColor(sf::Color::Blue);
            debugComponent->shape.setPointCount(3);
            debugComponent->shape.setPosition(0.f, 0.f);
            debugComponent->shape.setPoint(0, meshStart - hitted->getPosition());
            debugComponent->shape.setPoint(2, meshStart - hitted->getPosition() - sf::Vector2f(2.f, 2.f));
            debugComponent->shape.setPoint(1, callback.m_data.point - hitted->getPosition());
        }
    }
    return callback.m_data.entity;
}
