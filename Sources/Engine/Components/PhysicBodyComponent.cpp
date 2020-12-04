#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Physics/PhysicEngine.hpp>
#include <Engine/Physics/Box2D/box2d.h>
#include <Utility/Debugging/Assert.hpp>

PhysicBodyComponent::~PhysicBodyComponent()
{
    m_engine->DestroyBody(m_body);
}

void PhysicBodyComponent::InitFromPrototype()
{
    M42_ASSERT(m_engine, "Bind physic engine first!");
    const auto& prototype = GetPrototype();

    auto bodyDef = prototype.GetBodyDefinition();
   
    auto entityPosition = GetOwnerRef().getPosition();
    bodyDef.position.Set(entityPosition.x / Const::PixelPerUnit, entityPosition.y / Const::PixelPerUnit);

    m_body = m_engine->CreateBody(bodyDef);
    M42_ASSERT(m_body, "Failed to create b2Body!");
    for (const auto& fixture : prototype.GetFixtures())
    {
        auto fixtureTemp = *fixture;
        fixtureTemp.userData.pointer = (uintptr_t)GetOwner();
        m_body->CreateFixture(fixture.get());
    }
}

void PhysicBodyComponent::Update(float deltaTime)
{
    sf::Transformable* m_ownerTransform = GetOwner();

    auto bodyPosition = m_body->GetPosition();
    m_ownerTransform->setPosition(bodyPosition.x * Const::PixelPerUnit, bodyPosition.y * Const::PixelPerUnit);
    m_ownerTransform->setRotation(m_body->GetAngle() * 180 / b2_pi);

}

void PhysicBodyComponent::BindToPhysicEngine(PhysicEngine* engine)
{
    m_engine = engine;
}

void PhysicBodyComponent::SetLinearVelocity(float x, float y)
{
    m_body->SetLinearVelocity({ x, y });
}

void PhysicBodyComponent::PostInitSpecific()
{
    if (GetPrototype().ShouldInitFromMesh())
    {
        auto meshComponent = GetOwnerRef().GetComponent<MeshComponent>();
        M42_ASSERT(meshComponent, "No mesh to initialize physic component!");
        InitFromMesh(meshComponent);
    }
}

void PhysicBodyComponent::InitFromMesh(MeshComponent* mesh)
{
    auto meshSize = mesh->getLocalBounds();

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(meshSize.width / 2 / Const::PixelPerUnit, meshSize.height / 2 / Const::PixelPerUnit);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.userData.pointer = (uintptr_t)GetOwner();

    CreateFixture(fixtureDef);
}

void PhysicBodyComponent::CreateFixture(const b2FixtureDef& fixtureDef)
{
    m_body->CreateFixture(&fixtureDef);
}
