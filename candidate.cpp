#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include "candidate.h"
#include "utils.h"

using namespace std;

int load_candidates(Candidate candidates[])
{
    int count = 0;
    ifstream file(CANDIDATE_FILE);
    string line;

    while (count < MAX_CANDIDATES && getline(file, line))
    {
        size_t p1 = line.find('|');
        if (p1 == string::npos)
            continue;

        size_t p2 = line.find('|', p1 + 1);
        if (p2 == string::npos)
            continue;

        Candidate c;

        try
        {
            c.id = stoi(line.substr(0, p1));
        }
        catch (...)
        {
            continue;
        }

        c.name = line.substr(p1 + 1, p2 - p1 - 1);
        c.party = line.substr(p2 + 1);

        if (!c.name.empty() && !c.party.empty())
            candidates[count++] = c;
    }

    return count;
}

int add_candidate(const string& name, const string& party)
{
    Candidate candidates[MAX_CANDIDATES];
    int count = load_candidates(candidates);
    int next_id = 1;

    for (int i = 0; i < count; i++)
    {
        if (candidates[i].name == name &&
            candidates[i].party == party)
            return -1;

        if (candidates[i].id >= next_id)
            next_id = candidates[i].id + 1;
    }

    if (count >= MAX_CANDIDATES)
        return -2;

    ofstream file(CANDIDATE_FILE, ios::app);

    if (!file)
        return -2;

    file << next_id << '|' << name << '|' << party << '\n';

    if (!file)
        return -2;

    return next_id;
}

void list_candidates()
{
    Candidate candidates[MAX_CANDIDATES];
    int count = load_candidates(candidates);

    if (count == 0)
    {
        cout << "No candidates registered.\n";
        return;
    }

    cout << "\nRegistered Candidates:\n";

    for (int i = 0; i < count; i++)
    {
        cout << candidates[i].id << ". "
             << candidates[i].name << " ("
             << candidates[i].party << ")\n";
    }
}

void candidate_registration(int duration)
{
    time_t end_time = time(nullptr) + duration;

    cout << "\n=== CANDIDATE REGISTRATION ===\n";

    while (time_left(end_time) > 0)
    {
        cout << "\nTime left: " << time_left(end_time)
             << " seconds\n";
        cout << "Enter command (add/list/end): ";

        string command = get_input();

        if (command == "add")
        {
            cout << "Candidate name: ";
            string name = get_input();

            cout << "Party name: ";
            string party = get_input();

            clean_field(name);
            clean_field(party);

            if (name.empty() || party.empty())
            {
                cout << "Name and party are required.\n";
                continue;
            }

            int id = add_candidate(name, party);

            if (id == -1)
                cout << "Candidate already exists.\n";
            else if (id == -2)
                cout << "Could not add candidate "
                     << "(file error or limit reached).\n";
            else
                cout << "Candidate added with ID "
                     << id << ".\n";
        }
        else if (command == "list")
        {
            list_candidates();
        }
        else if (command == "end")
        {
            cout << "Enter admin password: ";
            string password = get_input();

            if (password == ADMIN_PASSWORD)
            {
                cout << "Registration ended.\n";
                break;
            }

            cout << "Incorrect password.\n";
        }
        else
        {
            cout << "Invalid command.\n";
        }
    }

    if (time_left(end_time) == 0)
        cout << "\nCandidate registration time expired.\n";
}
