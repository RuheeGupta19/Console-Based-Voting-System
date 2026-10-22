#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include "utils.h"
using namespace std;
string get_input()
{
    string line;
    if (!getline(cin, line))
    {
        cin.clear();
        return "";
    }
    while (!line.empty() &&
           (line.back() == '\r' || line.back() == ' ' || line.back() == '\t'))
        line.pop_back();
    return line;
}
int positive_int(const string& input)
{
    string s = input;
    while (!s.empty() && isspace(static_cast<unsigned char>(s.back())))
        s.pop_back();
    if (s.empty())
        return 0;
    for (unsigned char c : s)
        if (!isdigit(c))
            return 0;
    try
    {
        long long value = stoll(s);
        if (value <= 0 || value > numeric_limits<int>::max())
            return 0;
        return static_cast<int>(value);
    }
    catch (...)
    {
        return 0;
    }
}
int time_left(time_t end_time)
{
    time_t now = time(nullptr);
    if (end_time <= now)
        return 0;
    return static_cast<int>(difftime(end_time, now));
}
void clean_field(string& s)
{
    replace(s.begin(), s.end(), '|', ' ');
}
