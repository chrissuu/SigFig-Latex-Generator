#include <math.h>
#include <iostream>
#include "SigFigs.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

// double round_up(double value, int decimal_places)
// {
//     const double multiplier = std::pow(10.0, -1*decimal_places);
//     return std::round(value * multiplier) / multiplier;
// }

// void eraseZeros(string &arg)
// {
 
//     arg.erase(arg.find_last_not_of('0') + 1, std::string::npos);
//     arg.erase(arg.find_last_not_of('.') + 1, std::string::npos);
// }
// vector<string> roundPossiblesVector(double value, int actualSigFigsAfterDecimalCount, int sigFigsBeforeDecimalCount)
// {
//     int thisSigFigsAfterDP = countSigFigsAfterDecimalPoint(to_string(value));
//     vector<string> storeRet;

//     for (int i = actualSigFigsAfterDecimalCount; i > -sigFigsBeforeDecimalCount - 1; i--)
//     {

//         string temp = to_string(round_up(value, i));
//         eraseZeros(temp);
//         double val = round_up(value, i);
//         cout << "Temp: " << temp << "\n";
//         cout << "Val: " << val << "\n\n";

//         if (temp.find(".") != string::npos)
//         {
//             if (countSigFigsAfterDecimalPoint(temp) <= i)
//             {   int currCountSigs = countSigFigsAfterDecimalPoint(temp);
//                 for (int k = 0; k < i - currCountSigs; k++)
//                 {
//                     temp.append("0");
//                 }
//             }
//         }
//         storeRet.push_back(temp);
//     }

//     return storeRet;
// }

// void printVec(vector<string> v)
// {
//     for (auto s : v)
//     {
//         cout << s << "\n";
//     }
// }

int main()
{
//     int i = 10;
//     for (int k = -i; k < i + 1; k++)
//     {
//         std::cout << "I: " << k << " Val: " << round_up(126.89500, k) << "\n";
//     }
    // 5.33 * 7.88 = 41.764 = 42
    // double sigfigscounted = countSigFigs("41.764") - countSigFigsAfterDecimalPoint("41.764");
    // cout << sigfigscounted << "\n";
    SigFigs a("5.33");
    SigFigs b("7.88");

    SigFigs c = a * b;

    cout << c.getSVal() << "\n";

    // vector<string> res = roundPossiblesVector(0.895,3, 0);
    // printVec(res);

    cout << countSigFigs("42.000400") << "\n";
    cout << countDigitsAfterDP("42.000400") << "\n";

}