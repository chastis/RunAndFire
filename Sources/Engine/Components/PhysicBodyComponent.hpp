#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PhysicBodyPrototype.hpp>
#include <SFML/System/Vector2.hpp>

class MeshComponent;
class PhysicEngine;
class b2Body;
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
    void SetFixtures(sf::Vector2f origin, const std::vector<sf::Vector2f>& vertices);
protected:
    void PostInitSpecific() override;
    void CreateFixture(const b2FixtureDef& fixtureDef);

    b2BodyDef m_bodyDef;
    PhysicEngine* m_engine = nullptr;
    b2Body* m_body = nullptr;
};

class PhysicBodyComponent : public PhysicBodyComponentBase,  IPrototypeable<PhysicBodyPrototype>
{
    DECLARE_DYNAMIC_TYPE(PhysicBodyComponent, PhysicBodyComponentBase)
public:
    PhysicBodyComponent() = default;
    ~PhysicBodyComponent();

    void InitPrototype(const std::string& prototypeName) override;
    void InitPrototype(size_t prototypeID) override;
    
    void InitFromPrototype() override;
private:
    void PostInitSpecific() override;
    void InitFromMesh(MeshComponent* mesh);
};