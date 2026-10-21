#ifndef VOTER_H
#define VOTER_H

#include <string>

bool voter_exists(const std::string& id);
bool add_voter(const std::string& id, const std::string& name);
void voter_registration(int duration);

#endif
