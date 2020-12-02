#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>

class MeshPrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node& node) override
    {
        if (const auto childNode = node.child("mesh_path"))
        {
            if (const auto value = childNode.attribute("value"))
            {
                m_meshPath = value.as_string();
            }
            else
            {
                M42_ASSERT(false, "There is no value for mesh_path");
            }
        }
    }
    [[nodiscard]] const std::string& GetMeshMath() const
    {
        return m_meshPath;
    }
protected:
    std::string m_meshPath;
};

using MeshPrototypes = BasePrototypes<MeshPrototype>;