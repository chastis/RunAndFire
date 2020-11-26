#pragma once

#include <Utility/Core/StringId.hpp>
#include <Utility/XML/pugixml.hpp>
#include <string>
#include <map>

using ActionSignal = StringId;

class ActionMap
{
public:
    void LoadFromXml(const pugi::xml_node& actionMapNode);

    const std::string& GetName() const;
    const ActionSignal& GetSignalFromInput(const std::string& inputValue) const;
private:
    std::map<StringId, StringId> m_signals;
    std::string m_name;
};
