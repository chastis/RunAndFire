#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/Prototypes/CollisionPrototype.hpp>
#include <SFML/Graphics/Rect.hpp>

class CollisionComponent : public PrototypeableBaseComponent<CollisionPrototype>
{
    DECLARE_DYNAMIC_TYPE(CollisionComponent, PrototypeableBaseComponent<CollisionPrototype>)
public:
    void InitFromPrototype() override;
    void Update(float deltaTime) override;

    [[nodiscard]] bool CheckCollision(float x, float y) const;
    [[nodiscard]] bool CheckCollision(sf::Vector2f point) const;
    [[nodiscard]] bool CheckCollision(const CollisionComponent& collider) const;
    [[nodiscard]] sf::FloatRect GetIntersection(const CollisionComponent& collider) const;
    static bool CheckCollision(const CollisionComponent& first, const CollisionComponent& second);
    static sf::FloatRect FindIntersection(const CollisionComponent& first, const CollisionComponent& second);
    [[nodiscard]] const sf::FloatRect& GetLocalCollisionBox() const;
    [[nodiscard]] sf::FloatRect GetWorldCollisionBox() const;
protected:
    void PostInitSpecific() override;
    sf::FloatRect m_collisionBox;
};
