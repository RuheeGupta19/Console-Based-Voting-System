#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "results.h"
#include "candidate.h"
#include "config.h"
#include "utils.h"

void show_results()
{
    std::vector<Candidate> candidates = load_candidates();
    std::vector<int> votes(candidates.size(), 0);

    // Count the lines in votes.txt per candidate
    std::ifstream file(VOTES_FILE);
    std::string line;

    while (std::getline(file, line))
    {
        int id = positive_int(line);

        for (std::size_t i = 0; i < candidates.size(); i++)
        {
            if (candidates[i].id == id)
            {
                votes[i]++;
                break;
            }
        }
    }

    int max_votes = 0;
    std::string winner;

    std::cout << "\n=== RESULTS ===\n";

    for (std::size_t i = 0; i < candidates.size(); i++)
    {
        std::cout << std::left << std::setw(25) << candidates[i].name
                  << " : " << votes[i] << " votes\n";

        if (votes[i] > max_votes)
        {
            max_votes = votes[i];
            winner = candidates[i].name;
        }
    }

    if (candidates.empty())
        std::cout << "No candidates found.\n";
    else if (max_votes == 0)
        std::cout << "\nNo votes were cast.\n";
    else
        std::cout << "\nWinner: " << winner << " with " << max_votes << " votes!\n";
}
