#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/Prototypes/CollisionPrototype.hpp>
#include <Engine/Physics/Box2D/b2_body.h>
#include <Engine/Physics/Box2D/b2_fixture.h>
#include <SFML/Graphics/Rect.hpp>

class CollisionComponent : public PrototypeableBaseComponent<CollisionPrototype>
{
    DECLARE_DYNAMIC_TYPE(CollisionComponent, PrototypeableBaseComponent<CollisionPrototype>)
public:
    ~CollisionComponent();

    void InitFromPrototype() override;
    void Update(float deltaTime) override;

    const b2BodyDef& GetBodyDefinition() const;
    const std::vector<b2FixtureDef>& GetBodyFixtures() const;

#if defined(DEBUG)
    void AddFixture(const b2FixtureDef& fixture) { m_fixtures.push_back(fixture); }
    void SetBodyDefinition(const b2BodyDef& bodyDef) { m_bodyDefinition = bodyDef; }
#endif //DEBUG
private:
    void CreateFixture(float w, float h);
    void PostInitSpecific() override;

    std::vector<b2FixtureDef> m_fixtures;
    b2BodyDef m_bodyDefinition;
};


//class CollisionComponent : public PrototypeableBaseComponent<CollisionPrototype>
//{
//    DECLARE_DYNAMIC_TYPE(CollisionComponent, PrototypeableBaseComponent<CollisionPrototype>)
//public:
//    void InitFromPrototype() override;
//    void Update(float deltaTime) override;
//
//    [[nodiscard]] bool CheckCollision(float x, float y) const;
//    [[nodiscard]] bool CheckCollision(sf::Vector2f point) const;
//    [[nodiscard]] bool CheckCollision(const CollisionComponent& collider) const;
//    [[nodiscard]] sf::FloatRect GetIntersection(const CollisionComponent& collider) const;
//    static bool CheckCollision(const CollisionComponent& first, const CollisionComponent& second);
//    static sf::FloatRect FindIntersection(const CollisionComponent& first, const CollisionComponent& second);
//    [[nodiscard]] const sf::FloatRect& GetLocalCollisionBox() const;
//    [[nodiscard]] sf::FloatRect GetWorldCollisionBox() const;
//protected:
//    void PostInitSpecific() override;
//    sf::FloatRect m_collisionBox;
//};
