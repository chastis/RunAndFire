#pragma once

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
protected:
    virtual void InitSpecific() {};

    Entity* m_owner = nullptr;
};