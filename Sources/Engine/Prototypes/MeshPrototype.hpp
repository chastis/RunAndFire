#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>

struct TileInfo
{
    std::string name;
    int32_t id = 0;
    void Parse(const pugi::xml_node& node)
    {
        if (const auto value = node.attribute("name"))
        {
            name = value.as_string();
        }
        else
        {
            M42_ASSERT(false, "There is no value for mesh_path");
        }
        if (const auto value = node.attribute("id"))
        {
            id = value.as_int();
        }
        else
        {
            M42_ASSERT(false, "There is no value for mesh_path");
        }
    }
};

class MeshPrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node& node) override
    {
        if (const auto childNode = node.child("animation_tiles"))
        {
            for (pugi::xml_node child : childNode.children())
            {
                TileInfo animationTile;
                animationTile.Parse(child);
                m_animationTiles.push_back(animationTile);
            }

        }
        if (const auto childNode = node.child("collision_tile"))
        {
            m_collisionTile.Parse(childNode);
        }
    }
    [[nodiscard]] const std::vector<TileInfo>& GetAnimationTiles() const
    {
        return m_animationTiles;
    }
    [[nodiscard]] const TileInfo& GetAnimationTile(std::string name) const
    {
        for (const auto& tile : m_animationTiles)
        {
            if (tile.name == name)
            {
                return tile;
            }
        }
        M42_ASSERT(false, "there is no tile with this name");
        return m_collisionTile;
    }
    [[nodiscard]] const TileInfo& GetCollisionTile() const
    {
        return m_collisionTile;
    }
protected:
    std::vector<TileInfo> m_animationTiles;
    TileInfo m_collisionTile;
};

using MeshPrototypes = BasePrototypes<MeshPrototype>;