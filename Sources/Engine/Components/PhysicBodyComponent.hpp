#pragma once

#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Prototypes/PhysicBodyPrototype.hpp>

class MeshComponent;
class PhysicEngine;
class b2Body;
struct b2FixtureDef;

class PhysicBodyComponent : public PrototypeableBaseComponent<PhysicBodyPrototype>
{
    DECLARE_DYNAMIC_TYPE(PhysicBodyComponent, PrototypeableBaseComponent<PhysicBodyPrototype>)
public:
    PhysicBodyComponent() = default;
    ~PhysicBodyComponent();

    void InitFromPrototype() override;
    void Update(float deltaTime) override;

    void BindToPhysicEngine(PhysicEngine* engine);

    void SetLinearVelocity(float x, float y);
private:
    void PostInitSpecific() override;
    void InitFromMesh(MeshComponent* mesh);

    void CreateFixture(const b2FixtureDef& fixtureDef);
private:
    PhysicEngine* m_engine = nullptr;
    b2Body* m_body = nullptr;
};