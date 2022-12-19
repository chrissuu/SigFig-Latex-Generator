#include <math.h>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <SigFigs.h>

using std::cout;
using std::stack;
using std::stod;
using std::string;
using std::to_string;
using std::vector;

string pm("\pm");

string insertSpacesOnEntries(vector<string> args)
{
    string msg("");
    for (int i = 0; i < args.size(); i++)
    {
        msg += args[i] + " ";
        if (args[i] == "=")
        {
            msg += "\n";
        }
    }
    return msg;
}

class LatexFormatter
{
    SigFigs val;
    SigFigs uncertainty;

public:
    LatexFormatter(SigFigs val, SigFigs uncertainty)
    {
        this->val = val;
        this->uncertainty = uncertainty;
    }

    
};