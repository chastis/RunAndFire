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

void PhysicBodyComponentBase::SetFixtures(sf::Vector2f origin, const std::vector<sf::Vector2f>& vertices)
{
    M42_ASSERT(m_body, "there is no body");
    b2FixtureDef fixtureDef;
    fixtureDef.density = Const::DefaultDensity;
    fixtureDef.friction = Const::DefaultFriction;
    fixtureDef.userData.pointer = (uintptr_t)GetOwner();

    std::vector<b2Vec2> b2vertices;
    const sf::Vector2f shift = GetOwnerRef().getOrigin() - origin;
    for (const auto& verticeNode : vertices)
    {
        auto& vertice = b2vertices.emplace_back();
        vertice.x = (verticeNode.x - shift.x) / Const::PixelPerUnit;
        vertice.y = (verticeNode.y - shift.y) / Const::PixelPerUnit;
    }
    b2PolygonShape shape;
    shape.Set(b2vertices.data(), int32_t(b2vertices.size()));
    //shape.SetAsBox(vertices[3].x / 2 / Const::PixelPerUnit, vertices[3].y / 2 / Const::PixelPerUnit);
    fixtureDef.shape = &shape;
    m_body->CreateFixture(&fixtureDef);
}

void PhysicBodyComponentBase::PostInitSpecific()
{
    M42_ASSERT(m_engine, "Bind physic engine first!");

    auto entityPosition = GetOwnerRef().getPosition();
    m_bodyDef.position.Set(entityPosition.x / Const::PixelPerUnit, entityPosition.y / Const::PixelPerUnit);
    m_body = m_engine->CreateBody(m_bodyDef);
    M42_ASSERT(m_body, "Failed to create b2Body!");
}


void PhysicBodyComponentBase::CreateFixture(const b2FixtureDef& fixtureDef)
{
    m_body->CreateFixture(&fixtureDef);
}

PhysicBodyComponent::~PhysicBodyComponent()
{
    m_engine->DestroyBody(m_body);
}

void PhysicBodyComponent::InitPrototype(const std::string& prototypeName)
{
    this->SetPrototype(prototypeName);
    this->InitFromPrototype();
    m_status = EComponentStatus::PostPrototypeInit;
}

void PhysicBodyComponent::InitPrototype(size_t prototypeID)
{
    this->SetPrototype(prototypeID);
    this->InitFromPrototype();
    m_status = EComponentStatus::PostPrototypeInit;
}

void PhysicBodyComponent::InitFromPrototype()
{
    const auto& prototype = GetPrototype();
    m_bodyDef = prototype.GetBodyDefinition();
    auto entityPosition = GetOwnerRef().getPosition();
    m_bodyDef.position.Set(entityPosition.x / Const::PixelPerUnit, entityPosition.y / Const::PixelPerUnit);
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
    if (GetPrototype().ShouldInitFromMesh())
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

        m_body->CreateFixture(&fixtureDef);
    }
}