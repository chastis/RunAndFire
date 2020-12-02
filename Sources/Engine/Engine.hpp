#pragma once

#include <Engine/InputSystem/InputManager.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <memory>

#if defined(DEBUG)
#include <Utility/Core/FastPimpl.hpp>
#endif

enum class EGameMode
{
    Game,
    Menu
};

class Engine final
{
public:
    Engine();
    ~Engine();

    void Initialize(const std::weak_ptr<sf::RenderTarget>& renderTarget);
    void Shutdown();
    void ChangeGameMode(EGameMode newMode);
    void Update(float deltaTime);

private:
    std::weak_ptr<sf::RenderTarget> m_renderTargetWeak;

#if defined(DEBUG)
    class Debug;
    FastPimpl<Debug, 16, 8> m_debug;
#endif
};