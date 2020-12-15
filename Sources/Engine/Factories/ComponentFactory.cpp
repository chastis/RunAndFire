#include <Engine/Factories/ComponentFactory.hpp>
#include <Utility/Debugging/Assert.hpp>
#include <Engine/Components/EventHandlerComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>

#if defined(DEBUG)
#include <Engine/Debugging/EntityComponents_Debug.hpp>
#endif //DEBUG

BaseComponent* ComponentFactory::CreateComponent(const TypeId& typeId) const
{
    auto creator = m_creators.find(typeId);
    if (creator != m_creators.end())
    {
        return creator->second();
    }
    M42_ASSERT(false, "You forget to add component to Factory");
    return nullptr;
}

void ComponentFactory::RegisterTypes()
{
    m_creators[EventHandlerComponent::GetStaticType()] = []() { return new EventHandlerComponent; };
    m_creators[PhysicBodyComponent::GetStaticType()] = []() { return new PhysicBodyComponent; };
    m_creators[PhysicBodyComponentBase::GetStaticType()] = []() { return new PhysicBodyComponentBase; };
    m_creators[MeshComponent::GetStaticType()] = []() { return new MeshComponent; };
    m_creators[MeshComponentBase::GetStaticType()] = []() { return new MeshComponentBase; };
#if defined(DEBUG)
    m_creators[DebugInfoComponent::GetStaticType()] = []() { return new DebugInfoComponent; };
#endif //DEBUG
}
