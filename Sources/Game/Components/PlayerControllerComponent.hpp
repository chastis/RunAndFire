#pragma once

#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/BaseComponent.hpp>
#include <Engine/InputSystem/InputClient.hpp>
#include <Game/Prototypes/PlayerControllerPrototype.hpp>
#include <Engine/InputSystem/ActionMap.hpp>

class PhysicBodyComponent;

class PlayerControllerComponent : public ControllerComponent, public InputClient
{
    DECLARE_DYNAMIC_TYPE(PlayerControllerComponent, ControllerComponent)
public:
    PlayerControllerComponent();

    void InitFromPrototypeSpecific() override;
    void Update(float deltaTime) override;
    bool HandleInput(const ActionSignal& signal) override;
private:
    void PostInitSpecific() override;
private:
    sf::Vector2f m_speed;
    sf::Vector2f m_direction;

    PhysicBodyComponent* m_physicComponent = nullptr;
};
