#include <Game/Components/PlayerControllerComponent.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Entity/Entity.hpp>

void PlayerControllerComponent::InitFromPrototype()
{
    m_speed = GetPrototype().GetSpeed();
}

void PlayerControllerComponent::Update(float deltaTime)
{
    const auto delta = m_speed * m_direction.getNormilized() * deltaTime;
    m_physicComponent->SetLinearVelocity(delta.x, delta.y);

    if (m_direction.x < 0.f)
    {
        SetMeshScale(-1.f, 1.f);
    }
    else if (m_direction.x > 0.f)
    {
        SetMeshScale(1.f, 1.f);
    }
}

bool PlayerControllerComponent::HandleInput(const ActionSignal& signal)
{
    if (signal == ActionSignal("move_up"))
    {
        m_direction.y += -1.f;
    }
    if (signal == ActionSignal("move_down"))
    {
        m_direction.y += 1.f;
    }
    if (signal == ActionSignal("move_left"))
    {
        m_direction.x += -1.f;
        if (m_direction.x < 0.f)
        {
           SetMeshScale(-1.f, 1.f);
        }
    }
    if (signal == ActionSignal("move_right"))
    {
        m_direction.x += 1.f;
        if (m_direction.x > 0.f)
        {
            SetMeshScale(1.f, 1.f);
        }
    }
    if (signal == ActionSignal("stop_move_up"))
    {
        m_direction.y -= -1.f;
    }
    if (signal == ActionSignal("stop_move_down"))
    {
        m_direction.y -= 1.f;
    }
    if (signal == ActionSignal("stop_move_left"))
    {
        m_direction.x -= -1.f;
    }
    if (signal == ActionSignal("stop_move_right"))
    {
        m_direction.x -= 1.f;
    }
    return false;
}

void PlayerControllerComponent::PostInitSpecific()
{
    m_physicComponent = GetOwnerRef().GetComponent<PhysicBodyComponent>();
}
