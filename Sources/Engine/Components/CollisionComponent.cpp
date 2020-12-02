#include <Engine/Components/CollisionComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/Managers/EntityManager.hpp>
#include <Engine/Entity/EntityEvents.hpp>
#include <Engine/Entity/Entity.hpp>
#include <SFML/System/Vector2.hpp>

void CollisionComponent::InitFromPrototype()
{
    m_collisionBox = GetPrototype().GetCollisionBox();
}

void CollisionComponent::Update(float deltaTime)
{   
    std::vector<Entity*> entities = EntityManager::GetInstanceRef().GetEntities();
    for (auto en : entities)
    {
        if (en == GetOwner())
        {
            continue;
        }
        const auto enCollisionComp = en->GetComponent<CollisionComponent>();
        if (enCollisionComp && CheckCollision(*enCollisionComp))
        {
            auto collisionEvent = std::make_shared<EntityEvents::CollisionEntityEvent>();
            collisionEvent->collidedEntity.first = enCollisionComp->GetOwner();
            collisionEvent->collidedEntity.second = GetOwner();
            collisionEvent->intersection = GetIntersection(*enCollisionComp);
            EventSystem::Broadcast(collisionEvent, EntityEventChannel::GetInstance());
            EventSystem::Broadcast(collisionEvent, enCollisionComp->GetOwner());
            EventSystem::Broadcast(collisionEvent, GetOwner());
        }
    }
}

void CollisionComponent::PostInitSpecific()
{
    if (GetPrototype().IsInitFromMesh())
    {
        if (const auto meshComponent = GetOwnerRef().GetComponent<MeshComponent>())
        {
            m_collisionBox = meshComponent->getLocalBounds();
        }
        else
        {
            M42_ASSERT(false, "can't init from mesh, coz there is no mesh");   
        }
    }
}

bool CollisionComponent::CheckCollision(float x, float y) const
{
    const sf::FloatRect BoxWorldSpace = GetOwnerRef().getTransform().transformRect(m_collisionBox);
    return BoxWorldSpace.contains(x, y);
}

bool CollisionComponent::CheckCollision(sf::Vector2f point) const
{
    return CheckCollision(point.x, point.y);
}

bool CollisionComponent::CheckCollision(const CollisionComponent& collider) const
{
    return CheckCollision(*this, collider);
}

bool CollisionComponent::CheckCollision(const CollisionComponent& first, const CollisionComponent& second)
{
    const sf::FloatRect firstBoxWorldSpace = first.GetOwnerRef().getTransform().transformRect(first.m_collisionBox);
    const sf::FloatRect secondBoxWorldSpace = second.GetOwnerRef().getTransform().transformRect(second.m_collisionBox);
    return firstBoxWorldSpace.intersects(secondBoxWorldSpace) || secondBoxWorldSpace.intersects(firstBoxWorldSpace);
}

sf::FloatRect CollisionComponent::GetIntersection(const CollisionComponent& collider) const
{
    return FindIntersection(*this, collider);
}

sf::FloatRect CollisionComponent::FindIntersection(const CollisionComponent& first, const CollisionComponent& second)
{
    const sf::FloatRect firstBoxWorldSpace = first.GetOwnerRef().getTransform().transformRect(first.m_collisionBox);
    const sf::FloatRect secondBoxWorldSpace = second.GetOwnerRef().getTransform().transformRect(second.m_collisionBox);
    sf::FloatRect intersection;
    firstBoxWorldSpace.intersects(secondBoxWorldSpace, intersection);
    return intersection;
}

const sf::FloatRect& CollisionComponent::GetLocalCollisionBox() const
{
    return m_collisionBox;
}


sf::FloatRect CollisionComponent::GetWorldCollisionBox() const
{
    return GetOwnerRef().getTransform().transformRect(m_collisionBox);
}