#pragma once

#include <Engine/Factories/DynamicTypeFactory.hpp>
#include <Utility/Types/DynamicType.hpp>

class BaseComponent;

class ComponentFactory : public TypeFactoryBase
{
public:

    template <class T>
    BaseComponent* CreateComponent();
    BaseComponent* CreateComponent(const TypeId& typeId);

    void RegisterTypes() override;
private:
     using CreationFunction = std::function<BaseComponent* ()>;
    std::unordered_map<TypeId, CreationFunction> m_creators;
};

template <class T>
BaseComponent* ComponentFactory::CreateComponent()
{
    static_assert(std::is_base_of_v<BaseComponent, T>, "Component type should derrive ComponentBase!");
    const TypeId& componentId = T::GetStaticType();
    return CreateComponent(componentId);
}
