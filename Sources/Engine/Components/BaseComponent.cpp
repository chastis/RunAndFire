#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Entity.hpp>
#include <Utility/Debugging/Assert.hpp>

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
    M42_ASSERT(owner, "You forget to add component to Factory");
    m_owner = owner;
}

void BaseComponent::Update(float deltaTime)
{}
