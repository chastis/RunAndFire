#include <Engine/Components/PhysicComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Consts/Const.hpp>
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
        sf::Vector2f delta(0.f, 1.f);
        delta *= Const::G * deltaTime * deltaTime / 2;
        GetOwnerRef().move(delta);
    }
}
