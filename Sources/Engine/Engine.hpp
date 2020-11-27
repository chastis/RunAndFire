#pragma once

#include <Engine/InputSystem/InputManager.hpp>

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

    InputManager& GetPrimaryInputManagerRef();

private:
    void InitializeInputManager();
private:
    InputManager m_inputManager;
    std::weak_ptr<sf::RenderTarget> m_renderTargetWeak;

    sf::CircleShape m_shape;
};