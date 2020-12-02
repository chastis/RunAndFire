#include <Engine/Entity/Entity.hpp>
#include <Engine/Factories/DynamicTypeFactory.hpp>
#include <Engine/Factories/ComponentFactory.hpp>
#include <Engine/Components/BaseComponent.hpp>

Entity::Entity() = default;
Entity::~Entity() = default;

void Entity::InitFromPrototype()
{
    const auto& componentsData = GetPrototype().GetComponents();
    for (const auto& componentInfo : componentsData)
    {
        BaseComponent* newComponent = AddComponent(componentInfo.first);
        if (componentInfo.second.has_value())
        {
            newComponent->InitPrototype(componentInfo.second.value());
        }
    }
    PostInitComponents();
}

BaseComponent* Entity::AddComponent(const TypeId& typeId)
{
    const auto& factory = DynamicTypeFactory::GetInstanceRef().GetFactoryRef<ComponentFactory>();
    BaseComponent* newComponent = factory.CreateComponent(typeId);
    m_components.emplace_back(newComponent);
    newComponent->Init(this);
    return newComponent;
}

BaseComponent* Entity::GetComponent(const TypeId& typeId) const
{
    for (const auto& componentIt : m_components)
    {
        if (componentIt->GetDynamicType() == typeId)
        {
            return  componentIt.get();
        }
    }
    return nullptr;
}

BaseComponent* Entity::GetKindOfComponent(const TypeId& typeId) const
{
    for (const auto& componentIt : m_components)
    {
        if (componentIt->IsKindOf(typeId))
        {
            return  componentIt.get();
        }
    }
    return nullptr;
}

void Entity::Update(float deltaTime)
{
    for (const auto& componentIt : m_components)
    {
        componentIt->Update(deltaTime);
    } 
}

void Entity::PostInitComponents()
{
    for (const auto& componentIt : m_components)
    {
        componentIt->PostInit();
    } 
}

UID Entity::GetUID() const
{
    return m_UID;
}
