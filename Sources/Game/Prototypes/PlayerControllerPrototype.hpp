#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>
#include <SFML/System/Vector2.hpp>

class PlayerControllerPrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node& node) override
    {
        if (const auto jumpForceAttr = node.attribute("jump_force"))
        {
            m_jumpForce = jumpForceAttr.as_float();
        }
        if (const auto childNode = node.child("speed"))
        {
            if (const auto value = childNode.attribute("x"))
            {
                m_speed.x = value.as_float();
            }
            if (const auto value = childNode.attribute("y"))
            {
                m_speed.y = value.as_float();
            }
        }
    }
    [[nodiscard]] sf::Vector2f GetSpeed() const
    {
        return m_speed;
    }
    [[nodiscard]] float GetJumpForce() const
    {
        return m_jumpForce;
    }
protected:
    sf::Vector2f m_speed;
    float m_jumpForce = 10.f;
};

using PlayerControllerPrototypes = BasePrototypes<PlayerControllerPrototype>;