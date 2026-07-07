#pragma once

#include <string>
#include <unordered_map>
#include <mutex>
using namespace std;
class Database
{
public:
    void set(const string& key, const string& value);

    string get(const std::string& key);

    bool del(const std::string& key);

    bool exists(const std::string & key);

    std::string keys();

    void flushAll();
    int size();
    const std::unordered_map<std::string, std::string>& getStore() const;

private:
    std::unordered_map<std::string, std::string> store;
};
