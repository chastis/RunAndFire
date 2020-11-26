#include <Engine/Factories/DynamicTypeFactory.hpp>
#include <Engine/Factories/ComponentFactory.hpp>

DynamicTypeFactory_Impl::FactoryTypeId DynamicTypeFactory_Impl::ms_typeIdProvider = 0;

DynamicTypeFactory_Impl::DynamicTypeFactory_Impl()
{
    RegisterConcreteTypeFactory<ComponentFactory>();
}