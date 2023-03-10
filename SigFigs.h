#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <cmath>

using std::ceil;
using std::cout;
using std::exception;
using std::floor;
using std::stack;
using std::stod;
using std::string;
using std::to_string;
using std::vector;

#define x "\n";

bool isZero(string args)
{
    bool f = false;
    for (int i = 0; i < args.size(); i++)
    {
        if (args[i] == '0')
        {
            continue;
        }
        else if (args[i] == '.')
        {
            continue;
        }
        else
        {
            f = true;
        }
    }
    return f;
}
double round_up(double value, int decimal_places)
{
    const double multiplier = std::pow(10.0, -1 * decimal_places);
    return std::round(value * multiplier) / multiplier;
}

int countSigFigsAfterDecimalPoint(string s)
{
    int sigFigs = 0;
    // cout<<s << "\n";
    int in = s.find(".");
    if (in == string::npos)
    {
        return 0;
    }
    s = s.substr(s.find(".") + 1, s.size());
    // cout<<s << "\n";

    int sz = s.size();
    int zeroCounter = 0;
    while (s[0] == '0')
    {

        s = s.substr(1, s.size());
        // cout<<s << "\n";
        zeroCounter++;
        // cout<<zeroCounter << "\n";
    }
    // cout<<s << "\n";
    if (zeroCounter == sz)
    {
        sigFigs = zeroCounter;
    }
    else
    {
        sigFigs = s.size();
    }
    return sigFigs;
}

int countSigFigs(string s)
{
    string copy = s;
    // cout<<copy << "\n";
    int sigFigs = 0;
    // cout<<s << "\n";
    int in = s.find(".");
    int sz = s.size();

    if (in == string::npos)
    {
        while (s[s.size() - 1] == '0')
        {
            s = s.substr(0, s.size() - 1);
        }
    }
    else
    {
        string t("0");

        if (((s.substr(0, in)).size() == 1) && ((s.substr(0, in)) == t))
        {
            return countSigFigsAfterDecimalPoint(copy);
        }
        else
        {
            return (s.substr(0, in)).size() + countSigFigsAfterDecimalPoint(copy);
        }
    }
    return s.size();
}


void eraseZeros(string &arg)
{

    arg.erase(arg.find_last_not_of('0') + 1, std::string::npos);
    // arg.erase(arg.find_last_not_of('.') + 1, std::string::npos);
}
int countDigitsAfterDP(string s) {
    if(s.find(".")==string::npos) {
        return 0;
    }

    return s.substr(s.find(".")+1, s.size()).size();
}
bool dotExists(vector<string> arg) {
    bool exists = false;
    for (auto s: arg){ 
        if(s.find(".")!=string::npos) {
            exists = true;
        }
    }
    return exists;
}
vector<string> roundPossiblesVector(double value, int actualSigFigsAfterDecimalCount, int sigFigsBeforeDecimalCount)
{
    int thisSigFigsAfterDP = countSigFigsAfterDecimalPoint(to_string(value));
    vector<string> storeRet;

    for (int i = actualSigFigsAfterDecimalCount; i > -sigFigsBeforeDecimalCount - 1; i--)
    {

        string temp = to_string(round_up(value, i));
        eraseZeros(temp);
        double val = round_up(value, i);
        cout << "I: " << i << "\n";
        cout << "Temp: " << temp << "\n";
        cout << "Val: " << val << "\n";
        
        if (temp.find(".") != string::npos)
        {
            if (countSigFigsAfterDecimalPoint(temp) <= i)
            {
                int currCountSigs = countSigFigsAfterDecimalPoint(temp);
                for (int k = 0; k < i - currCountSigs; k++)
                {
                    temp.append("0");
                }
            }
        }
        storeRet.push_back(temp);
        cout << "Temp final: " << temp << "\n\n";
    }
    
    

    return storeRet;
}
void printVec(vector<string> v)
{
    for (auto s : v)
    {
        cout << s << "\n";
    }
}
class SigFigs
{

    string sVal;
    double val;

public:
    SigFigs(string s = "0")
    {
        sVal = s;
        // val = stod(sVal);
    }

    SigFigs operator+(SigFigs const &ot) const
    {
        SigFigs res("0");
        string s1 = this->sVal;
        string s2 = ot.sVal;

        int sigfig1 = countSigFigsAfterDecimalPoint(s1);
        int sigfig2 = countSigFigsAfterDecimalPoint(s2);

        double sum = stod(s1) + stod(s2);

        int sigfigsum = countSigFigsAfterDecimalPoint(to_string(sum));

        int smallestSigFigCount = sigfig1 > sigfig2 ? sigfig2 : sigfig1;

        string s = to_string(sum);
        int in = s.find(".");
        string wholePart = s.substr(0, in + 1);
        string fractionalPart = s.substr(in + 1, s.size()).substr(0, smallestSigFigCount);

        res.sVal = wholePart + fractionalPart;
        res.val = stod(res.sVal);
        return res;
    }

    SigFigs operator-(SigFigs const &ot) const
    {
        SigFigs res("0");
        string s1 = this->sVal;
        string s2 = ot.sVal;

        int sigfig1 = countSigFigsAfterDecimalPoint(s1);
        int sigfig2 = countSigFigsAfterDecimalPoint(s2);

        double sum = stod(s1) - stod(s2);

        int sigfigsum = countSigFigsAfterDecimalPoint(to_string(sum));

        int smallestSigFigCount = sigfig1 > sigfig2 ? sigfig2 : sigfig1;

        string s = to_string(sum);
        int in = s.find(".");
        string wholePart = s.substr(0, in + 1);
        string fractionalPart = s.substr(in + 1, s.size()).substr(0, smallestSigFigCount);

        res.sVal = wholePart + fractionalPart;
        res.val = stod(res.sVal);
        return res;
    }

