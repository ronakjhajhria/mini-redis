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
bool Database::del(const string& key)
{
    return store.erase(key) > 0;
}
bool Database::exists(const string& key)
{
    return store.find(key) != store.end();
}
string Database::keys()
{
    string result;
    for(const auto& pair : store)
    {
        result += pair.first + "\n";
    }
    return result;
}

void Database::flushAll()
{
    store.clear();
}
int Database::size()
{
    return store.size();
}

const unordered_map<string, string>& Database::getStore() const
{
    return store;
}
