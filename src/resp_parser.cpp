#include "resp_parser.h"

#include <sstream>

using namespace std;

vector<string> RespParser::parse(const string& input)
{
    vector<string> tokens;

    if(input.empty())
        return tokens;

    // Plain text support
    if(input[0] != '*')
    {
        stringstream ss(input);

        string word;

        while(ss >> word)
            tokens.push_back(word);

        return tokens;
    }

    stringstream ss(input);

    string line;

    getline(ss,line);

    while(getline(ss,line))
    {
        if(line.empty())
            continue;

        if(line[0] == '$')
            continue;

        if(line.back()=='\r')
            line.pop_back();

        tokens.push_back(line);
    }

    return tokens;
}