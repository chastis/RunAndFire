#include <Engine/Entity/Entity.hpp>
#include <Engine/Entity/EntityEvents.hpp>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/Factories/DynamicTypeFactory.hpp>
#include <Engine/Factories/ComponentFactory.hpp>
#include <Engine/Components/BaseComponent.hpp>

Entity::Entity()
{
    m_prototypeWrapper = std::move(std::make_unique<IPrototypeWrapper<EntityPrototype>>());
}
Entity::~Entity() = default;

void Entity::InitFromPrototypeSpecific()
{
    const auto& componentsData = GetPrototype<EntityPrototype>().GetComponents();
    for (const auto& componentInfo : componentsData)
    {
        BaseComponent* newComponent = AddComponent(componentInfo.first);
        if (componentInfo.second.has_value())
        {
            newComponent->InitFromPrototype(componentInfo.second.value());
        }
    }
}

BaseComponent* Entity::AddComponent(const TypeId& typeId)
{
    const auto& factory = DynamicTypeFactory::GetInstanceRef().GetFactoryRef<ComponentFactory>();
    BaseComponent* newComponent = factory.CreateComponent(typeId);

    auto componentCreatedEvent = std::make_shared<EntityEvents::ComponentCreatedEvent>();
    componentCreatedEvent->component = newComponent;
    EventSystem::Broadcast(std::move(componentCreatedEvent), EntityEventChannel::GetInstance());

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

std::vector<BaseComponent*> Entity::GetComponents(const TypeId& typeId) const
{
    std::vector<BaseComponent*> components;
    for (const auto& componentIt : m_components)
    {
        if (componentIt->GetStaticType() == typeId)
        {
            components.push_back(componentIt.get());
        }
    }
    return components;
}

std::vector<BaseComponent*> Entity::GetKindOfComponents(const TypeId& typeId) const
{
    std::vector<BaseComponent*> components;
    for (const auto& componentIt : m_components)
    {
        if (componentIt->IsKindOf(typeId))
        {
            components.push_back(componentIt.get());
        }
    }
    return components;
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
