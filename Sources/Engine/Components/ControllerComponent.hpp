#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/InputSystem/InputClient.hpp>
#include <Game/Prototypes/PlayerControllerPrototype.hpp>
#include <Engine/InputSystem/ActionMap.hpp>
#include <Engine/Entity/EntityEvents.hpp>

class ControllerComponent : public BaseComponent
{
    DECLARE_DYNAMIC_TYPE(ControllerComponent, BaseComponent)
public:
    void ConnectEvent(TypeId eventType) override;
    sf::Vector2f m_velocity;
protected:
    void SetMeshScale(sf::Vector2f scale);
    void SetMeshScale(float x, float y);
    void ChangeAnimation(const std::string& animationName);
};