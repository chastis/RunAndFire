#include <Engine/Entity.hpp>
#include <Engine/Factories/DynamicTypeFactory.hpp>
#include <Engine/Factories/ComponentFactory.hpp>
#include <Engine/Components/BaseComponent.hpp>

Entity::Entity() = default;
Entity::~Entity() = default;

BaseComponent* Entity::AddComponent(const TypeId& typeId)
{
    const auto& factory = DynamicTypeFactory::GetInstanceRef().GetFactoryRef<ComponentFactory>();
    BaseComponent* newComponent = factory.CreateComponent(typeId);
    m_components.emplace(typeId, newComponent);
    return newComponent;
}

BaseComponent* Entity::GetComponent(const TypeId& typeId)
{
    const auto componentIt = m_components.find(typeId);
    if (componentIt != m_components.end())
    {
        return componentIt->second.get();
    }
    return nullptr;
}
