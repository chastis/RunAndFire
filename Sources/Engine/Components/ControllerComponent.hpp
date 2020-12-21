#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/InputSystem/InputClient.hpp>
#include <Game/Prototypes/PlayerControllerPrototype.hpp>
#include <Engine/InputSystem/ActionMap.hpp>
#include <Engine/Entity/EntityEvents.hpp>

class MeshComponent;

class ControllerComponent : public BaseComponent
{
    DECLARE_DYNAMIC_TYPE(ControllerComponent, BaseComponent)
public:
    void SetMeshScale(sf::Vector2f scale);
    void SetMeshScale(float x, float y);
    void ChangeAnimation(const std::string& animationName);
    void SetAnimationRepetition(int32_t amount);
    std::string GetPlayingAnimationName();
protected:
    void PostInitSpecific() override;
    sf::Vector2f m_velocity;
    MeshComponent* m_meshComponent = nullptr;
};