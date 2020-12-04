#include <Engine/Components/CollisionComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/Managers/EntityManager.hpp>
#include <Engine/Entity/EntityEvents.hpp>
#include <Engine/Entity/Entity.hpp>
#include <SFML/System/Vector2.hpp>

#include <Engine/Physics/Box2D/box2d.h>
#include <Engine/Physics/PhysicEngine.hpp>
#include <Engine/Static/Const.hpp>

CollisionComponent::~CollisionComponent()
{
    for (auto& fixture : m_fixtures)
    {
        delete fixture.shape;
    }
}

void CollisionComponent::InitFromPrototype()
{
    auto entityPosition = GetOwnerRef().getPosition();
    m_bodyDefinition.position.Set(entityPosition.x / Const::PixelPerUnit, entityPosition.y / Const::PixelPerUnit);

    if (GetPrototype().IsInitFromMesh()) return;

    auto collisionBox = GetPrototype().GetCollisionBox();
    CreateFixture(collisionBox.width, collisionBox.height);
}

void CollisionComponent::Update(float deltaTime)
{   

}

void CollisionComponent::CreateFixture(float w, float h)
{
    auto dynamicBox = new b2PolygonShape;
    dynamicBox->SetAsBox(w / 2 / Const::PixelPerUnit, h / 2 / Const::PixelPerUnit);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = dynamicBox;

    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.userData.pointer = (uintptr_t)GetOwner();

    m_fixtures.push_back(fixtureDef);
}

void CollisionComponent::PostInitSpecific()
{
    if (GetPrototype().IsInitFromMesh())
    {
        if (const auto meshComponent = GetOwnerRef().GetComponent<MeshComponent>())
        {
            auto collisionBox = meshComponent->getLocalBounds();
            CreateFixture(collisionBox.width, collisionBox.height);
        }
        else
        {
            M42_ASSERT(false, "can't init from mesh, coz there is no mesh");   
        }
    }
}
//
//bool CollisionComponent::CheckCollision(float x, float y) const
//{
//    const sf::FloatRect BoxWorldSpace = GetOwnerRef().getTransform().transformRect(m_collisionBox);
//    return BoxWorldSpace.contains(x, y);
//}
//
//bool CollisionComponent::CheckCollision(sf::Vector2f point) const
//{
//    return CheckCollision(point.x, point.y);
//}
//
//bool CollisionComponent::CheckCollision(const CollisionComponent& collider) const
//{
//    return CheckCollision(*this, collider);
//}
//
//bool CollisionComponent::CheckCollision(const CollisionComponent& first, const CollisionComponent& second)
//{
//    const sf::FloatRect firstBoxWorldSpace = first.GetOwnerRef().getTransform().transformRect(first.m_collisionBox);
//    const sf::FloatRect secondBoxWorldSpace = second.GetOwnerRef().getTransform().transformRect(second.m_collisionBox);
//    return firstBoxWorldSpace.intersects(secondBoxWorldSpace) || secondBoxWorldSpace.intersects(firstBoxWorldSpace);
//}
//
//sf::FloatRect CollisionComponent::GetIntersection(const CollisionComponent& collider) const
//{
//    return FindIntersection(*this, collider);
//}
//
//sf::FloatRect CollisionComponent::FindIntersection(const CollisionComponent& first, const CollisionComponent& second)
//{
//    const sf::FloatRect firstBoxWorldSpace = first.GetOwnerRef().getTransform().transformRect(first.m_collisionBox);
//    const sf::FloatRect secondBoxWorldSpace = second.GetOwnerRef().getTransform().transformRect(second.m_collisionBox);
//    sf::FloatRect intersection;
//    firstBoxWorldSpace.intersects(secondBoxWorldSpace, intersection);
//    return intersection;
//}
//
//const sf::FloatRect& CollisionComponent::GetLocalCollisionBox() const
//{
//    return m_collisionBox;
//}
//
//
//sf::FloatRect CollisionComponent::GetWorldCollisionBox() const
//{
//    return GetOwnerRef().getTransform().transformRect(m_collisionBox);
//}

const b2BodyDef& CollisionComponent::GetBodyDefinition() const
{
    return m_bodyDefinition;
}

const std::vector<b2FixtureDef>& CollisionComponent::GetBodyFixtures() const
{
    return m_fixtures;
}
