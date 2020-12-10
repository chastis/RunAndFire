#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PhysicBodyPrototype.hpp>
#include <SFML/System/Vector2.hpp>

class MeshComponent;
class PhysicEngine;
class b2Body;
class b2Fixture;
struct b2FixtureDef;

class PhysicBodyComponentBase : public BaseComponent
{
    DECLARE_DYNAMIC_TYPE(PhysicBodyComponentBase, BaseComponent)
public:
    PhysicBodyComponentBase() = default;
    virtual ~PhysicBodyComponentBase();

    void Update(float deltaTime) override;

    void BindToPhysicEngine(PhysicEngine* engine);
    void SetLinearVelocity(float x, float y);
    void ApplyImpulse(float x, float y);
    float GetMass() const;

    b2Fixture* GetFixtures();
    const b2Fixture* GetFixtures() const;

    sf::Vector2f GetLinearVelocity() const;

    void SetFixtures(sf::Vector2f origin, const std::vector<sf::Vector2f>& vertices);
protected:
    void PostInitSpecific() override;
    void CreateFixture(const b2FixtureDef& fixtureDef);

    b2BodyDef m_bodyDef;
    PhysicEngine* m_engine = nullptr;
    b2Body* m_body = nullptr;
};

class PhysicBodyComponent : public PhysicBodyComponentBase
{
    DECLARE_DYNAMIC_TYPE(PhysicBodyComponent, PhysicBodyComponentBase)
public:
    PhysicBodyComponent();
    ~PhysicBodyComponent();
    
private:
    void PostInitSpecific() override;
    void InitFromPrototypeSpecific() override;
    void InitFromMesh(MeshComponent* mesh);
};