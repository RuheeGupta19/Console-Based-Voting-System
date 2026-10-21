#include <cstdlib>
#include <fstream>
#include <iostream>
#include "storage.h"
#include "config.h"

static void ensure_file(const char* path)
{
    // app mode creates the file if missing and keeps data if present
    std::ofstream file(path, std::ios::app);

    if (!file)
    {
        std::cout << "File error: cannot open " << path << "\n";
        std::exit(1);
    }
}

void init_storage()
{
    ensure_file(CANDIDATE_FILE);
    ensure_file(VOTER_FILE);
    ensure_file(VOTES_FILE);
    ensure_file(VOTED_FILE);
}
