#pragma once
#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/Prototypes/EntityPrototype.hpp>
#include <Utility/Core/Noncopyable.hpp>
#include <Utility/Ref/ReferenceCountable.hpp>
#include <Utility/Types/DynamicType.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>

class BaseComponent;

using UID = size_t;

class Entity final : public sf::Transformable, public Noncopyable, public ReferenceCountable<DefaultThreadPolicy>, public IPrototypeable<EntityPrototype>
{
public:
    Entity();
    ~Entity();

    void InitFromPrototype() override;
    void PostInitComponents();

    template <class T>
    [[nodiscard]] T* GetComponent() const;
    [[nodiscard]] BaseComponent* GetComponent(const TypeId& typeId) const;
    template <class T>
    [[nodiscard]] T* GetKindOfComponent() const;
    [[nodiscard]] BaseComponent* GetKindOfComponent(const TypeId& typeId) const;
    template <class T>
    [[nodiscard]] std::vector<T*> GetComponents() const;
    [[nodiscard]] std::vector<BaseComponent*> GetComponents(const TypeId& typeId) const;
    template <class T>
    [[nodiscard]] std::vector<T*> GetKindOfComponents() const;
    [[nodiscard]] std::vector<BaseComponent*> GetKindOfComponents(const TypeId& typeId) const;
    UID GetUID() const;

    template <class T>
    T* AddComponent();
    BaseComponent* AddComponent(const TypeId& typeId);

    void Update(float deltaTime);
private:
    void PostPrototypeInitComponents();
    std::vector<std::unique_ptr<BaseComponent>> m_components;
    UID m_UID = 0;
    friend class EntityManager_Impl;
};

template <class T>
T* Entity::AddComponent()
{
    static_assert(std::is_base_of_v<BaseComponent, T>, "Component type should derrive ComponentBase!");
    const TypeId& componentId = T::GetStaticType();
    BaseComponent* newComponent = AddComponent(componentId);
    return static_cast<T*>(newComponent);
}

template <class T>
T* Entity::GetComponent() const
{
    static_assert(std::is_base_of_v<BaseComponent, T>, "Component type should derrive ComponentBase!");
    const TypeId& componentId = T::GetStaticType();
    BaseComponent* findComponent = GetComponent(componentId);
    return static_cast<T*>(findComponent);
}

template <class T>
T* Entity::GetKindOfComponent() const
{
    static_assert(std::is_base_of_v<BaseComponent, T>, "Component type should derrive ComponentBase!");
    const TypeId& componentId = T::GetStaticType();
    BaseComponent* findComponent = GetKindOfComponent(componentId);
    return static_cast<T*>(findComponent);
}

template <class T>
std::vector<T*> Entity::GetComponents() const
{
    std::vector<T*> components;
    for (auto& comp : GetComponents(T::GetStaticType()))
    {
        components.push_back(static_cast<T*>(comp));
    }
    return components;
}

template <class T>
std::vector<T*> Entity::GetKindOfComponents() const
{
    std::vector<T*> components;
    for (auto& comp : GetKindOfComponents(T::GetStaticType()))
    {
        components.push_back(static_cast<T*>(comp));
    }
    return components;
}
