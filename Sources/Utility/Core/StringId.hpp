#pragma once

#include <Utility/Core/CRC.hpp>

#include <string>

class StringId
{
public:
    StringId() = default;
    StringId(const std::string& str);

    bool operator==(const StringId& rhs) const;
    bool operator!=(const StringId& rhs) const;

    const std::string& Str() const;
    std::uint32_t Id() const;
private:
    std::string m_string;
    std::uint32_t m_crc = 0;
};

#include <functional>

namespace std
{
    template<> struct hash<StringId>
    {
        std::size_t operator()(StringId const& s) const noexcept
        {
            return s.Id();
        }
    };
}