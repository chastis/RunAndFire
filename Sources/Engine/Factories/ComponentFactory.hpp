#pragma once

#include <Engine/Factories/DynamicTypeFactory.hpp>
#include <Utility/Types/DynamicType.hpp>

class BaseComponent;

class ComponentFactory : public TypeFactoryBase
{
public:

    template <class T>
    [[nodiscard]] BaseComponent* CreateComponent() const;
    [[nodiscard]] BaseComponent* CreateComponent(const TypeId& typeId) const;
    void RegisterTypes() override;

    template <class T>
    void AddCustomType();
private:
    using CreationFunction = std::function<BaseComponent* ()>;
    std::unordered_map<TypeId, CreationFunction> m_creators;
};

template <class T>
BaseComponent* ComponentFactory::CreateComponent() const
{
    static_assert(std::is_base_of_v<BaseComponent, T>, "Component type should derrive ComponentBase!");
    const TypeId& componentId = T::GetStaticType();
    return CreateComponent(componentId);
}

template <class T>
void ComponentFactory::AddCustomType()
{
     m_creators[T::GetStaticType()] = []() { return new T; };
}
