#pragma once

#include <Engine/Prototypes/BasePrototype.hpp>
#include <Engine/Physics/Box2D/b2_fixture.h>
#include <Engine/Physics/Box2D/b2_body.h>
#include <Engine/Physics/Box2D/b2_polygon_shape.h>
#include <Engine/Static/Const.hpp>

#include <vector>
#include <memory>

class PhysicBodyPrototype : public BasePrototype
{
public:
    void InitSpecific(const pugi::xml_node &node) override
    {
        if (const auto bodyDefNode = node.child("body_definition"))
        {
            ParseBodyDef(bodyDefNode);
        }
        if (const auto childNode = node.child("fixtures"))
        {
            ParseFixtures(childNode);
        }
    }

    const b2BodyDef &GetBodyDefinition() const { return m_bodyDefinition; }
    const std::vector<std::unique_ptr<b2FixtureDef>>& GetFixtures() const { return m_fixtures; }

    bool ShouldInitFromMesh() const { return m_initFromMesh; }

private:
    void ParseFixtures(const pugi::xml_node &node)
    {
        m_initFromMesh = node.attribute("init_from_mesh").as_bool();
        if (!m_initFromMesh)
        {
            for (auto fixtureNode : node.children("fixture"))
            {
                auto& fixture = m_fixtures.emplace_back(std::make_unique<b2FixtureDef>());
                fixture->density = fixtureNode.attribute("density").as_float();
                fixture->friction = fixtureNode.attribute("friction").as_float();
                fixture->isSensor = fixtureNode.attribute("is_sensor").as_bool();

                std::vector<b2Vec2> vertices;
                for (auto verticeNode : fixtureNode.child("vertices").children("vertice"))
                {
                    auto& vertice = vertices.emplace_back();
                    vertice.x = verticeNode.attribute("x").as_float() / 2 / Const::PixelPerUnit;
                    vertice.y = verticeNode.attribute("y").as_float() / 2 / Const::PixelPerUnit;
                }
                auto& shape = m_shapes.emplace_back(std::make_unique<b2PolygonShape>());
                shape->Set(vertices.data(), int32_t(vertices.size()));
                fixture->shape = shape.get();
            }
        }
    }

    void ParseBodyDef(const pugi::xml_node &node)
    {
        m_bodyDefinition.type = (node.attribute("is_static").as_bool() ? b2_staticBody : b2_dynamicBody);
        m_bodyDefinition.fixedRotation = node.attribute("lock_rotation").as_bool();
    }

protected:
    std::vector<std::unique_ptr<b2FixtureDef>> m_fixtures;
    std::vector<std::unique_ptr<b2PolygonShape>> m_shapes; //Need this to initialize fixtures on demand

    bool m_initFromMesh = false;
    b2BodyDef m_bodyDefinition;
};

using PhysicBodyPrototypes = BasePrototypes<PhysicBodyPrototype>;