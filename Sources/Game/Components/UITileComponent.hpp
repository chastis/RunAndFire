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

    bool HandleInput(const ActionSignal& signal) override;
private:
    void InitFromPrototypeSpecific() override;
    void PostInitSpecific() override;
};
