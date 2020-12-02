#pragma once

#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Utility/Types/DynamicType.hpp>
#include <Utility/Core/Noncopyable.hpp>

class Entity;

class BaseComponent : public DynamicType, Noncopyable
{
    DECLARE_DYNAMIC_TYPE(BaseComponent, DynamicType)
public:
    [[nodiscard]] Entity* GetOwner() const;
    [[nodiscard]] Entity& GetOwnerRef() const;
    void Init(Entity* owner);
    virtual void PostInit() {};
    virtual void Update(float deltaTime) {};

    virtual void InitPrototype(const std::string& prototypeName)
    {
        M42_ASSERT(false, "you call this in not-inherited prototype class");
    }
    virtual void InitPrototype(size_t prototypeID)
    {
        M42_ASSERT(false, "you call this in not-inherited prototype class");
    }
protected:
    virtual void InitSpecific() {};

    Entity* m_owner = nullptr;
};

template <class T>
class BasePrototypeableComponent : public BaseComponent, public IPrototypeable<T>
{
    DECLARE_DYNAMIC_TYPE(BasePrototypeableComponent, BaseComponent)
public:
    void InitPrototype(const std::string& prototypeName) override
    {
        SetPrototype(prototypeName);
        InitFromPrototype();
    }
    void InitPrototype(size_t prototypeID) override
    {
        SetPrototype(prototypeID);
        InitFromPrototype();
    }
};
