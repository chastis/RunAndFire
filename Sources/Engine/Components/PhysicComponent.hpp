//#pragma once
//
//#include <Engine/Components/BaseComponent.hpp>
//#include <Engine/Prototypes/PrototypeableInterface.hpp>
//#include <Engine/Prototypes/PhysicPrototype.hpp>
//
//class PhysicEngine;
//class b2Body;
//
//class PhysicComponent : public PrototypeableBaseComponent<PhysicPrototype>
//{
//    DECLARE_DYNAMIC_TYPE(PhysicComponent, PrototypeableBaseComponent<PhysicPrototype>)
//public:
//    PhysicComponent() = default;
//    ~PhysicComponent();
//
//    void InitFromPrototype() override;
//    void Update(float deltaTime) override;
//
//    void BindToPhysicEngine(PhysicEngine* engine);
//
//    void SetLinearVelocity(float x, float y);
//private:
//    void PostInitSpecific() override;
//private:
//    PhysicEngine* m_engine = nullptr;
//    b2Body* m_body = nullptr;
//    float m_mass = 0.f;
//    bool m_isStatic = true;
//};