#pragma once

#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/BaseComponent.hpp>
#include <Engine/Entity/EntityEvents.hpp>
#include <Engine/InputSystem/InputClient.hpp>
#include <Engine/InputSystem/ActionMap.hpp>


class UITileComponent : public BaseComponent, public InputClient
{
    DECLARE_DYNAMIC_TYPE(UITileComponent, BaseComponent)
public:
    UITileComponent();

    void Update(float deltaTime) override;
    bool HandleInput(const ActionSignal& signal) override;
    void ToggleActive(bool active);
private:
    void InitFromPrototypeSpecific() override;
    void PostInitSpecific() override;
    std::string m_nextSID;
    std::string m_prevSID;
    std::function<void()> m_action;
    bool m_active = false;
};
