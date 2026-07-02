#include "parser.h"

using namespace std;
string Parser::parse(const string& input)
{
    if(input == "PING")
    {
        return "PONG";
    }

    return "ERROR";
}
