#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "SigFigs.h"
using std::cout;
using std::find;
using std::pair;
using std::stod;
using std::string;
using std::to_string;
using std::vector;
// 532.99 * 29384.5 => pair (532.99, 29384.5)
pair<double, double> split(string args, char delim)
{
    pair<double, double> temp;
    temp.first = stod(args.substr(0, args.find(delim)));
    temp.second = stod(args.substr(args.find(delim) + 1, args.size()));
    return temp;
}
void normalizeString(string &args)
{
    while (args.find(" ") != string::npos)
    {
        args = args.substr(0, args.find(" ")) + args.substr(args.find(" ") + 1, args.size());
    }
}
void printVec(vector<char> &ot)
{
    for (int i = 0; i < ot.size(); i++)
    {
        cout << ot[i] << "\n";
    }
}

// *991391.138 + 13812898-
pair<pair<int, int>, string> expandAroundIndex(string args, int index)
{
    char storeDelimArr[] = {'-', '+', '^', '/', '*', '(', ')'};
    vector<char> storeDelim(storeDelimArr, storeDelimArr + 7);
    // printVec(storeDelim);
    // storeDelim.erase(find(storeDelim.begin(), storeDelim.end(), args[index]));
    int indexBegin = 0;
    for (int i = index - 1; i >= 0; i--)
    {
        indexBegin = i;
        if (find(storeDelim.begin(), storeDelim.end(), args[i]) != storeDelim.end())
        {
            break;
        }
    }
    // cout << indexBegin x;
    // cout << ((find(storeDelim.begin(), storeDelim.end(), '*') != storeDelim.end()) == true) x;
    int indexEnd = 0;
    for (int i = index + 1; i < args.size(); i++)
    {
        indexEnd = i;

        if (find(storeDelim.begin(), storeDelim.end(), args[i]) != storeDelim.end())
        {
            break;
        }
    }
    pair<int, int> indices;
    indices.first = indexBegin;
    indices.second = indexEnd;

    pair<pair<int, int>, string> ret;
    ret.first = indices;
    if (args[indexBegin] != '(' && !('0' <= (args[indexBegin]) && args[indexBegin] <= '9')){
        indexBegin++;
    }

    if (args[indexEnd] != ')'&& !('0' <= (args[indexBegin]) && args[indexBegin] <= '9')){
        indexEnd--;
    }
    ret.second = args.substr(indexBegin, indexEnd - indexBegin + 1);

    return ret;
}
string calculate(string args, int priority)
{
    normalizeString(args);
    if (priority == 4)
    {
        vector<string> s;
        while (args.find_last_of("(") != string::npos)
        {
            string temp = args.substr(args.find_last_of("("), args.size());
            temp = temp.substr(1, temp.find(")") - 1);
            //((a+b) * (c + 3)) =>(e*c) //e = a+b
            //cout << temp << " " << calculate(temp, 3) << "\n";
            args = args.substr(0, args.find_last_of("(")) + calculate(temp, 3) + args.substr(args.find(")") + 1, args.size());
            //cout << args << "\n";
            // cout << "args: " << args << "\n";
            //cout <<"Prio: " <<priority << " Sub: " << temp << "\n";
            // calculate(args,3);
            // calculate(args,2);
            // calculate(args,1);
            
        }

        string temp = calculate(args, 3);
        // cout << "inside parenthesis" << temp << "\n";
        return temp;

        //return calculate(args, 3);
    }

    if (priority == 3)
    {
        while (args.find("^") != string::npos)
        {
            pair<pair<int, int>, string> temp = expandAroundIndex(args, args.find("^"));
            string sub = temp.second;
            if (sub.find("(") != string::npos)
            {
                sub = sub.substr(sub.find("("), sub.size() - 1);
            }
            // cout <<"Prio: " <<priority << " Sub: " << sub << "\n";
            char delim = '^';
            pair<double, double> t = split(sub, delim);
            double p = pow(t.first, t.second);
            int firstIndex = temp.first.first;
            int lastIndex = temp.first.second;

            args = args.substr(0, firstIndex) + to_string(p) + args.substr(lastIndex, args.size());
        }
        return calculate(args, 2);
    }

    if (priority == 2)
    {
        while (args.find("*") != string::npos)
        {
            pair<pair<int, int>, string> temp = expandAroundIndex(args, args.find("*"));
            string sub = temp.second;
            if (sub.find("(") != string::npos)
            {
                sub = sub.substr(sub.find("("), sub.size() - 1);
            }
            // cout <<"Prio: " <<priority << " Sub: " << sub << "\n";
            char delim = '*';
            pair<double, double> t = split(sub, delim);

            cout << "SUB: " << sub << "DELIM:" << delim << "\n";

            SigFigs a(to_string(t.first));
            SigFigs b(to_string(t.second));

            cout << a.getSVal() << " " << b.getSVal() << "\n";
            SigFigs prod = a * b;

            cout << prod.getSVal() << "\n";

            int firstIndex = temp.first.first;
            int lastIndex = temp.first.second;

            


            args = args.substr(0, firstIndex) + prod.getSVal() + args.substr(lastIndex, args.size());


        }

        while (args.find("/") != string::npos)
        {
            pair<pair<int, int>, string> temp = expandAroundIndex(args, args.find("/"));
            string sub = temp.second;
            if (sub.find("(") != string::npos)
            {
                sub = sub.substr(sub.find("("), sub.size() - 1);
            }
            // cout <<"Prio: " <<priority << " Sub: " << sub << "\n";
            char delim = '/';
            pair<double, double> t = split(sub, delim);
            SigFigs a(to_string(t.first));
            SigFigs b(to_string(t.second));
            SigFigs prod = a / b;

            int firstIndex = temp.first.first;
            int lastIndex = temp.first.second;

            args = args.substr(0, firstIndex) + prod.getSVal() + args.substr(lastIndex, args.size());
        }

        return calculate(args, 1);
    }

    if (priority == 1)
    {
        while (args.find("+") != string::npos)
        {
            pair<pair<int, int>, string> temp = expandAroundIndex(args, args.find("+"));
            string sub = temp.second;
            if (sub.find("(") != string::npos)
            {
                sub = sub.substr(sub.find("("), sub.size() - 1);
            }
            // cout <<"Prio: " <<priority << " Sub: " << sub << "\n";
            char delim = '+';
            pair<double, double> t = split(sub, delim);
            SigFigs a(to_string(t.first));
            SigFigs b(to_string(t.second));
            SigFigs sum = a + b;

            int firstIndex = temp.first.first;
            int lastIndex = temp.first.second;

            args = args.substr(0, firstIndex) + sum.getSVal() + args.substr(lastIndex, args.size());
        }

        while (args.find("-") != string::npos && args[0] != '-')
        {
            pair<pair<int, int>, string> temp = expandAroundIndex(args, args.find("-"));
            string sub = temp.second;
            
            if (sub.find("(") != string::npos)
            {
                sub = sub.substr(sub.find("("), sub.size() - 1);
            }
            // cout <<"Prio: " <<priority << " Sub: " << sub << "\n";
            char delim = '-';
            pair<double, double> t = split(sub, delim);
            SigFigs a(to_string(t.first));
            SigFigs b(to_string(t.second));
            SigFigs diff = a - b;

            int firstIndex = temp.first.first;
            int lastIndex = temp.first.second;

            //cout << "args1: " << args << "\n";

            args = args.substr(0, firstIndex) + diff.getSVal() + args.substr(lastIndex, args.size());
            //cout << "args2: " << args << "\n";

        }

        //return calculate(args, 0);
        return args;
    }

    return args;
}

int main()
{   double t1= (0.98*3) + 7.6 - 2;
    double t2= (((4+55.2)*203 + 5993)/3 + 3) + 9.8;
    double t3 = 4.5 + 7;
    double t4 = 2.3 - 9;
    double t5 = 2.3*2;
    string s1("(0.98*3) + 7.6 - 2");
    string s2 ("(((4+55.2)*203 + 5993)/3 + 3) + 9.8");
    string s3 ("4.5 + 7");
    string s4("2.3 - 9");
    string s5 ("2.3*2");
    string s6 ("0.98 * 3");
    
    // s1 = calculate(s1,4);
    // s2 = calculate(s2,4);
    // s3 = calculate(s3,4);
    // s4 = calculate(s4,4);
    // s5 = calculate(s5,4);
    s6 = calculate(s6, 4);



    cout << t1 << " " << s1 << "\n";
    cout << t2 << " " << s2<< "\n";
    cout << t3 << " " << s3<< "\n";
    cout << t4 << " " << s4<< "\n";
    cout << t5 << " " << s5<< "\n";
    cout << s6 << "\n";
    SigFigs sf1("0.98");
    SigFigs sf2("3");

    cout << (sf1 * sf2).getSVal();
    
}