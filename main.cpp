#include <iostream>
#include <string>
#include "config.h"
#include "utils.h"
#include "storage.h"
#include "candidate.h"
#include "voter.h"
#include "voting.h"
#include "results.h"

using namespace std;

int main()
{
    init_storage();
    cout << "====================================\n";
    cout << "   TIME-BOUND VOTING SYSTEM\n";
    cout << "====================================\n";
    cout << "\nEnter admin password: ";
    string password = get_input();
    if (password != ADMIN_PASSWORD)
    {
        cout << "Incorrect password.\n";
        return 0;
    }
    
    cout << "Admin login successful.\n";
    cout << "\nCandidate registration time: ";
    int candidate_time = positive_int(get_input());
    cout << "Voter registration time: ";
    int voter_time = positive_int(get_input());
    if (candidate_time <= 0 || voter_time <= 0)
    {
        cout << "Invalid time entered.\n";
        return 1;
    }
    
    candidate_registration(candidate_time);
    voter_registration(voter_time);
    cout << "\n=== VOTING SETUP ===\n";
    cout << "Enter admin password: ";
    password = get_input();
    if (password != ADMIN_PASSWORD)
    {
        cout << "Incorrect password.\n";
        return 0;
    }
    
    cout << "Voting duration: ";
    int voting_time = positive_int(get_input());
    if (voting_time <= 0)
    {
        cout << "Invalid voting time.\n";
        return 1;
    }

    
    voting_phase(voting_time);
    show_results();
    cout << "\nVoting process completed.\n";
    return 0;
}
