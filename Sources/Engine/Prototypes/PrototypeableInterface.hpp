#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>
#include <string>

class IPrototypeWrapperBase
{
public:
    virtual void SetPrototype(size_t prototypeID);
    virtual void SetPrototype(const std::string& prototypeSID);
    [[nodiscard]] virtual const BasePrototype* GetBasePrototype() const;
};

template <class T>
class IPrototypeWrapper : public IPrototypeWrapperBase
{
public:
    virtual ~IPrototypeWrapper() = default;
    void SetPrototype(size_t prototypeID) override;
    void SetPrototype(const std::string& prototypeSID) override;
    [[nodiscard]] const BasePrototype* GetBasePrototype() const override;
    [[nodiscard]] const T& GetPrototype() const;
protected:
    const T* prototype = nullptr;
};

class IPrototypeable
{
public:
    void InitFromPrototype(const std::string& prototypeName);
    void InitFromPrototype(size_t prototypeID);
    bool IsPrototypeExist() const;
    
    template <class T>
    const T& GetPrototype() const;

protected:
    virtual void InitFromPrototypeSpecific() {};
    virtual void PostPrototypeInitSpecific() {};
    std::unique_ptr<IPrototypeWrapperBase> m_prototypeWrapper; 
};

template <class T>
const T& IPrototypeable::GetPrototype() const
{
    return *reinterpret_cast<const T *>(m_prototypeWrapper->GetBasePrototype());
}

template <class T>
void IPrototypeWrapper<T>::SetPrototype(size_t prototypeID)
{
    prototype = &BasePrototypes<T>::Get(prototypeID);
}

template <class T>
void IPrototypeWrapper<T>::SetPrototype(const std::string& prototypeSID)
{
    prototype = &BasePrototypes<T>::Get(prototypeSID);
}

template <class T>
const BasePrototype* IPrototypeWrapper<T>::GetBasePrototype() const
{
    return reinterpret_cast<const BasePrototype*>(prototype);
}

template <class T>
const T& IPrototypeWrapper<T>::GetPrototype() const
{
    if (prototype)
    {
        return *prototype;
    }
    return BasePrototypes<T>::GetDefault();
}

