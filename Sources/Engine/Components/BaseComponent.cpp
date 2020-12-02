#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Components/EventHandlerComponent.hpp>
#include <Engine/Entity/Entity.hpp>
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
    M42_ASSERT(owner, "You forget to give owner");
    m_owner = owner;
    InitSpecific();
}

void BaseComponent::PostInit()
{
    PostInitSpecific();
    if (auto eventComponent = GetOwnerRef().GetComponent<EventHandlerComponent>())
    {
        eventComponent->ConnectHandler(m_eventHandler);
    }
}

void BaseComponent::InitPrototype(const std::string& prototypeName)
{
    M42_ASSERT(false, "you call this in not-inherited prototype class");
}

void BaseComponent::InitPrototype(size_t prototypeID)
{
    M42_ASSERT(false, "you call this in not-inherited prototype class");
}

void BaseComponent::ConnectEvent(TypeId eventType)
{
     M42_ASSERT(false, "you need to override this, if you want to subscribe to events");
}
