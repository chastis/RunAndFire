#pragma once

#include <Engine/Map/tileson.hpp>

class ITileObject
{
public:
    void InitFromTileObject(const tson::Object& object);
    
    const tson::Object& GetTileObject() const;
protected:
    virtual void InitFromTileObjectSpecific() {};
    const tson::Object* m_objectWrapper = nullptr; 
};

