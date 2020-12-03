#pragma once

#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/EventSystem/EventHandler.hpp>
//#include <Engine/EventSystem/EventCallback.hpp>
#include <Utility/Types/DynamicType.hpp>
#include <Utility/Core/Noncopyable.hpp>

class Entity;

class BaseComponent : public DynamicType, public Noncopyable
{
    DECLARE_DYNAMIC_TYPE(BaseComponent, DynamicType)
public:
    [[nodiscard]] Entity* GetOwner() const;
    [[nodiscard]] Entity& GetOwnerRef() const;
    void Init(Entity* owner);
    void PostInit();
    virtual void Update(float deltaTime) {};

    virtual void InitPrototype(const std::string& prototypeName);
    virtual void InitPrototype(size_t prototypeID);

    virtual void ConnectEvent(TypeId eventType);
protected:    

    virtual void InitSpecific() {};
    virtual void PostInitSpecific() {};

    Entity* m_owner = nullptr;
    EventHandler m_eventHandler;
};

template <class T>
class PrototypeableBaseComponent : public BaseComponent, public IPrototypeable<T>
{
    DECLARE_DYNAMIC_TYPE(BasePrototypeableComponent, BaseComponent)
public:
    void InitPrototype(const std::string& prototypeName) override
    {
        IPrototypeable<T>::SetPrototype(prototypeName);
        IPrototypeable<T>::InitFromPrototype();
    }
    void InitPrototype(size_t prototypeID) override
    {
        IPrototypeable<T>::SetPrototype(prototypeID);
        IPrototypeable<T>::InitFromPrototype();
    }
};
