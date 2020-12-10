#pragma once

#include <Engine/InputSystem/InputManager.hpp>
#include <Engine/Physics/PhysicEngine.hpp>
#include <Engine/Scene/Scene.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <stack>

#if defined(DEBUG)
#include <Utility/Core/FastPimpl.hpp>
#endif

namespace EntityEvents
{
    class ComponentCreatedEvent;
}

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
    void Draw();
    void Shutdown();
    void ChangeGameMode(EGameMode newMode);
    void Update(float deltaTime);
    Scene* GetCurrentScene();
private:
    void OnComponentCreatedEvent(EntityEvents::ComponentCreatedEvent& event);
private:
    std::weak_ptr<sf::RenderTarget> m_renderTargetWeak;
    std::stack<std::unique_ptr<Scene>> m_scenes;
    PhysicEngine m_physicEngine;
    EventHandler m_eventHandler;

#if defined(DEBUG)
    class Debug;
    FastPimpl<Debug, 8, 8> m_debug;
#endif
};