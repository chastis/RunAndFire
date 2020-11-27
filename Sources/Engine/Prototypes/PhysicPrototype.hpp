#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>

class PhysicPrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node& node) override
    {
        if (const auto childNode = node.child("mass"))
        {
            if (const auto value = childNode.attribute("value"))
            {
                m_mass = value.as_float();
            }
            else
            {
                M42_ASSERT(false, "There is no value for Mass");
            }
        }
        if (const auto childNode = node.child("is_static"))
        {
            if (const auto value = childNode.attribute("value"))
            {
                m_isStatic = value.as_bool();
            }
            else
            {
                M42_ASSERT(false, "There is no value for Static");
            }
        }
    }
    [[nodiscard]] float GetMass() const
    {
        return m_mass;
    }
    [[nodiscard]] bool IsStatic() const
    {
        return m_isStatic;
    }
protected:
    float m_mass = 0.f;
    bool m_isStatic = true;
};

using PhysicPrototypes = BasePrototypes<PhysicPrototype>;