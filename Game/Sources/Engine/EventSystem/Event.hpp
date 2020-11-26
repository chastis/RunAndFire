#pragma once

#include <Utility/Types/DynamicType.hpp>

class Event : public DynamicType
{
public:
    DECLARE_DYNAMIC_TYPE(Event, DynamicType)
public:
    virtual ~Event() = default;
};