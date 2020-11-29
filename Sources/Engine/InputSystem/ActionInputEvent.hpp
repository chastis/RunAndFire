#pragma once

#include <SFML/Window/Event.hpp>

enum class ActionInputEventType
{
    Nones,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased
};

struct ActionSignalEvent
{
    ActionInputEventType type;
    int value = 0;
};

#define BEGIN_ACTION_INPUT_EVENT_DESCRIPTION() inline const char* GetActionInputEventPrefix(ActionInputEventType action_event) { switch(action_event){
#define DECLARE_ACTION_INPUT_TYPE(type, prefix) case type: return prefix;
#define END_ACTION_INPUT_EVENT_DESCRIPTION() default: return nullptr;}}

BEGIN_ACTION_INPUT_EVENT_DESCRIPTION()
    DECLARE_ACTION_INPUT_TYPE(ActionInputEventType::KeyPressed,             "kp")
    DECLARE_ACTION_INPUT_TYPE(ActionInputEventType::KeyReleased,            "kr")
    DECLARE_ACTION_INPUT_TYPE(ActionInputEventType::MouseButtonPressed,     "mbp")
    DECLARE_ACTION_INPUT_TYPE(ActionInputEventType::MouseButtonReleased,    "mbr")
END_ACTION_INPUT_EVENT_DESCRIPTION()
