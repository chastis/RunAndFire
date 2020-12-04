#include <Engine/Engine.hpp>
#include <Engine/InputSystem/InputManager.hpp>
#include <Engine/Factories/DynamicTypeFactory.hpp>
#include <Engine/Managers/EntityManager.hpp>
#include <Engine/Components/MeshComponent.hpp>

#if defined(DEBUG)
#include <Engine/Debugging/Engine_Debug.hpp>
#endif

Engine::Engine()
#if defined(DEBUG)
    : m_debug(*this)
#endif
{
}

Engine::~Engine()
{
}

void Engine::Initialize(const std::weak_ptr<sf::RenderTarget>& renderTarget)
{
    m_renderTargetWeak = renderTarget;

    ChangeGameMode(EGameMode::Game);

#if defined(DEBUG)
    m_debug->Initialize();
#endif //DEBUG
}

void Engine::Draw()
{
    m_scenes.top().Draw();
}

void Engine::Shutdown()
{
    EntityManager::GetInstanceRef().DeleteAllEntities();
#if defined(DEBUG)
    m_debug->Shutdown();
#endif //DEBUG
}

void Engine::ChangeGameMode(EGameMode newMode)
{
    switch (newMode)
    {
    case EGameMode::Game:
        {
            InputManager::GetInstanceRef().PushActionMap("game_input");
            Scene scene;
            scene.Initialize(m_renderTargetWeak);
            scene.InitFromPrototype();
            m_scenes.push(scene);
        }
    case EGameMode::Menu: break;
    default: ;
    }
}

void Engine::Update(float deltaTime)
{
    m_scenes.top().Update(deltaTime);
#if defined(DEBUG)
    m_debug->Update(deltaTime);
#endif //DEBUG
}