#include <algorithm>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "voting.h"
#include "candidate.h"
#include "voter.h"
#include "config.h"
#include "utils.h"

// Appends one line (the candidate id) to votes.txt
bool cast_vote(int candidate_id)
{
    std::ofstream file(VOTES_FILE, std::ios::app);

    if (!file)
        return false;

    file << candidate_id << '\n';
    file.flush();
    return static_cast<bool>(file);
}

// Checks voted.txt for this voter id
bool has_voted(const std::string& voter_id)
{
    std::ifstream file(VOTED_FILE);
    std::string line;

    while (std::getline(file, line))
    {
        if (line == voter_id)
            return true;
    }

    return false;
}

// Appends the voter id to voted.txt
bool mark_voted(const std::string& voter_id)
{
    std::ofstream file(VOTED_FILE, std::ios::app);

    if (!file)
        return false;

    file << voter_id << '\n';
    file.flush();
    return static_cast<bool>(file);
}

void voting_phase(int duration)
{
    std::vector<Candidate> candidates = load_candidates();

    if (candidates.empty())
    {
        std::cout << "No candidates available.\n";
        return;
    }

    std::time_t end_time = std::time(nullptr) + duration;

    std::cout << "\n=== VOTING PHASE ===\n";

    while (time_left(end_time) > 0)
    {
        std::cout << "\nTime left: " << time_left(end_time) << " seconds\n";
        std::cout << "Commands: vote/list/end\n";
        std::cout << "cmd> ";
        std::string command = get_input();

        if (command == "list")
        {
            list_candidates();
            continue;
        }

        if (command == "end")
        {
            std::cout << "Enter admin password: ";
            std::string password = get_input();

            if (password == ADMIN_PASSWORD)
            {
                std::cout << "Voting ended.\n";
                break;
            }

            std::cout << "Incorrect password.\n";
            continue;
        }

        if (command != "vote")
        {
            std::cout << "Invalid command.\n";
            continue;
        }

        std::cout << "Enter Voter ID: ";
        std::string voter_id = get_input();

        if (voter_id.size() != 6)
        {
            std::cout << "Invalid Voter ID.\n";
            continue;
        }

        bool all_digits = std::all_of(voter_id.begin(), voter_id.end(),
            [](unsigned char c) { return std::isdigit(c) != 0; });

        if (!all_digits)
        {
            std::cout << "Voter ID must contain digits only.\n";
            continue;
        }

        if (!voter_exists(voter_id))
        {
            std::cout << "Voter is not registered.\n";
            continue;
        }

        if (has_voted(voter_id))
        {
            std::cout << "This voter already voted.\n";
            continue;
        }

        list_candidates();

        std::cout << "Enter candidate ID: ";
        std::string selection = get_input();

        int id = positive_int(selection);

        auto it = std::find_if(candidates.begin(), candidates.end(),
            [id](const Candidate& c) { return c.id == id; });

        if (it == candidates.end())
        {
            std::cout << "Invalid candidate ID.\n";
            continue;
        }

        if (!cast_vote(id))
        {
            std::cout << "ERROR: could not write " << VOTES_FILE
                      << " (check folder permissions). Vote NOT recorded.\n";
            continue;
        }

        if (!mark_voted(voter_id))
            std::cout << "WARNING: could not write " << VOTED_FILE << ".\n";

        std::cout << "Vote recorded for " << it->name << ".\n";
    }

    if (time_left(end_time) == 0)
        std::cout << "\nVoting time expired.\n";
}
