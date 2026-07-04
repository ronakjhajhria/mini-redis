#pragma once

#include <string>
#include "database.h"

class Parser
{
public:
    Parser(Database& db);
    std::string parse(const std::string& input);
private:
    Database& database;
};
