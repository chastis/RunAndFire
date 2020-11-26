#pragma once
#include <Utility/Core/Noncopyable.hpp>
#include <Utility/Ref/ReferenceCountable.hpp>
#include <Utility/DynamicType.hpp>
#include <map>

class  Entity : public Noncopyable, ReferenceCountable<>
{
public:
    template <class T>
    T* AddComponent();

    template <class T>
    T* GetComponent();
private:
    std::map<TypeId, std::unique_ptr<BaseComponent>> m_components;
};

template <class T>
T* Entity::AddComponent()
{
    static_assert(std::is_base_of_v<BaseComponent, T>, "Component type should derrive ComponentBase!");
    const TypeId& componentId = T::GetStaticType();
    T* newComponent = m_components.emplace(componentId, );
}

template <class T>
T* Entity::GetComponent()
{
    static_assert(std::is_base_of_v<BaseComponent, T>, "Component type should derrive ComponentBase!");
}
