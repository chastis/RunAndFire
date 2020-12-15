#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Static/Misc.hpp>

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

void ControllerComponent::SetAnimationRepetition(int32_t amount)
{
    auto meshComponent = GetOwnerRef().GetComponent<MeshComponent>();
    if (meshComponent)
    {
        if (amount == -1)
        {
            meshComponent->SetAnimationRepetitionInfinity();
        }
        else
        {
            meshComponent->SetAnimationRepetitionAmount(amount);
        }
    }
}

std::string ControllerComponent::GetPlayingAnimationName()
{
    const auto meshComponent = GetOwnerRef().GetComponent<MeshComponent>();
    if (meshComponent)
    {
        return meshComponent->GetPlayingAnimName();
    }
    return "";
}