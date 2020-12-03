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
        }
    case EGameMode::Menu: break;
    default: ;
    }
}

void Engine::Update(float deltaTime)
{
    std::vector<Entity*> entities = EntityManager::GetInstanceRef().GetEntities();
    for (auto en : entities)
    {
        en->Update(deltaTime);
        if (const auto enMeshComp = en->GetComponent<MeshComponent>())
        {
            m_renderTargetWeak.lock()->draw(*enMeshComp, en->getTransform());
        }
    }
#if defined(DEBUG)
    m_debug->Update(deltaTime);
#endif //DEBUG
}