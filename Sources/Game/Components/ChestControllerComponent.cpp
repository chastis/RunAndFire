#include <Game/Components/ChestControllerComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Game/Events/GameEvents.hpp>

ChestControllerComponent::ChestControllerComponent()
{
    m_eventHandler.ConnectHandler(this, &ChestControllerComponent::OnTakeDamage);
}

void ChestControllerComponent::OnTakeDamage(GameEvents::TakeDamageEvent& gameEvent)
{
    if (GetPlayingAnimationName() != "chest_open")
    {
        ChangeAnimation("chest_open");
        SetAnimationRepetition(1);
    }
}
