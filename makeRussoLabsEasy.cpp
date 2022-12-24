#include <math.h>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include "SigFigs.h"
#include "ErrorComputer.h"
#include <stack>
#include <fstream>
#include <unordered_map>
using std::unordered_map;
using std::cout;
using std::ifstream;
using std::stack;
using std::stod;
using std::string;
using std::to_string;
using std::vector;

string pm("\\pm");

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
//4 = paren, 3 = exponent, 2 = multi/division, 1 = addition/subtraction
string calculate(string args, int priority) {
    if(priority ==4) {
        vector<string> s;
        while(args.find_last_of("(")!=string::npos){
            string temp = args.substr(args.find_last_of("("),args.size()).substr(0,args.find(")"));
            args = args.substr(0,args.find_last_of("(")) +calculate(temp,4) + args.substr(args.find(")")+1,args.size());
            return calculate(args, 3);
        }

        calculate(args , 3)
    }
}

int main()
{
    // ifstream f("query.txt");
    // v
    // while(f.is_open()){

    // }
    // string infix = "((a+(b*c))-d)";
    // string postfix;
    // postfix = convert(infix);
    // cout << "\n";
    // unordered_map<char,double> map;
    // map['a'] = 56.72;
    // map['b'] = 2.5;
    // map['c'] = -9.3;
    // map['d'] = 87.0;
    // cout << calculate_Postfix(postfix, map);
    SigFigs s = ((SigFigs("7.68") * SigFigs("4.509") + SigFigs("3.224"))/SigFigs("0.23"));
    cout << s.getSVal();
    return 0;
}
