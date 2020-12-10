#include <Engine/Prototypes/PrototypeableInterface.hpp>

void IPrototypeWrapperBase::SetPrototype(size_t prototypeID)
{
    M42_ASSERT(false, "you call this in not-inherited prototype class");
}
void IPrototypeWrapperBase::SetPrototype(const std::string& prototypeSID)
{
    M42_ASSERT(false, "you call this in not-inherited prototype class");
}

const BasePrototype* IPrototypeWrapperBase::GetBasePrototype() const
{
    M42_ASSERT(false, "you call this in not-inherited prototype class");
    return nullptr;
}

void IPrototypeable::InitFromPrototype(const std::string& prototypeName)
{
    if (m_prototypeWrapper)
    {
        m_prototypeWrapper->SetPrototype(prototypeName);
        InitFromPrototypeSpecific();
    }
    else
    {
        M42_ASSERT(false, "you forgot to create prototype");
    }
    PostPrototypeInitSpecific();
}

void IPrototypeable::InitFromPrototype(size_t prototypeID)
{
    if (m_prototypeWrapper)
    {
        m_prototypeWrapper->SetPrototype(prototypeID);
        InitFromPrototypeSpecific();
    }
    else
    {
        M42_ASSERT(false, "you forgot to create prototype");
    }
    PostPrototypeInitSpecific();
}
