#include "parser.h"

using namespace std;

Parser::Parser(Database& db)
    : database(db)
{

}


string Parser::parse(const string& input)
{
    if(input == "PING")
        return "PONG";

    return "ERROR";
}