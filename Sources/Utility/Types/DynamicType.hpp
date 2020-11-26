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
private:
    inline static const TypeId ms_typeId = GetTypeId("DynamicType");
public:
    virtual const TypeId& GetDynamicType() const;
    virtual bool IsKindOf(const TypeId& type) const;
protected:
    virtual ~DynamicType() = default;
};

#define DECLARE_DYNAMIC_TYPE(TypeName, ParentName)                                          \
private:                                                                                    \
    using Base = ParentName;                                                                \
    inline static const TypeId ms_typeId = GetTypeId(#TypeName);                            \
public:                                                                                     \
    static constexpr const TypeId& GetStaticType()                                          \
    {                                                                                       \
        return ms_typeId;                                                                   \
    }                                                                                       \
                                                                                            \
    virtual const TypeId& GetDynamicType() const override                                   \
    {                                                                                       \
        return ms_typeId;                                                                   \
    }                                                                                       \
                                                                                            \
    virtual bool IsKindOf(const TypeId& type) const override                                \
    {                                                                                       \
        if (type == ms_typeId) return true;                                                 \
        return Base::IsKindOf(type);                                                        \
    }
