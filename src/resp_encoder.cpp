#include "resp_encoder.h"

using namespace std;

string RespEncoder::simpleString(const string& value)
{
    return "+" + value + "\r\n";
}

string RespEncoder::bulkString(const string& value)
{
    return "$" + to_string(value.size()) + "\r\n" +
           value + "\r\n";
}

string RespEncoder::nullBulkString()
{
    return "$-1\r\n";
}

string RespEncoder::integer(int value)
{
    return ":" + to_string(value) + "\r\n";
}

string RespEncoder::error(const string& message)
{
    return "-" + message + "\r\n";
}
