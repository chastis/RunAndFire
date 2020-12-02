#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PrototypeableInterface.hpp>
#include <Engine/Prototypes/CollisionPrototype.hpp>
#include <SFML/Graphics/Rect.hpp>

class CollisionComponent : public BasePrototypeableComponent<CollisionPrototype>
{
    DECLARE_DYNAMIC_TYPE(CollisionComponent, BasePrototypeableComponent<CollisionPrototype>)
public:
    void InitFromPrototype() override;
    void Update(float deltaTime) override;

    [[nodiscard]] bool CheckCollision(float x, float y) const;
    [[nodiscard]] bool CheckCollision(sf::Vector2f point) const;
    [[nodiscard]] bool CheckCollision(const CollisionComponent& collider) const;
    static bool CheckCollision(const CollisionComponent& first, const CollisionComponent& second);
protected:
    sf::FloatRect collisionBox;
};
