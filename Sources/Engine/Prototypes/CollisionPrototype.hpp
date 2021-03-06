#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>
#include <SFML/Graphics/Rect.hpp>

class CollisionPrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node& node) override
    {
        if (const auto childNode = node.child("collision_box"))
        {
            if (const auto value = childNode.attribute("init_from_mesh"))
            {
                m_initFromMesh = value.as_bool();
            }
            if (const auto value = childNode.attribute("left"))
            {
                m_collisionBox.left = value.as_float();
            }
            if (const auto value = childNode.attribute("top"))
            {
                m_collisionBox.top = value.as_float();
            }
            if (const auto value = childNode.attribute("width"))
            {
                m_collisionBox.width = value.as_float();
            }
            if (const auto value = childNode.attribute("height"))
            {
                m_collisionBox.height = value.as_float();
            }
        }
    }
    [[nodiscard]] sf::FloatRect GetCollisionBox() const
    {
        return m_collisionBox;
    }
    [[nodiscard]] bool IsInitFromMesh() const
    {
        return m_initFromMesh;
    }
protected:
    sf::FloatRect m_collisionBox;
    bool m_initFromMesh = false;
};

using CollisionPrototypes = BasePrototypes<CollisionPrototype>;