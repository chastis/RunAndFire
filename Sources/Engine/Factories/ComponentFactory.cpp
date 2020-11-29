#include <Engine/Factories/ComponentFactory.hpp>
#include <Utility/Debugging/Assert.hpp>

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
#if defined(DEBUG)
    m_creators[CircleShapeComponent::GetStaticType()] = []() { return new CircleShapeComponent; };
    m_creators[EntityControllerComponent::GetStaticType()] = []() { return new EntityControllerComponent; };
#endif //DEBUG
}