    SigFigs operator*(SigFigs const &ot) const
    {
        SigFigs res("0");
        string s1 = this->sVal;
        string s2 = ot.sVal;

        int sigfig1 = countSigFigs(s1);
        int sigfig2 = countSigFigs(s2);

        double prod = stod(s1) * stod(s2);

        int smallestSigFigCount = sigfig1 > sigfig2 ? sigfig2 : sigfig1;

        int sigfigprod = countSigFigs(to_string(prod));
        int sigfigAfterDPProd = countSigFigsAfterDecimalPoint(to_string(prod));
        int digitsAfterDPProd = countDigitsAfterDP(to_string(prod));

        cout << to_string(prod) << "\n";
        vector<string> storeRet = roundPossiblesVector(prod, digitsAfterDPProd, sigfigprod - sigfigAfterDPProd);
        cout << "Smallest sigfig count: " << smallestSigFigCount << "\n";
        cout << "# sigfigs before dp: " << sigfigprod - sigfigAfterDPProd << "\n";
        // printVec(storeRet);
        for (auto s : storeRet)
        {
            if (countSigFigs(s) == smallestSigFigCount)
            {
                res.sVal = s;
            }
        }

        return res;
    }

    SigFigs operator/(SigFigs const &ot) const
    {
        SigFigs res("0");
        string s1 = this->sVal;
        string s2 = ot.sVal;

        int sigfig1 = countSigFigs(s1);
        int sigfig2 = countSigFigs(s2);
        SigFigs und("undefined");

        if (stod(s2) == 0)
        {
            return und;
        }
        double quot = stod(s1) / stod(s2);

        int smallestSigFigCount = sigfig1 > sigfig2 ? sigfig2 : sigfig1;
        int sigfigprod = countSigFigs(to_string(quot));

        int roundDegree = smallestSigFigCount - sigfigprod;
        string temp = to_string(round_up(quot, roundDegree));

        return res;
    }
    SigFigs operator+(string const &ot) const
    {
        SigFigs res("0");
        string s = this->sVal;

        int sigfig1 = countSigFigsAfterDecimalPoint(s);
        int sigfig2 = countSigFigsAfterDecimalPoint(ot);

        double sum = stod(s) + stod(ot);

        int sigfigsum = countSigFigsAfterDecimalPoint(to_string(sum));

        int smallestSigFigCount = sigfig1 > sigfig2 ? sigfig2 : sigfig1;

        string sumstr = to_string(sum);
        int in = sumstr.find(".");
        string wholePart = sumstr.substr(0, in + 1);
        string fractionalPart = sumstr.substr(in + 1, sumstr.size()).substr(0, smallestSigFigCount);
        res.sVal = wholePart + fractionalPart;
        res.val = stod(res.sVal);
        return res;
    }
    SigFigs operator-(string const &ot) const
    {
        SigFigs res("0");
        string s = this->sVal;

        int sigfig1 = countSigFigsAfterDecimalPoint(s);
        int sigfig2 = countSigFigsAfterDecimalPoint(ot);

        double sum = stod(s) - stod(ot);

        int sigfigsum = countSigFigsAfterDecimalPoint(to_string(sum));

        int smallestSigFigCount = sigfig1 > sigfig2 ? sigfig2 : sigfig1;

        string sumstr = to_string(sum);
        int in = sumstr.find(".");
        string wholePart = sumstr.substr(0, in + 1);
        string fractionalPart = sumstr.substr(in + 1, sumstr.size()).substr(0, smallestSigFigCount);

        res.sVal = wholePart + fractionalPart;
        res.val = stod(res.sVal);
        return res;
    }
    SigFigs operator*(string const &ot) const
    {
        SigFigs res("0");
        string s1 = this->sVal;

        int sigfig1 = countSigFigs(s1);
        int sigfig2 = countSigFigs(ot);
        SigFigs und("undefined");

        if (stod(ot) == 0)
        {
            return und;
        }
        double quot = stod(s1) * stod(ot);

        int smallestSigFigCount = sigfig1 > sigfig2 ? sigfig2 : sigfig1;
        int sigfigprod = countSigFigs(to_string(quot));

        int roundDegree = smallestSigFigCount - sigfigprod;
        string temp = to_string(round_up(quot, roundDegree));

        res.val = stod(res.sVal);
        return res;
    }
    SigFigs operator/(string const &ot) const
    {
        SigFigs res("0");
        string s1 = this->sVal;

        int sigfig1 = countSigFigs(s1);
        int sigfig2 = countSigFigs(ot);
        SigFigs und("undefined");

        if (stod(ot) == 0)
        {
            return und;
        }
        double quot = stod(s1) / stod(ot);

        int smallestSigFigCount = sigfig1 > sigfig2 ? sigfig2 : sigfig1;
        int sigfigprod = countSigFigs(to_string(quot));

        int roundDegree = smallestSigFigCount - sigfigprod;

        string temp = to_string(round_up(quot, roundDegree));
        res.sVal = temp;

        return res;
    }

    string getSVal()
    {
        return sVal;
    }

    double getVal()
    {
        return val;
    }
};

SigFigs pow(SigFigs base, double exponent)
{
    double ret = pow(stod(base.getSVal()), exponent);
    return SigFigs(to_string(ret));
}

// int main()
// {

//     // cout << countSigFigs(s);
//     SigFigs a("0.980000");
//     SigFigs b("3.000000");
//     SigFigs d("129.45086");
//     string s("0.122");
//     SigFigs c = a * b;
//     SigFigs lam = b / s;
//     cout << c.getSVal() << x cout << c.getVal() << x cout << lam.getSVal() << x
// }