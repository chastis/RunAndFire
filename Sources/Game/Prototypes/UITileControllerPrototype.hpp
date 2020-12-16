#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>
#include <SFML/System/Vector2.hpp>

class UITilePrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node& node) override
    {
        if (const auto jumpForceAttr = node.attribute("jump_force"))
        {
           // m_jumpForce = jumpForceAttr.as_float();
        }
        if (const auto childNode = node.child("speed"))
        {
            if (const auto value = childNode.attribute("x"))
            {
              //  m_speed.x = value.as_float();
            }
            if (const auto value = childNode.attribute("y"))
            {
                //m_speed.y = value.as_float();
            }
        }
    }
protected:

};

using UITilePrototypes = BasePrototypes<UITilePrototype>;