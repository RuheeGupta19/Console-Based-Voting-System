#include <algorithm>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include "voter.h"
#include "config.h"
#include "utils.h"

bool voter_exists(const std::string& id)
{
    std::ifstream file(VOTER_FILE);
    std::string line;

    while (std::getline(file, line))
    {
        if (line.substr(0, line.find('|')) == id)
            return true;
    }

    return false;
}

bool add_voter(const std::string& id, const std::string& name)
{
    std::ofstream file(VOTER_FILE, std::ios::app);

    if (!file)
        return false;

    file << id << '|' << name << '\n';
    return true;
}

void voter_registration(int duration)
{
    std::time_t end_time = std::time(nullptr) + duration;

    std::cout << "\n=== VOTER REGISTRATION ===\n";

    while (time_left(end_time) > 0)
    {
        std::cout << "\nTime left: " << time_left(end_time) << " seconds\n";
        std::cout << "Enter command (reg/end): ";
        std::string command = get_input();

        if (command == "reg")
        {
            std::cout << "Voter ID (6 digits): ";
            std::string id = get_input();

            std::cout << "Voter name: ";
            std::string name = get_input();

            clean_field(name);

            if (id.size() != 6 || name.empty())
            {
                std::cout << "Invalid voter information.\n";
                continue;
            }

            bool all_digits = std::all_of(id.begin(), id.end(),
                [](unsigned char c) { return std::isdigit(c) != 0; });

            if (!all_digits)
            {
                std::cout << "Voter ID must contain digits only.\n";
                continue;
            }

            int number = std::stoi(id);

            if (number < VALID_VOTER_START || number > VALID_VOTER_END)
            {
                std::cout << "Voter ID is outside valid range.\n";
                continue;
            }

            if (voter_exists(id))
            {
                std::cout << "Voter already registered.\n";
                continue;
            }

            if (add_voter(id, name))
                std::cout << "Voter " << id << " registered successfully.\n";
            else
                std::cout << "Could not register voter.\n";
        }
        else if (command == "end")
        {
            std::cout << "Enter admin password: ";
            std::string password = get_input();

            if (password == ADMIN_PASSWORD)
            {
                std::cout << "Voter registration ended.\n";
                break;
            }

            std::cout << "Incorrect password.\n";
        }
        else
        {
            std::cout << "Invalid command.\n";
        }
    }

    if (time_left(end_time) == 0)
        std::cout << "\nVoter registration time expired.\n";
}
