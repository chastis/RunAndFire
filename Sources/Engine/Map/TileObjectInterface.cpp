#include <Engine/Map/TileObjectInterface.hpp>
#include <Utility/Debugging/Assert.hpp>

void ITileObject::InitFromTileObject(const tson::Object& object)
{
    m_objectWrapper = &object;
    InitFromTileObjectSpecific();
}

const tson::Object& ITileObject::GetTileObject() const
{
    M42_ASSERT(m_objectWrapper, "nullptr");
    return *m_objectWrapper;
}
