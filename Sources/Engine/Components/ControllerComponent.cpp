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
    m_meshComponent->setScale(x, y);
}
void ControllerComponent::ChangeAnimation(const std::string& animationName)
{
    m_meshComponent->ChangeAnimation(animationName);
}

void ControllerComponent::SetAnimationRepetition(int32_t amount)
{
    if (amount == -1)
    {
        m_meshComponent->SetAnimationRepetitionInfinity();
    }
    else
    {
        m_meshComponent->SetAnimationRepetitionAmount(amount);
    }
}

std::string ControllerComponent::GetPlayingAnimationName()
{
    return m_meshComponent->GetPlayingAnimName();
}

void ControllerComponent::PostInitSpecific()
{
    m_meshComponent = GetOwnerRef().GetComponent<MeshComponent>();
}
