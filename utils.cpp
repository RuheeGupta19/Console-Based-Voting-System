#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include "utils.h"

std::string get_input()
{
    std::string line;

    if (!std::getline(std::cin, line))
    {
        std::cin.clear();
        return "";
    }

    // strip stray CR / trailing spaces (Windows line endings)
    while (!line.empty() && (line.back() == '\r' || line.back() == ' ' || line.back() == '\t'))
        line.pop_back();

    return line;
}

int positive_int(const std::string& input)
{
    std::string s = input;
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back())))
        s.pop_back();

    if (s.empty())
        return 0;

    for (unsigned char c : s)
    {
        if (!std::isdigit(c))
            return 0;
    }

    try
    {
        long long value = std::stoll(s);
        if (value <= 0 || value > std::numeric_limits<int>::max())
            return 0;
        return static_cast<int>(value);
    }
    catch (...)
    {
        return 0;   // too large to parse
    }
}

int time_left(std::time_t end_time)
{
    std::time_t now = std::time(nullptr);

    if (end_time <= now)
        return 0;

    return static_cast<int>(std::difftime(end_time, now));
}

void clean_field(std::string& s)
{
    std::replace(s.begin(), s.end(), '|', ' ');
}
