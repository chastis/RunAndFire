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
    //sf::Vector2f m_accel;
protected:
    void UpdateMovement(float deltaTime);

    void OnCollision(EntityEvents::CollisionEntityEvent& entityEvent);
};

template <class T>
class PrototypeableControllerComponent : public ControllerComponent, public IPrototypeable<T>
{
    DECLARE_DYNAMIC_TYPE(PrototypeableControllerComponent, ControllerComponent)
public:
    void InitPrototype(const std::string& prototypeName) override
    {
        SetPrototype(prototypeName);
        InitFromPrototype();
    }
    void InitPrototype(size_t prototypeID) override
    {
        SetPrototype(prototypeID);
        InitFromPrototype();
    }
};