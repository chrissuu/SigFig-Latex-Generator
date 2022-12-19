#include <math.h>
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

double round_up(double value, int decimal_places)
{
    const double multiplier = std::pow(10.0, decimal_places);
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
        // cout << "copy sz: " << countSigFigsAfterDecimalPoint(copy) << "\n";
        // cout << "substr sz : " << (s.substr(0,in)).size() << "\n";
        // cout << "in sz : " << in << "\n";
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

class SigFigs
{

    string sVal;

public:
    SigFigs(string s = "0")
    {
        sVal = s;
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

        return wholePart + fractionalPart;
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

        return wholePart + fractionalPart;
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

        int roundDegree = smallestSigFigCount - sigfigprod;
        for (int i = -roundDegree - 2; i < roundDegree + 2; i++)
        {
            string temp = to_string(round_up(prod, i));
            if (countSigFigs(temp) == smallestSigFigCount)
            {
                res.sVal = temp;
            }
        }

        if (res.sVal == "0")
        {
            if (prod < 1)
            {
                res.sVal = to_string(prod).substr(0, smallestSigFigCount + 2);
            }
            else
            {
                res.sVal = to_string(prod).substr(0, smallestSigFigCount + 1);
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
        for (int i = -roundDegree - 2; i < roundDegree + 2; i++)
        {
            string temp = to_string(round_up(quot, i));
            if (countSigFigs(temp) == smallestSigFigCount)
            {
                res.sVal = temp;
            }
        }

        if (res.sVal == "0")
        {
            if (quot < 1)
            {
                res.sVal = to_string(quot).substr(0, smallestSigFigCount + 2);
            }
            else
            {
                res.sVal = to_string(quot).substr(0, smallestSigFigCount + 1);
            }
        }

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

        return wholePart + fractionalPart;
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

        return wholePart + fractionalPart;
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
        for (int i = -roundDegree - 2; i < roundDegree + 2; i++)
        {
            string temp = to_string(round_up(quot, i));
            if (countSigFigs(temp) == smallestSigFigCount)
            {
                res.sVal = temp;
            }
        }

        if (res.sVal == "0")
        {
            if (quot < 1)
            {
                res.sVal = to_string(quot).substr(0, smallestSigFigCount + 2);
            }
            else
            {
                res.sVal = to_string(quot).substr(0, smallestSigFigCount + 1);
            }
        }

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
        for (int i = -roundDegree - 2; i < roundDegree + 2; i++)
        {
            string temp = to_string(round_up(quot, i));
            if (countSigFigs(temp) == smallestSigFigCount)
            {
                res.sVal = temp;
            }
        }

        if (res.sVal == "0")
        {
            if (quot < 1)
            {
                res.sVal = to_string(quot).substr(0, smallestSigFigCount + 2);
            }
            else
            {
                res.sVal = to_string(quot).substr(0, smallestSigFigCount + 1);
            }
        }

        return res;
    }

    string getSVal()
    {
        return sVal;
    }
};


SigFigs pow(SigFigs base, double exponent)
{
    double ret = pow(stod(base.getSVal()), exponent);
    return SigFigs(to_string(ret));
}

int main()
{
   
    // cout << countSigFigs(s);
    SigFigs a("0.122");
    SigFigs b("0.139909");
    SigFigs d("129.45086");
    string s("0.122");
    SigFigs c = b/a;
    SigFigs lam = b/s;
    cout << c.getSVal() << x
    cout << lam.getSVal() << x
}