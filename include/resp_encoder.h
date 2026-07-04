#pragma once

#include <string>

class RespEncoder
{
public:
    std::string simpleString(const std::string& value);

    std::string bulkString(const std::string& value);

    std::string nullBulkString();

    std::string integer(int value);

    std::string error(const std::string& message);
};
