#pragma once

#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/EventSystem/EventHandler.hpp>
#include <Utility/Types/DynamicType.hpp>
#include <Utility/Core/Noncopyable.hpp>

enum class EComponentStatus
{
    Created,
    PostPrototypeInit,
    Initialized
};

class Entity;

class BaseComponent : public DynamicType, public Noncopyable
{
    DECLARE_DYNAMIC_TYPE(BaseComponent, DynamicType)
public:
    [[nodiscard]] Entity* GetOwner() const;
    [[nodiscard]] Entity& GetOwnerRef() const;
    virtual void Update(float deltaTime) {};
    
    void Init(Entity* owner);
    void PostInit();

    virtual void InitPrototype(const std::string& prototypeName);
    virtual void InitPrototype(size_t prototypeID);
    void PostPrototypeInit();
    virtual void ConnectEvent(TypeId eventType);
protected:    

    virtual void InitSpecific() {};
    virtual void PostPrototypeInitSpecific() {};
    virtual void PostInitSpecific() {};
    Entity* m_owner = nullptr;
    EventHandler m_eventHandler;
    EComponentStatus m_status = EComponentStatus::Created;

    // todo : rewrite using this, instead of inheritance
    std::unique_ptr<IPrototypeableBase> m_prototype; 
};

template <class T>
class PrototypeableBaseComponent : public BaseComponent, public IPrototypeable<T>
{
    DECLARE_DYNAMIC_TYPE(BasePrototypeableComponent, BaseComponent)
public:
    void InitPrototype(const std::string& prototypeName) override
    {
        this->SetPrototype(prototypeName);
        this->InitFromPrototype();
        m_status = EComponentStatus::PostPrototypeInit;
    }
    void InitPrototype(size_t prototypeID) override
    {
        this->SetPrototype(prototypeID);
        this->InitFromPrototype();
        m_status = EComponentStatus::PostPrototypeInit;
    }
};
