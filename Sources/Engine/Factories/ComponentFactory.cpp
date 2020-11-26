#include <Engine/Factories/ComponentFactory.hpp>

BaseComponent* ComponentFactory::CreateComponent(const TypeId& typeId)
{
    auto creator = m_creators.find(typeId);
    if (creator != m_creators.end())
    {
        return creator->second();
    }
    // todo : assert
    return nullptr;
}

void ComponentFactory::RegisterTypes()
{

}
