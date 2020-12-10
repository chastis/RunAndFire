#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Static/Misc.hpp>

void ControllerComponent::ConnectEvent(TypeId eventType)
{

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
void ControllerComponent::ChangeAnimation(const std::string& animationName)
{
    auto meshComponent = GetOwnerRef().GetComponent<MeshComponent>();
    if (meshComponent)
    {
        meshComponent->ChangeAnimation(animationName);
    }
}