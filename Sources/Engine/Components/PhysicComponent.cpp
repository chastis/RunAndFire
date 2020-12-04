#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/PhysicComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Static/Const.hpp>
#include <SFML/System/Vector2.hpp>

void PhysicComponent::InitFromPrototype()
{
    m_mass = GetPrototype().GetMass();
    m_isStatic = GetPrototype().IsStatic();
}

void PhysicComponent::Update(float deltaTime)
{
    if (!m_isStatic)
    {
        if (auto controllerComp = GetOwnerRef().GetKindOfComponent<ControllerComponent>())
        {
            //controllerComp->m_velocity.y += Const::FallingForce * deltaTime;
        }
        else
        {
            M42_ASSERT(false, "you are trying apply physic to non-controllable component");
        }
    }
}
