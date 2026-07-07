#include "persistence.h"

#include <fstream>

using namespace std;

bool Persistence::save(Database& db)
{
    ofstream file("data/dump.rdb");

    if(!file.is_open())
        return false;

    for(const auto& p : db.getStore())
    {
        file << p.first << " " << p.second << '\n';
    }

    file.close();

    return true;
}

bool Persistence::load(Database& db)
{
    std::ifstream file("data/dump.rdb");

    if(!file.is_open())
        return false;

    string key;
    string value;

    while(file >> key >> value)
    {
        db.set(key, value);
    }

    file.close();

    return true;
}