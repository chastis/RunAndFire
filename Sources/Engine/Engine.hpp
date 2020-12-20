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

    void Initialize(sf::RenderTarget* renderTarget);
    void Draw();
    void Shutdown();
    void Update(float deltaTime);
    void RequestChangeGameMode(EGameMode gameMode, const std::string& input, const std::string& map);
    Scene* GetCurrentScene();
    sf::RenderTarget* GetRenderTarget() const;
private:
    void OnComponentCreatedEvent(EntityEvents::ComponentCreatedEvent& event);
    void ChangeGameMode(EGameMode newMode, const std::string& input);
private:
    sf::RenderTarget* m_renderTargetWeak;
    std::stack<std::unique_ptr<Scene>> m_scenes;
    PhysicEngine m_physicEngine;
    EventHandler m_eventHandler;

    struct RequestParam
    {
        std::string map;
        std::string input;
        EGameMode gameMode;
    };
    std::optional<RequestParam> m_requestedData;

#if defined(DEBUG)
    class Debug;
    FastPimpl<Debug, 8, 8> m_debug;
#endif
};