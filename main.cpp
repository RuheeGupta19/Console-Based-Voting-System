#include <iostream>
#include <string>
#include "config.h"
#include "utils.h"
#include "storage.h"
#include "candidate.h"
#include "voter.h"
#include "voting.h"
#include "results.h"
int main()
{
    init_storage();
    std::cout << "====================================\n";
    std::cout << "   TIME-BOUND VOTING SYSTEM\n";
    std::cout << "====================================\n";

    std::cout << "\nEnter admin password: ";
    std::string password = get_input();
    if (password != ADMIN_PASSWORD)
    {
        std::cout << "Incorrect password.\n";
        return 0;
    }
    std::cout << "Admin login successful.\n";
    std::cout << "\nCandidate registration time: ";
    int candidate_time = positive_int(get_input());

    std::cout << "Voter registration time: ";
    int voter_time = positive_int(get_input());

    if (candidate_time <= 0 || voter_time <= 0)
    {
        std::cout << "Invalid time entered.\n";
        return 1;
    }
    candidate_registration(candidate_time);

    voter_registration(voter_time);

    std::cout << "\n=== VOTING SETUP ===\n";

    std::cout << "Enter admin password: ";
    password = get_input();

    if (password != ADMIN_PASSWORD)
    {
        std::cout << "Incorrect password.\n";
        return 0;
    }
    std::cout << "Voting duration: ";
    int voting_time = positive_int(get_input());

    if (voting_time <= 0)
    {
        std::cout << "Invalid voting time.\n";
        return 1;
    }
    voting_phase(voting_time);

    show_results();

    std::cout << "\nVoting process completed.\n";

    return 0;
}
