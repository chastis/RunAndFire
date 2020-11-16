#pragma once

#include <Utility/Core/StringId.hpp>

#include <type_traits>

using TypeId = StringId;

inline TypeId GetTypeId(const std::string& type_name)
{
    return TypeId(type_name);
}

class DynamicType
{
public:
    virtual TypeId GetDynamicType() const = 0;
};

#define DECLARE_DYNAMIC_TYPE(TypeName)                                                      \
private:                                                                                    \
    inline static const TypeId ms_typeId = GetTypeId(#TypeName);                            \
public:                                                                                     \
    static TypeId GetStaticType()                                                           \
    {                                                                                       \
        return ms_typeId;                                                                   \
    }                                                                                       \
                                                                                            \
    virtual const TypeId& GetDynamicType() const override                                   \
    {                                                                                       \
        return ms_typeId;                                                                   \
    }