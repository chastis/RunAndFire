#include <Utility/Types/DynamicType.hpp>

const TypeId& DynamicType::GetDynamicType() const
{
    return ms_typeId;
}

bool DynamicType::IsKindOf(const TypeId& type) const
{
    return ms_typeId == type;
}
