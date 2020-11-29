#include <Engine/Components/CollisionComponent.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/Managers/EntityManager.hpp>
#include <Engine/Entity/EntityEvents.hpp>
#include <Engine/Entity/Entity.hpp>
#include <SFML/System/Vector2.hpp>

void CollisionComponent::InitFromPrototype()
{
    
}

void CollisionComponent::Update(float deltaTime)
{   
    std::vector<Entity*> entities = EntityManager::GetInstanceRef().GetEntities();
    for (auto en : entities)
    {
        const auto enCollisionComp = en->GetComponent<CollisionComponent>();
        if (enCollisionComp && CheckCollision(*enCollisionComp))
        {
            auto collisionEvent = std::make_shared<EntityEvents::CollisionEntityEvent>();
            collisionEvent->CollidedEntity = enCollisionComp->GetOwner();
            EventSystem::Broadcast(collisionEvent, EntityEventChannel::GetInstance());
            EventSystem::Broadcast(collisionEvent, EntityEventChannel::GetInstance());
        }
    }
}

bool CollisionComponent::CheckCollision(float x, float y) const
{
    const sf::FloatRect BoxWorldSpace = GetOwnerRef().getTransform().transformRect(collisionBox);
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
    const sf::FloatRect firstBoxWorldSpace = first.GetOwnerRef().getTransform().transformRect(first.collisionBox);
    const sf::FloatRect secondBoxWorldSpace = second.GetOwnerRef().getTransform().transformRect(second.collisionBox);
    return firstBoxWorldSpace.intersects(secondBoxWorldSpace) || secondBoxWorldSpace.intersects(firstBoxWorldSpace);
}
