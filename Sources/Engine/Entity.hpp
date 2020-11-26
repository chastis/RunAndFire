#pragma once
#include <Utility/Core/Noncopyable.hpp>
#include <Utility/Ref/ReferenceCountable.hpp>
#include <Utility/Types/DynamicType.hpp>
#include <map>

class BaseComponent;

class  Entity final : public Noncopyable, ReferenceCountable<>
{
public:
    Entity();
    ~Entity();
    template <class T>
    T* AddComponent();
    BaseComponent* AddComponent(const TypeId& typeId);
    template <class T>
    T* GetComponent();
    BaseComponent* GetComponent(const TypeId& typeId);
private:
    std::unordered_map<TypeId, std::unique_ptr<BaseComponent>> m_components;
};

template <class T>
T* Entity::AddComponent()
{
    static_assert(std::is_base_of_v<BaseComponent, T>, "Component type should derrive ComponentBase!");
    const TypeId& componentId = T::GetStaticType();
    BaseComponent* newComponent = AddComponent(componentId);
    return static_cast<T>(newComponent);
}

template <class T>
T* Entity::GetComponent()
{
    static_assert(std::is_base_of_v<BaseComponent, T>, "Component type should derrive ComponentBase!");
    const TypeId& componentId = T::GetStaticType();
    BaseComponent* findComponent = GetComponent(componentId);
    return static_cast<T>(findComponent);
}
