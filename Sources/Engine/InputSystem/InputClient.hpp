#pragma once

#include <Engine/InputSystem/ActionMap.hpp>

class InputClient
{
public:
    virtual bool HandleInput(const ActionSignal& signal) = 0;
protected:
    InputClient();
    virtual ~InputClient();
};