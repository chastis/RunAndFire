//#include <Engine/Components/PhysicComponent.hpp>
//#include <Engine/Components/CollisionComponent.hpp>
//#include <Engine/Entity/Entity.hpp>
//#include <Engine/Physics/PhysicEngine.hpp>
//#include <Engine/Physics/Box2D/box2d.h>
//#include <Engine/Static/Const.hpp>
//
//PhysicComponent::~PhysicComponent()
//{
//    m_engine->DestroyBody(m_body);
//}
//
//void PhysicComponent::InitFromPrototype()
//{
//    m_mass = GetPrototype().GetMass();
//    m_isStatic = GetPrototype().IsStatic();
//}
//
//void PhysicComponent::Update(float deltaTime)
//{
//    sf::Transformable* m_ownerTransform = GetOwner();
//
//    auto bodyPosition = m_body->GetPosition();
//    m_ownerTransform->setPosition(bodyPosition.x * PhysicEngine::PixelsPerUnit, bodyPosition.y * PhysicEngine::PixelsPerUnit);
//    m_ownerTransform->setRotation(m_body->GetAngle() * 180 / b2_pi);
//
//}
//
//void PhysicComponent::BindToPhysicEngine(PhysicEngine* engine)
//{
//    m_engine = engine;
//}
//
//void PhysicComponent::SetLinearVelocity(float x, float y)
//{
//    m_body->SetLinearVelocity({ x, y });
//}
//
//void PhysicComponent::PostInitSpecific()
//{
//    M42_ASSERT(m_engine, "Bind physic engine first!");
//    auto collisionComponent = GetOwnerRef().GetComponent<CollisionComponent>();
//    M42_ASSERT(collisionComponent, "PhysicComponent must be used with collision component!");
//
//    auto bodyDefinition = collisionComponent->GetBodyDefinition();
//    bodyDefinition.type = m_isStatic ? b2_staticBody : b2_dynamicBody;
//    m_body = m_engine->CreateBody(bodyDefinition);
//    M42_ASSERT(m_body, "Failed to create b2Body!");
//
//    for (const auto& fixture : collisionComponent->GetBodyFixtures())
//    {
//        m_body->CreateFixture(&fixture);
//    }
//}