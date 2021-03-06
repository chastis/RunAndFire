#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Physics/PhysicEngine.hpp>
#include <Engine/Physics/Box2D/box2d.h>
#include <Utility/Debugging/Assert.hpp>

PhysicBodyComponentBase::~PhysicBodyComponentBase()
{
    m_engine->DestroyBody(m_body);
}

void PhysicBodyComponentBase::Update(float deltaTime)
{
    sf::Transformable* m_ownerTransform = GetOwner();
    auto bodyPosition = m_body->GetPosition();
    m_ownerTransform->setPosition(bodyPosition.x * Const::PixelPerUnit, bodyPosition.y * Const::PixelPerUnit);
    m_ownerTransform->move(m_ownerTransform->getOrigin());
    m_ownerTransform->setRotation(m_body->GetAngle() * 180 / b2_pi);
}

void PhysicBodyComponentBase::BindToPhysicEngine(PhysicEngine* engine)
{
    m_engine = engine;
}

void PhysicBodyComponentBase::SetLinearVelocity(float x, float y)
{
    m_body->SetLinearVelocity({ x, y });
}

void PhysicBodyComponentBase::ApplyImpulse(float x, float y)
{
    m_body->ApplyLinearImpulseToCenter({ x, y }, true);
}

float PhysicBodyComponentBase::GetMass() const
{
    return m_body->GetMass();
}

b2Fixture* PhysicBodyComponentBase::GetFixtures()
{
    return m_body->GetFixtureList();
}

const b2Fixture* PhysicBodyComponentBase::GetFixtures() const
{
    return m_body->GetFixtureList();
}

sf::Vector2f PhysicBodyComponentBase::GetLinearVelocity() const
{
    auto velocity = m_body->GetLinearVelocity();
    return { velocity.x, velocity.y };
}

Entity* PhysicBodyComponentBase::RayCastGetEntity(sf::Vector2f point, bool fromMeshOrigin) const
{
    const sf::Vector2f casterOriginPosition = GetOwnerRef().getPosition() - GetOwnerRef().getOrigin();
    sf::Vector2f start = casterOriginPosition;
    sf::Vector2f finish = point - GetOwnerRef().getOrigin();
    if (fromMeshOrigin)
    {
        if (const auto meshComponent = GetOwnerRef().GetKindOfComponent<MeshComponentBase>())
        {
            start += meshComponent->getOrigin();
            finish += meshComponent->getOrigin();
        }
    }
    return m_engine->RayCastGetEntity(GetOwner(), start, finish);
}

void PhysicBodyComponentBase::SetFixtures(sf::Vector2f origin, const std::vector<sf::Vector2f>& vertices)
{
    M42_ASSERT(m_body, "there is no body");
    b2FixtureDef fixtureDef;
    fixtureDef.density = Const::DefaultDensity;
    fixtureDef.friction = Const::DefaultFriction;
    fixtureDef.userData.pointer = (uintptr_t)GetOwner();

    std::vector<b2Vec2> b2vertices;
    const sf::Vector2f shift = -origin;//GetOwnerRef().getOrigin() - origin;
    for (const auto& verticeNode : vertices)
    {
        auto& vertice = b2vertices.emplace_back();
        vertice.x = (verticeNode.x - shift.x) / Const::PixelPerUnit;
        vertice.y = (verticeNode.y - shift.y) / Const::PixelPerUnit;
    }
    b2PolygonShape shape;
    shape.Set(b2vertices.data(), int32_t(b2vertices.size()));
    fixtureDef.shape = &shape;
    CreateFixture(fixtureDef);
}

void PhysicBodyComponentBase::SetGravityScale(float scale)
{
    m_body->SetGravityScale(scale);
}

b2Body* PhysicBodyComponentBase::GetBody() const
{
    return m_body;
}

void PhysicBodyComponentBase::PostInitSpecific()
{
    M42_ASSERT(m_engine, "Bind physic engine first!");

    auto entityPosition = GetOwnerRef().getPosition() - GetOwnerRef().getOrigin();
    m_bodyDef.position.Set(entityPosition.x / Const::PixelPerUnit, entityPosition.y / Const::PixelPerUnit);
    m_body = m_engine->CreateBody(m_bodyDef);
    M42_ASSERT(m_body, "Failed to create b2Body!");
}


void PhysicBodyComponentBase::CreateFixture(const b2FixtureDef& fixtureDef)
{
    m_body->CreateFixture(&fixtureDef);
}

PhysicBodyComponent::PhysicBodyComponent()
{
    m_prototypeWrapper = std::move(std::make_unique<IPrototypeWrapper<PhysicBodyPrototype>>());
}

void PhysicBodyComponent::InitFromPrototypeSpecific()
{
    const auto& prototype = GetPrototype<PhysicBodyPrototype>();
    m_bodyDef = prototype.GetBodyDefinition();
    for (const auto& fixture : prototype.GetFixtures())
    {
        auto fixtureTemp = *fixture;
        fixtureTemp.userData.pointer = (uintptr_t)GetOwner();
        m_body->CreateFixture(fixture.get());
    }
}


void PhysicBodyComponent::PostInitSpecific()
{
    PhysicBodyComponentBase::PostInitSpecific();
    if (m_prototypeWrapper && GetPrototype<PhysicBodyPrototype>().ShouldInitFromMesh())
    {
        auto meshComponent = GetOwnerRef().GetComponent<MeshComponent>();
        M42_ASSERT(meshComponent, "No mesh to initialize physic component!");
        InitFromMesh(meshComponent);
    }
}

void PhysicBodyComponent::InitFromMesh(MeshComponent* mesh)
{
    M42_ASSERT(m_body, "create body first");

    b2FixtureDef fixtureDef;

    const auto tileCollisionData = mesh->GetTileCollisionParamData();
    if (tileCollisionData)
    {
        SetFixtures(tileCollisionData->m_origin, tileCollisionData->m_vertices);
    }
    else
    {
        const auto meshSize = mesh->getLocalBounds();
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(meshSize.width / 2 / Const::PixelPerUnit, meshSize.height / 2 / Const::PixelPerUnit);
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = Const::DefaultDensity;
        fixtureDef.friction = Const::DefaultFriction;
        fixtureDef.userData.pointer = (uintptr_t)GetOwner();

        CreateFixture(fixtureDef);
    }
}
