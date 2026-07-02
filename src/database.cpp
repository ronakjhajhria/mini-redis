#include "database.h"

using namespace std;

void Database::set(const string& key, const string& value)
{
    store[key] = value;
}

string Database::get(const string& key)
{
    auto it = store.find(key);

    if(it == store.end())
        return "NULL";

    return it->second;
}
