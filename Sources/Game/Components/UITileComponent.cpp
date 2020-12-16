#include <Game/Components/UITileComponent.hpp>
#include <Game/Events/GameEvents.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Physics/Box2D/box2d.h>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/Engine.hpp>
#include <Game/Managers/GameManager.hpp>
#include <Game/Prototypes/UITileControllerPrototype.hpp>

UITileComponent::UITileComponent()
{
    m_prototypeWrapper = std::move(std::make_unique<IPrototypeWrapper<UITilePrototype>>());
}

void UITileComponent::InitFromPrototypeSpecific()
{

}

bool UITileComponent::HandleInput(const ActionSignal& signal)
{
    return false;  
}

void UITileComponent::PostInitSpecific()
{

}
