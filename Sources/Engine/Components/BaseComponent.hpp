#pragma once

#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/EventSystem/EventHandler.hpp>
#include <Utility/Types/DynamicType.hpp>
#include <Utility/Core/Noncopyable.hpp>

class Entity;

class BaseComponent : public DynamicType, public Noncopyable, public IPrototypeable
{
    DECLARE_DYNAMIC_TYPE(BaseComponent, DynamicType)
public:
    [[nodiscard]] Entity* GetOwner() const;
    [[nodiscard]] Entity& GetOwnerRef() const;
    virtual void Update(float deltaTime) {};
    
    void Init(Entity* owner);
    void PostInit();

    virtual void ConnectEvent(TypeId eventType);
    template <class T>
    const T& GetPrototype() const;
protected:    
    virtual void InitSpecific() {};
    virtual void PostInitSpecific() {};

    Entity* m_owner = nullptr;
    EventHandler m_eventHandler;
};

template <class T>
const T& BaseComponent::GetPrototype() const
{
    return *reinterpret_cast<const T *>(m_prototypeWrapper->GetBasePrototype());
}