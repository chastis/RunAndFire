#pragma once

#include <Utility/Core/Noncopyable.hpp>
#include <Utility/XML/pugixml.hpp>
#include <Utility/Debugging/Assert.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <memory>

template <class T>
class BasePrototypes;

class BasePrototype
{
public:
    [[nodiscard]] size_t GetID() const
    {
        return id;
    }
    [[nodiscard]] const std::string& GetSID() const
    {
        return sid;
    }
    bool operator==(const BasePrototype& prototype) const
    {
        return id == prototype.id;
    }
    void Init(const pugi::xml_node& node)
    {
        sid = node.name();
        InitSpecific(node);
    }
protected:
    virtual void InitSpecific(const pugi::xml_node& node){}// = 0;

    size_t id = 0;
    std::string sid;

    template <class T>
    friend class BasePrototypes;
};

template <class T>
class BasePrototypes : public Noncopyable
{
public:
    static void Init(std::ifstream& file);
    static const T& GetDefault();
    static const T& Get(size_t inID);
    static const T& Get(const std::string& inSID);
    static size_t Size();

protected:
    static std::vector<std::unique_ptr<T>> prototypes;
};

template <class T>
std::vector<std::unique_ptr<T>> BasePrototypes<T>::prototypes;

template <class T>
void BasePrototypes<T>::Init(std::ifstream& file)
{
    using namespace std::string_literals;

    pugi::xml_document xml_doc;
    xml_doc.load(file);

    uint32_t currentId = 0;
    for (pugi::xml_node child : xml_doc.first_child().children())
    {
        std::unique_ptr<T> newPrototype = std::make_unique<T>();
        if (const pugi::xml_attribute& parent = child.attribute("parent"))
        {
            std::string query = xml_doc.first_child().name() + "/"s + parent.as_string()+ "";
            pugi::xpath_node parentNode = xml_doc.select_node(query.data());
            if (parentNode)
            {
                newPrototype->Init(parentNode.node());
            }
        }
        newPrototype->Init(child);
        newPrototype->id = currentId++;
        prototypes.push_back(std::move(newPrototype));
        
    }

    file.close();
}

template <class T>
const T& BasePrototypes<T>::GetDefault()
{
    if (prototypes.size() == 0)
    {
        std::unique_ptr<T> defaultPrototype = std::make_unique<T>();
        prototypes.push_back(std::move(defaultPrototype));
    }
    return *prototypes[0];
}

template <class T>
const T& BasePrototypes<T>::Get(size_t inID)
{
    if (inID >=0 && inID < prototypes.size())
    {
        if (prototypes[inID] && prototypes[inID]->GetID()==inID)
        {
            return *prototypes[inID];
        }
    }
    M42_ASSERT(false, "Don't exist prototype with this ID");
    return GetDefault();
}

template <class T>
const T& BasePrototypes<T>::Get(const std::string& inSID)
{
    for (const auto& el : prototypes)
    {
        if (el && el->GetSID() == inSID)
        {
            return *el;
        }
    }
    M42_ASSERT(false, "Don't exist prototype with this SID");
    return GetDefault();
}

template <class T>
size_t BasePrototypes<T>::Size()
{
    return prototypes.size();
}

