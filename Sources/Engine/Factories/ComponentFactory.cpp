#include <Engine/Factories/ComponentFactory.hpp>
#include <Utility/Debugging/Assert.hpp>
#include <Engine/Components/CollisionComponent.hpp>
#include <Engine/Components/EventHandlerComponent.hpp>
#include <Engine/Components/PhysicComponent.hpp>
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
    m_creators[CollisionComponent::GetStaticType()] = []() { return new CollisionComponent; };
    m_creators[EventHandlerComponent::GetStaticType()] = []() { return new EventHandlerComponent; };
    m_creators[PhysicComponent::GetStaticType()] = []() { return new PhysicComponent; };
    m_creators[MeshComponent::GetStaticType()] = []() { return new MeshComponent; };
    m_creators[MeshComponentBase::GetStaticType()] = []() { return new MeshComponentBase; };
#if defined(DEBUG)
    m_creators[CircleShapeComponent::GetStaticType()] = []() { return new CircleShapeComponent; };
    m_creators[EntityControllerComponent::GetStaticType()] = []() { return new EntityControllerComponent; };
#endif //DEBUG
}
