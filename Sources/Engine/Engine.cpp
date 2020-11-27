#include <Engine/Engine.hpp>
#include <Engine/InputSystem/InputClient.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

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
    InitializeInputManager();
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

InputManager& Engine::GetPrimaryInputManagerRef()
{
    return m_inputManager;
}

void Engine::InitializeInputManager()
{
    //TODO MB: query file from file managers

    pugi::xml_document actionMapsDoc;
    actionMapsDoc.load_file("action_maps.xml");

    InputManager::LoadActionMaps(actionMapsDoc);
}
