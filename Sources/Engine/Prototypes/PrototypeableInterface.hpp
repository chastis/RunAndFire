#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>
#include <string>

template <class T>
class IPrototypeable
{
public:
    virtual ~IPrototypeable() = default;
    virtual void InitFromPrototype() = 0;
    void SetPrototype(size_t prototypeID);
    void SetPrototype(const std::string& prototypeSID);
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
