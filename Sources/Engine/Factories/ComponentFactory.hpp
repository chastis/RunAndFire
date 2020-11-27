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
