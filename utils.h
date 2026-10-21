#ifndef UTILS_H
#define UTILS_H

#include <ctime>
#include <string>

std::string get_input();                       // read one line from stdin ("" on EOF)
int         positive_int(const std::string& s); // digits-only string -> int, 0 if invalid
int         time_left(std::time_t end_time);    // seconds remaining, 0 if expired
void        clean_field(std::string& s);        // replace '|' with ' '

#endif
