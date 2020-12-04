#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Static/Misc.hpp>

void ControllerComponent::ConnectEvent(TypeId eventType)
{
    //if (eventType == EntityEvents::CollisionEntityEvent::GetStaticType())
    //{
    //    m_eventHandler.ConnectHandler(this, &ControllerComponent::OnCollision);
    //}
}

void ControllerComponent::UpdateMovement(float deltaTime)
{
    sf::Vector2f delta = m_velocity * deltaTime;
    //delta += deltaTime * deltaTime * m_accel / 2.f;
    GetOwnerRef().move(delta);
}

void ControllerComponent::SetMeshScale(sf::Vector2f scale)
{
    SetMeshScale(scale.x, scale.y);
}

void ControllerComponent::SetMeshScale(float x, float y)
{
    auto meshComponent = GetOwnerRef().GetKindOfComponent<MeshComponentBase>();
    if (meshComponent)
    {
        meshComponent->setScale(x, y);
    }
}

//void ControllerComponent::OnCollision(EntityEvents::CollisionEntityEvent& entityEvent)
//{
//    if (!GetOwnerRef().GetComponent<CollisionComponent>())
//    {
//        return;
//    }
//    const sf::FloatRect collisionBox = GetOwnerRef().GetComponent<CollisionComponent>()->GetWorldCollisionBox();
//    sf::Vector2f shift(0.f, 0.f);
//    if (Misc::IsNearlyEqual(collisionBox.top + collisionBox.height, entityEvent.intersection.top + entityEvent.intersection.height))
//    {
//        shift.y = -entityEvent.intersection.height;
//        m_velocity.y = 0.f;
//    }
//    else if (Misc::IsNearlyEqual(collisionBox.top, entityEvent.intersection.top))
//    {
//        shift.y = entityEvent.intersection.height;
//        m_velocity.y = 0.f;
//    }
//    else if (Misc::IsNearlyEqual(collisionBox.left + collisionBox.width, entityEvent.intersection.left + entityEvent.intersection.width))
//    {
//        shift.x = -entityEvent.intersection.width;
//    }
//    else if (Misc::IsNearlyEqual(collisionBox.left, entityEvent.intersection.left))
//    {

//        shift.x = entityEvent.intersection.width;
//    }
//    GetOwnerRef().move(shift);
//}
