#include <Engine/Engine.hpp>
#include <Engine/InputSystem/InputManager.hpp>

#include <Engine/Factories/DynamicTypeFactory.hpp>

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

void Engine::Shutdown()
{
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
        }
    case EGameMode::Menu: break;
    default: ;
    }
}

void Engine::Update(float deltaTime)
{

#if defined(DEBUG)
    m_debug->Update(deltaTime);
#endif //DEBUG
}