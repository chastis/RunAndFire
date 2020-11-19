#include <Utility/DynamicType.hpp>

const TypeId& DynamicType::GetDynamicType() const
{
    return ms_typeId;
}

bool DynamicType::IsChildOf(const TypeId& type) const
{
    return ms_typeId == type;
}
