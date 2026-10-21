#ifndef VOTING_H
#define VOTING_H

#include <string>

bool cast_vote(int candidate_id);
bool has_voted(const std::string& voter_id);
bool mark_voted(const std::string& voter_id);
void voting_phase(int duration);

#endif
