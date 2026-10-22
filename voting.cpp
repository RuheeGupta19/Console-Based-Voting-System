#include <algorithm>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include "voting.h"
#include "candidate.h"
#include "voter.h"
#include "config.h"
#include "utils.h"
using namespace std;
// Appends one line (the candidate ID) to votes.txt
bool cast_vote(int candidate_id)
{
    ofstream file(VOTES_FILE, ios::app);
    if (!file)
        return false;
    file << candidate_id << '\n';
    file.flush();
    return static_cast<bool>(file);
}
// Checks voted.txt for this voter ID
bool has_voted(const string& voter_id)
{
    ifstream file(VOTED_FILE);
    string line;

    while (getline(file, line))
        if (line == voter_id)
            return true;
    return false;
}
// Appends the voter ID to voted.txt
bool mark_voted(const string& voter_id)
{
    ofstream file(VOTED_FILE, ios::app);
    if (!file)
        return false;
    file << voter_id << '\n';
    file.flush();
    return static_cast<bool>(file);
}
void voting_phase(int duration)
{
    Candidate candidates[MAX_CANDIDATES];
    int count = load_candidates(candidates);
    if (count == 0)
    {
        cout << "No candidates available.\n";
        return;
    }
    time_t end_time = time(nullptr) + duration;
    cout << "\n=== VOTING PHASE ===\n";
    while (time_left(end_time) > 0)
    {
        cout << "\nTime left: " << time_left(end_time) << " seconds\n";
        cout << "Commands: vote/list/end\n";
        cout << "cmd> ";
        string command = get_input();
        if (command == "list")
        {
            list_candidates();
            continue;
        }
        if (command == "end")
        {
            cout << "Enter admin password: ";
            string password = get_input();
            if (password == ADMIN_PASSWORD)
            {
                cout << "Voting ended.\n";
                break;
            }
            cout << "Incorrect password.\n";
            continue;
        }
        if (command != "vote")
        {
            cout << "Invalid command.\n";
            continue;
        }
        cout << "Enter Voter ID: ";
        string voter_id = get_input();
        if (voter_id.size() != 6)
        {
            cout << "Invalid Voter ID.\n";
            continue;
        }
        bool all_digits = all_of(voter_id.begin(), voter_id.end(),
            [](unsigned char c) { return isdigit(c) != 0; });
        if (!all_digits)
        {
            cout << "Voter ID must contain digits only.\n";
            continue;
        }
        if (!voter_exists(voter_id))
        {
            cout << "Voter is not registered.\n";
            continue;
        }
        if (has_voted(voter_id))
        {
            cout << "This voter already voted.\n";
            continue;
        }
        list_candidates();
        cout << "Enter candidate ID: ";
        string selection = get_input();
        int id = positive_int(selection);
        int index = -1;
        for (int i = 0; i < count; i++)
        {
            if (candidates[i].id == id)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            cout << "Invalid candidate ID.\n";
            continue;
        }
        if (!cast_vote(id))
        {
            cout << "ERROR: could not write " << VOTES_FILE
                 << " (check folder permissions). Vote NOT recorded.\n";
            continue;
        }
        if (!mark_voted(voter_id))
            cout << "WARNING: could not write " << VOTED_FILE << ".\n";
        cout << "Vote recorded for " << candidates[index].name << ".\n";
    }

    if (time_left(end_time) == 0)
        cout << "\nVoting time expired.\n";
}
