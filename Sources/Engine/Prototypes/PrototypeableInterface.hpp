#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>
#include <string>

class IPrototypeableBase
{
public:
    virtual void InitFromPrototype()
    {
        M42_ASSERT(false, "you call this in not-inherited prototype class");
    }
    virtual void SetPrototype(size_t prototypeID)
    {
        M42_ASSERT(false, "you call this in not-inherited prototype class");
    }
    virtual void SetPrototype(const std::string& prototypeSID)
    {
        M42_ASSERT(false, "you call this in not-inherited prototype class");
    }
};

template <class T>
class IPrototypeable : public IPrototypeableBase
{
public:
    virtual ~IPrototypeable() = default;
    //virtual void InitFromPrototype() = 0;
    void SetPrototype(size_t prototypeID) override;
    void SetPrototype(const std::string& prototypeSID) override;
    [[nodiscard]] const T& GetPrototype() const;
protected:
    const T* prototype = nullptr;
};

template <class T>
void IPrototypeable<T>::SetPrototype(size_t prototypeID)
{
    prototype = &BasePrototypes<T>::Get(prototypeID);
}

template <class T>
void IPrototypeable<T>::SetPrototype(const std::string& prototypeSID)
{
    prototype = &BasePrototypes<T>::Get(prototypeSID);
}

template <class T>
const T& IPrototypeable<T>::GetPrototype() const
{
    if (prototype)
    {
        return *prototype;
    }
    return BasePrototypes<T>::GetDefault();
}
