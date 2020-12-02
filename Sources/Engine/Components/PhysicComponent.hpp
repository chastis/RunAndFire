#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/Prototypes/PhysicPrototype.hpp>

class PhysicComponent : public BasePrototypeableComponent<PhysicPrototype>
{
    DECLARE_DYNAMIC_TYPE(PhysicComponent, BasePrototypeableComponent<PhysicPrototype>)
public:
    void InitFromPrototype() override;
    void Update(float deltaTime) override;
protected:
    float m_mass = 0.f;
    bool m_isStatic = true;
};