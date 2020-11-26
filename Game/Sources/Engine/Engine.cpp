#include <Engine/Engine.hpp>

#include <SFML/Graphics.hpp>

Engine::Engine()
    : m_shape(100.f)
{
    m_shape.setFillColor(sf::Color::Green);
}

Engine::~Engine()
{
}

void Engine::Initialize(const std::weak_ptr<sf::RenderTarget>& renderTarget)
{
    m_renderTargetWeak = renderTarget;
}

void Engine::Shutdown()
{
}

void Engine::Update(float deltaTime)
{
    if (auto renderTarget = m_renderTargetWeak.lock())
    {
        renderTarget->draw(m_shape);
    }
}
