#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>

class MeshPrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node& node) override
    {
        if (const auto childNode = node.child("mesh_tile_name"))
        {
            if (const auto value = childNode.attribute("value"))
            {
                m_meshTileName = value.as_string();
            }
            else
            {
                M42_ASSERT(false, "There is no value for mesh_path");
            }
        }
        if (const auto childNode = node.child("tile_id"))
        {
            if (const auto value = childNode.attribute("value"))
            {
                m_tileId = static_cast<uint32_t>(value.as_uint());
            }
            else
            {
                M42_ASSERT(false, "There is no value for mesh_path");
            }
        }
    }
    [[nodiscard]] const std::string& GetMeshTileName() const
    {
        return m_meshTileName;
    }
    [[nodiscard]] uint32_t GetTileId() const
    {
        return m_tileId;
    }
protected:
    std::string m_meshTileName;
    uint32_t m_tileId = 0;
};

using MeshPrototypes = BasePrototypes<MeshPrototype>;