#ifndef CONFIG_H
#define CONFIG_H
#include <string>
// Data files (all plain text, created automatically)
constexpr const char* CANDIDATE_FILE = "candidates.txt";  // id|name|party
constexpr const char* VOTER_FILE     = "voters.txt";      // voter_id|name
constexpr const char* VOTES_FILE     = "votes.txt";       // one candidate id per vote
constexpr const char* VOTED_FILE     = "voted.txt";       // voter ids who already voted
constexpr const char* ADMIN_PASSWORD = "admin123";
constexpr int VALID_VOTER_START = 100000;
constexpr int VALID_VOTER_END   = 999999;
constexpr int MAX_CANDIDATES = 100;
struct Candidate {
    int         id = 0;
    std::string name;
    std::string party;
};
#endif
