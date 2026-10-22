#include <cstdlib>
#include <fstream>
#include <iostream>
#include "storage.h"
#include "config.h"
using namespace std;
static void ensure_file(const char* path)
{
    ofstream file(path, ios::app);
    if (!file)
    {
        cout << "File error: cannot open " << path << "\n";
        exit(1);
    }
}
void init_storage()
{
    ensure_file(CANDIDATE_FILE);
    ensure_file(VOTER_FILE);
    ensure_file(VOTES_FILE);
    ensure_file(VOTED_FILE);
}
