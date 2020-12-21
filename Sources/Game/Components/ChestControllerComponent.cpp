#include <Game/Components/ChestControllerComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Game/Events/GameEvents.hpp>
#include <Game/Managers/GameManager.hpp>
#include <Engine/Engine.hpp>
#include "Engine/Prototypes/ScenePrototype.hpp"

ChestControllerComponent::ChestControllerComponent()
{
    m_eventHandler.ConnectHandler(this, &ChestControllerComponent::OnTakeDamage);
    m_eventHandler.ConnectHandler(this, &ChestControllerComponent::OnAnimationEnded);
}

void ChestControllerComponent::OnTakeDamage(GameEvents::TakeDamageEvent& gameEvent)
{
    if (GetPlayingAnimationName() != "chest_open")
    {
        ChangeAnimation("chest_open");
        SetAnimationRepetition(1);
    }
}

void ChestControllerComponent::OnAnimationEnded(EntityEvents::AnimationEndedEvent& animationEvent)
{
    if (animationEvent.animation_name == "chest_open")
    {
        auto& engine = GameManager::GetInstanceRef().GetEngineInstanceRef();
        const auto& next_map = engine.GetCurrentScene()->GetPrototype<ScenePrototype>().GetNextMap();
        if (next_map.has_value())
        {
            engine.RequestChangeScene(next_map.value());
        }
        else
        {
            engine.RequestChangeScene("Menu");
        }
    }
}