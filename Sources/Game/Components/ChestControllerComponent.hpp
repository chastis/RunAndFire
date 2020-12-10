#pragma once

#include <Engine/Components/ControllerComponent.hpp>
#include <Engine/Components/BaseComponent.hpp>

class ChestControllerComponent : public ControllerComponent
{
    DECLARE_DYNAMIC_TYPE(ChestControllerComponent, ControllerComponent)
public:
    ChestControllerComponent();

private:
    void InitFromPrototypeSpecific() override;
};
