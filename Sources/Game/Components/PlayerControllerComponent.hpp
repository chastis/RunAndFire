#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/Prototypes/PhysicPrototype.hpp>

class PlayerControllerComponent : public BaseComponent, public IPrototypeable<PhysicPrototype>
{
    DECLARE_DYNAMIC_TYPE(PlayerControllerComponent, BaseComponent)
public:
    void InitFromPrototype() override;
    void Update(float deltaTime) override;
protected:
    
};