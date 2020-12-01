#if defined(DEBUG)

#include <Engine/Debugging/EntityComponents_Debug.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

void EntityControllerComponent::SetSpeed(float x, float y)
{
    m_speed = { x, y };
}

void EntityControllerComponent::Update(float deltaTime)
{
    sf::Vector2f move{ 0.f, 0.f };
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        move.y -= 1.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        move.y += 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        move.x -= 1.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move.x += 1.f;
    }

    move.x *= m_speed.x;
    move.y *= m_speed.y;

    m_ownerTransform->move(move * deltaTime);
}

void EntityControllerComponent::InitSpecific()
{
    m_ownerTransform = m_owner;
}



void CircleShapeComponent::SetRenderTarget(sf::RenderTarget* target)
{
    m_renderTarget = target;
}
void CircleShapeComponent::Update(float deltaTime)
{
    sf::RenderStates states;
    states.transform *= GetOwnerRef().getTransform();
    m_renderTarget->draw(m_shape, states);
}

void CircleShapeComponent::InitSpecific()
{
    m_shape.setRadius(25);
    m_shape.setFillColor(sf::Color::Green);
}

#endif //DEBUG