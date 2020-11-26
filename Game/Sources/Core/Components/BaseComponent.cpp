#include <Core/Components/BaseComponent.hpp>
#include <Core/Entity.hpp>

Entity* BaseComponent::GetOwner() const
{
    return m_owner;
}

Entity& BaseComponent::GetOwnerRef() const
{
    return *m_owner;
}

void BaseComponent::Init(Entity* owner)
{
    // todo : assert
    m_owner = owner;
}

void BaseComponent::Update(float deltaTime)
{}
