#include <Engine/Factories/ComponentFactory.hpp>
#include <Utility/Debugging/Assert.hpp>

BaseComponent* ComponentFactory::CreateComponent(const TypeId& typeId) const
{
    auto creator = m_creators.find(typeId);
    if (creator != m_creators.end())
    {
        return creator->second();
    }
    M42_ASSERT(false, "You forget to add component to Factory");
    return nullptr;
}

void ComponentFactory::RegisterTypes()
{

}
