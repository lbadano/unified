#include "String.hpp"
#include "../Maybe.hpp"
#include <sstream>
#include <stdlib.h> 
#include <string.h>

namespace NWNXLib {
namespace Utils {

template<> Maybe<bool> from_string(const std::string& str)
{
    static const char* truesies[] = { "t", "true", "y", "yes", "1" };
    static const char* falsies[] = { "f", "false", "n", "no", "0" };

    for (const char* t : truesies)
    {
        if (strcasecmp(t, str.c_str()) == 0)
        {
            return Maybe<bool>(true);
        }
    }

    for (const char* f : falsies)
    {
        if (strcasecmp(f, str.c_str()) == 0)
        {
            return Maybe<bool>(false);
        }
    }

    return Maybe<bool>();
}

inline int base(const std::string& str)
{
    return str.length() > 2 && str[0] == '0' && str[1] == 'x' ? 16 : 10;
}

inline const char* first_non_space(const std::string& str) {
    const char* start = str.c_str();
    while (*start && std::isspace(*start)) ++start;
    return start;
}

template <> Maybe<int32_t> from_string(const std::string& str)
{
    const char* start = first_non_space(str);
    if (!*start) return Maybe<int32_t>();
    char* end;
    int32_t res = strtol(start, &end, base(str));
    return (!*end || std::isspace(*end)) ? Maybe<int32_t>(res) : Maybe<int32_t>();
}

template<> Maybe<uint32_t> from_string(const std::string& str)
{
    const char* start = first_non_space(str);
    if (!*start) return Maybe<uint32_t>();
    char* end;
    uint32_t res = strtoul(start, &end, base(str));
    return (!*end || std::isspace(*end)) ? Maybe<uint32_t>(res) : Maybe<uint32_t>();
}

template<> Maybe<int64_t> from_string(const std::string& str)
{
    const char* start = first_non_space(str);
    if (!*start) return Maybe<int64_t>();
    char* end;
    int64_t res = strtoll(start, &end, base(str));
    return (!*end || std::isspace(*end)) ? Maybe<int64_t>(res) : Maybe<int64_t>();
}

template<> Maybe<uint64_t> from_string(const std::string& str)
{
    const char* start = first_non_space(str);
    if (!*start) return Maybe<uint64_t>();
    char* end;
    uint64_t res = strtoull(start, &end, base(str));
    return (!*end || std::isspace(*end)) ? Maybe<uint64_t>(res) : Maybe<uint64_t>();
}

template<> Maybe<float> from_string(const std::string& str)
{
    const char* start = first_non_space(str);
    if (!*start) return Maybe<float>();
    char* end;
    float res = strtof(start, &end);
    return (!*end || std::isspace(*end)) ? Maybe<float>(res) : Maybe<float>();
}

template<> Maybe<double> from_string(const std::string& str)
{
    const char* start = first_non_space(str);
    if (!*start) return Maybe<double>();
    char* end;
    double res = strtod(start, &end);
    return (!*end || std::isspace(*end)) ? Maybe<double>(res) : Maybe<double>();
}

std::string& ltrim(std::string& str) 
{
    str.erase(0, str.find_first_not_of(" \n\r\t"));
    return str;
}

std::string& rtrim(std::string& str) 
{
    str.erase(str.find_last_not_of(" \n\r\t") + 1);
    return str;
}

std::string& trim(std::string& str) 
{
    return ltrim(rtrim(str));
}

std::string join(const std::vector<std::string>& v, const char* delim)
{
    if (!v.size()) return {};

    std::ostringstream out;
    auto it = std::begin(v);

    out << *it;
    while(++it != std::end(v)) 
    {
        out << delim << *it; 
    }
    return out.str();
}

std::vector<std::string> split(const std::string& sp, char delim, bool skipEmpty, bool trimmed)
{
    std::vector<std::string> out;
    std::istringstream ss{sp};
    std::string item;
    while (getline(ss, item, delim))
    {
        if (skipEmpty && item.empty()) 
            continue;
        
        if (trimmed)
            trim(item);

        out.push_back(item);
    }
    return out;
}

}
}