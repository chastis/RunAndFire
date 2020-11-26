#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

#include <SFML/Graphics/CircleShape.hpp>

#include <memory>

class Engine final
{
public:
    Engine();
    ~Engine();

    void Initialize(const std::weak_ptr<sf::RenderTarget>& renderTarget);
    void Shutdown();

    void Update(float deltaTime);

private:
    std::weak_ptr<sf::RenderTarget> m_renderTargetWeak;

    sf::CircleShape m_shape;
};