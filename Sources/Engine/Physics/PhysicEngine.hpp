#include <Engine/Physics/Box2D/box2d.h>

#include <cstdint>

class PhysicEngine
{
public:
    PhysicEngine();
    ~PhysicEngine();

    void SetFramerate(float framerate);
    void SetGravity(float x, float y);

    b2Body* CreateBody(const b2BodyDef& bodyDefinition);
    void DestroyBody(b2Body* body);

    void Update(std::uint32_t velocityIterations = 1, std::uint32_t positionIterations = 1);
private:
    b2Vec2 m_gravity = { 0, 10.f };
    b2World* m_world = nullptr;
    float m_framerate = 1 / 60.f;
};