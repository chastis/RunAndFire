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
    if (!m_prototypeWrapper)
    {
        // if there is no m_prototypeWrapper we still want to PostPrototypeInitSpecific
        // because it called in InitFromPrototype, which will not call in NON-prototype component
        PostPrototypeInitSpecific();
    }
    PostInitSpecific();
    if (auto eventComponent = GetOwnerRef().GetComponent<EventHandlerComponent>())
    {
        eventComponent->ConnectHandler(m_eventHandler);
    }
}

void BaseComponent::ConnectEvent(TypeId eventType)
{
    M42_ASSERT(false, "you need to override this, if you want to subscribe to events");
}
