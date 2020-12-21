#include <Game/Components/UITileComponent.hpp>
#include <Game/Events/GameEvents.hpp>
#include <Engine/Components/PhysicBodyComponent.hpp>
#include <Engine/Components/MeshComponent.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Physics/Box2D/box2d.h>
#include <Engine/EventSystem/EventDispatcher.hpp>
#include <Engine/Engine.hpp>
#include <Game/Managers/GameManager.hpp>
#include <Game/Prototypes/UITilePrototype.hpp>
#include <Engine/Managers/EntityManager.hpp>
#include <Engine/Components/TextComponent.hpp>

UITileComponent::UITileComponent()
{
    m_prototypeWrapper = std::move(std::make_unique<IPrototypeWrapper<UITilePrototype>>());
}

void UITileComponent::Update(float deltaTime)
{
    auto textComp = GetOwnerRef().GetComponent<TextComponent>();
    if (textComp)
    {
        if (m_active)
        {
            textComp->setOutlineThickness(1.f);
        }
        else
        {
            textComp->setOutlineThickness(0.f);
        }
    }
    
}

void UITileComponent::InitFromPrototypeSpecific()
{
    const auto& prototype = GetPrototype<UITilePrototype>();
    m_nextSID = prototype.GetNext();
    m_prevSID = prototype.GetPrev();
    m_active = prototype.IsActive();

    if (prototype.GetAction() == "start")
    {
        m_action = [&]()
        {
            auto& engine = GameManager::GetInstanceRef().GetEngineInstanceRef();
            engine.RequestChangeScene("Map1");
        };
    }
    if (prototype.GetAction() == "tutorial")
    {
        m_action = [&]()
        {
            auto& engine = GameManager::GetInstanceRef().GetEngineInstanceRef();
            engine.RequestChangeScene("Tutorial");
        };
    }
    else if (prototype.GetAction() == "exit")
    {
        m_action = [&]()
        {
            std::shared_ptr<Event> applicationEvent = std::make_shared<EngineEvents::Closed>();
            EventSystem::Broadcast(applicationEvent, EngineEventChannel::GetInstance());
        };
    }
    else if (prototype.GetAction() == "to_menu")
    {
        m_action = [&]()
        {
            auto& engine = GameManager::GetInstanceRef().GetEngineInstanceRef();
            engine.RequestChangeScene("Menu");
        };
    }
}

void UITileComponent::PostInitSpecific()
{
    auto textComp = GetOwnerRef().GetComponent<TextComponent>();
    if (textComp)
    {
        textComp->setOutlineColor(sf::Color(156, 60, 194));
    }
    else
    {
        M42_ASSERT(false, "");
    }
}

bool UITileComponent::HandleInput(const ActionSignal& signal)
{
    if (!m_active)
    {
        return false;
    }
    if (signal == ActionSignal("ui_action"))
    {
        m_action();
    }
    if (signal == ActionSignal("ui_next"))
    {
        Entity* NextEntity = EntityManager::GetInstanceRef().GetEntityBySID(m_nextSID);
        if (NextEntity)
        {
            auto uiTileComp = NextEntity->GetComponent<UITileComponent>();
            if (uiTileComp)
            {
                ToggleActive(false);
                uiTileComp->ToggleActive(true);
                return true;
            }
        }
    }
    if (signal == ActionSignal("ui_prev"))
    {
        Entity* NextEntity = EntityManager::GetInstanceRef().GetEntityBySID(m_prevSID);
        if (NextEntity)
        {
            auto uiTileComp = NextEntity->GetComponent<UITileComponent>();
            if (uiTileComp)
            {
                ToggleActive(false);
                uiTileComp->ToggleActive(true);
                return true;
            }
        }
    }
    return false;  
}

void UITileComponent::ToggleActive(bool active)
{
    m_active = active;
}
