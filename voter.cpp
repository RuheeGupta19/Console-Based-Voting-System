#include <algorithm>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include "voter.h"
#include "config.h"
#include "utils.h"
using namespace std;
bool voter_exists(const string& id)
{
    ifstream file(VOTER_FILE);
    string line;
    while (getline(file, line))
    {
        if (line.substr(0, line.find('|')) == id)
            return true;
    }
    return false;
}
bool add_voter(const string& id, const string& name)
{
    ofstream file(VOTER_FILE, ios::app);
    if (!file)
        return false;
    file << id << '|' << name << '\n';
    return static_cast<bool>(file);
}
void voter_registration(int duration)
{
    time_t end_time = time(nullptr) + duration;
    cout << "\n=== VOTER REGISTRATION ===\n";
    while (time_left(end_time) > 0)
    {
        cout << "\nTime left: " << time_left(end_time) << " seconds\n";
        cout << "Enter command (reg/end): ";
        string command = get_input();
        if (command == "reg")
        {
            cout << "Voter ID (6 digits): ";
            string id = get_input();
            cout << "Voter name: ";
            string name = get_input();
            clean_field(name);
            if (id.size() != 6 || name.empty())
            {
                cout << "Invalid voter information.\n";
                continue;
            }
            bool all_digits = all_of(id.begin(), id.end(),
                [](unsigned char c) { return isdigit(c) != 0; });
            if (!all_digits)
            {
                cout << "Voter ID must contain digits only.\n";
                continue;
            }
            int number = stoi(id);
            if (number < VALID_VOTER_START || number > VALID_VOTER_END)
            {
                cout << "Voter ID is outside valid range.\n";
                continue;
            }
            if (voter_exists(id))
            {
                cout << "Voter already registered.\n";
                continue;
            }
            if (add_voter(id, name))
                cout << "Voter " << id << " registered successfully.\n";
            else
                cout << "Could not register voter.\n";
        }
        else if (command == "end")
        {
            cout << "Enter admin password: ";
            string password = get_input();
            if (password == ADMIN_PASSWORD)
            {
                cout << "Voter registration ended.\n";
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
        cout << "\nVoter registration time expired.\n";
}
