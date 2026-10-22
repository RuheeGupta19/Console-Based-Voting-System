#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "results.h"
#include "candidate.h"
#include "config.h"
#include "utils.h"
using namespace std;
void show_results()
{
    Candidate candidates[MAX_CANDIDATES];
    int votes[MAX_CANDIDATES] = {};
    int count = load_candidates(candidates);
    ifstream file(VOTES_FILE);
    string line;
    while (getline(file, line))
    {
        int id = positive_int(line);
        for (int i = 0; i < count; i++)
        {
            if (candidates[i].id == id)
            {
                votes[i]++;
                break;
            }
        }
    }
    int max_votes = 0;
    string winner;
    cout << "\n=== RESULTS ===\n";
    for (int i = 0; i < count; i++)
    {
        cout << left << setw(25) << candidates[i].name
             << " : " << votes[i] << " votes\n";
        if (votes[i] > max_votes)
        {
            max_votes = votes[i];
            winner = candidates[i].name;
        }
    }
    if (count == 0)
        cout << "No candidates found.\n";
    else if (max_votes == 0)
        cout << "\nNo votes were cast.\n";
    else
        cout << "\nWinner: " << winner << " with "
             << max_votes << " votes!\n";
}
