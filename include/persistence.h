#pragma once

#include "database.h"

class Persistence
{
public:
    static bool save(Database& db);
    static bool load(Database& db);
};
