#include <Engine/Physics/RayCasts.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Static/Const.hpp>

EntityRayCastCallback::EntityRayCastCallback(Entity* owner)
    : m_owner(owner)
{

}

float EntityRayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
    const b2Vec2& normal, float fraction)
{
    if (fixture)
    {
        Entity* fixtureOwner = reinterpret_cast<Entity*>(fixture->GetUserData().pointer);
        if (fixtureOwner && fixtureOwner != m_owner)
        {
            m_data.entity = fixtureOwner;
            m_data.fraction = fraction;
            m_data.normal = {normal.x, normal.y};
            m_data.point = {point.x * Const::PixelPerUnit, point.y * Const::PixelPerUnit};
            return 0.f;
        }
    }
    return -1.f;
}
