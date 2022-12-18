#include <math.h>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <SigFigs>

using std::cout;
using std::stack;
using std::vector;
using std::string;
using std::stod;
using std::to_string;

class LatexFormatter() {
    SigFigs val;
    SigFigs uncertainty

    public:
        LatexFormatter(SigFigs val, SigFigs uncertainty) {
            this->val = val;
            this->uncertainty = uncertainty;
        }

        LatexFormatter operator +(LatexFormatter const &ot) const {
            string msg("");
            
            SigFigs tVal = val;
            SigFigs oVal = ot.val;

            SigFigs tUncertainty = uncertainty;
            SigFigs oUncertainty = ot.uncertainty;

            msg += 

            int sigfig1 = countSigFigsAfterDecimalPoint(s1);
            int sigfig2 = countSigFigsAfterDecimalPoint(s2);

            double sum = stod(s1) + stod(s2);

            int sigfigsum = countSigFigsAfterDecimalPoint(to_string(sum));

            int smallestSigFigCount = sigfig1 > sigfig2 ? sigfig2 : sigfig1;
            //cout << "Sum:" << sum << "\n";
            res.actualVal = sum;
            res.sVal= to_string(sum).substr(0,to_string(sum).size()-(sigfigsum - smallestSigFigCount));
            return res;
        }
}