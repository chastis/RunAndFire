#pragma once

#include <Utility/DynamicType.hpp>
#include <Utility/Core/Noncopyable.hpp>

class Entity;

class BaseComponent : public DynamicType, Noncopyable
{
    DECLARE_DYNAMIC_TYPE(BaseComponent, DynamicType)
public:
    [[nodiscard]] Entity* GetOwner() const;
    [[nodiscard]] Entity& GetOwnerRef() const;
    virtual void Init(Entity* owner);
    virtual void Update(float deltaTime);
protected:
    Entity* m_owner = nullptr;
};