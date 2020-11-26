#pragma once

#include <Engine/Consts/Const.hpp>
#include <Utility/Core/Noncopyable.hpp>
#include <Utility/Json/Json.hpp>
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
    virtual bool Init(const nlohmann::json::iterator& nodeIt)
    {
        nlohmann::json node = nodeIt.value();
        sid = nodeIt.key();
        return true;
    }
protected:
    size_t id = 0;
    std::string sid;

    template <class T>
    friend class BasePrototypes;
};

template <class T>
class BasePrototypes : public Noncopyable
{
public:
    static void Init(const std::string& filePath);
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
void BasePrototypes<T>::Init(const std::string& filePath)
{
    std::ifstream file(filePath);
    
    nlohmann::json j = nlohmann::json::parse(file);
    prototypes.resize(j.size());
    uint32_t currentId = 0;
    for (auto node = j.begin(); node != j.end(); ++node)
    {
        std::unique_ptr<T> newPrototype = std::make_unique<T>();
        if (node.value().contains("parent"))
        {
            std::string parentSid = node.value().at("parent").get<std::string>();
            if (j.contains(parentSid))
            {
                nlohmann::json::iterator parentNode = j.at(parentSid).get<nlohmann::json::iterator>();
                newPrototype->Init(parentNode);
            }
            
        }
        newPrototype->Init(node);
        newPrototype->id = currentId;
        prototypes[currentId] = std::move(newPrototype);
        
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
    assert(false && "Don't exist prototype with this ID");
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
    assert(false && "Don't exist prototype with this SID");
    return GetDefault();
}

template <class T>
size_t BasePrototypes<T>::Size()
{
    return prototypes.size();
}

