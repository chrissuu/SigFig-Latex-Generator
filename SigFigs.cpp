#include <math.h>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <cmath>

using std::cout;
using std::stack;
using std::vector;
using std::string;
using std::stod;
using std::to_string;
using std::floor;
using std::ceil;

int countSigFigsAfterDecimalPoint(string s){
    int sigFigs =0;
    //cout<<s << "\n";
    int in = s.find(".");
    if(in == string::npos) {
        return 0;
    }
    s = s.substr(s.find(".")+1,s.size());
    //cout<<s << "\n";

    int sz  =s.size();
    int zeroCounter = 0;
    while(s[0]=='0') {
        
        s = s.substr(1, s.size());
        //cout<<s << "\n";
        zeroCounter++;
        //cout<<zeroCounter << "\n";
    
    }
    //cout<<s << "\n";
    if(zeroCounter == sz) {
        sigFigs = zeroCounter;
    } else {
        sigFigs = s.size();
    }
    return sigFigs;
}

int countSigFigs(string s){
    string copy = s;
    //cout<<copy << "\n";
    int sigFigs =0;
    //cout<<s << "\n";
    int in = s.find(".");
    int sz  = s.size();
    
    
    if(in == string::npos) {
        while(s[s.size()-1]=='0') {
            s = s.substr(0,s.size()-1);
        }
        
    } else {
        string t("0");
        //cout << "copy sz: " << countSigFigsAfterDecimalPoint(copy) << "\n";
        //cout << "substr sz : " << (s.substr(0,in)).size() << "\n";
        //cout << "in sz : " << in << "\n";
        if(((s.substr(0,in)).size()==1) && ((s.substr(0,in))==t)) {
            return countSigFigsAfterDecimalPoint(copy);
        } else {
            return (s.substr(0,in)).size() + countSigFigsAfterDecimalPoint(copy);
        }
    }
    return s.size();
}

class SigFigs {
    double actualVal; 
    string sVal;
    public:
        SigFigs(string s = "0", double actualVal = 0){ 
            this->actualVal = actualVal;
            sVal = s;
        }

        SigFigs operator +(SigFigs const &ot) const {
            SigFigs res("0", 0);
            string s1 = this->sVal;
            string s2 = ot.sVal;

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

        SigFigs operator -(SigFigs const &ot) const {
            SigFigs res("0", 0);
            string s1 = this->sVal;
            string s2 = ot.sVal;

            int sigfig1 = countSigFigsAfterDecimalPoint(s1);
            int sigfig2 = countSigFigsAfterDecimalPoint(s2);

            double diff = stod(s1) - stod(s2);

            int sigfigdiff = countSigFigsAfterDecimalPoint(to_string(diff));

            int smallestSigFigCount = sigfig1 > sigfig2 ? sigfig2 : sigfig1;
            //cout << "Sum:" << sum << "\n";
            res.actualVal = diff;
            res.sVal= to_string(diff).substr(0,to_string(diff).size()-(sigfigdiff - smallestSigFigCount));
            return res;
        }

        SigFigs operator *(SigFigs const &ot) const {
            SigFigs res("0", 0);
            string s1 = this->sVal;
            string s2 = ot.sVal;

            int sigfig1 = countSigFigs(s1);
            int sigfig2 = countSigFigs(s2);

            double prod = stod(s1) * stod(s2);

            int smallestSigFigCount = sigfig1 > sigfig2 ? sigfig2 : sigfig1;
         
            res.actualVal = prod;
            cout << "Smallest sigfigcount: " << smallestSigFigCount << "\n";
            if(prod < 1) {
                res.sVal= to_string(prod).substr(0,smallestSigFigCount+2);
            } else {
                res.sVal= to_string(prod).substr(0,smallestSigFigCount+1);
            }
            return res;
        }

        SigFigs operator /(SigFigs const &ot) const {
            SigFigs res("0", 0);
            string s1 = this->sVal;
            string s2 = ot.sVal;

            int sigfig1 = countSigFigs(s1);
            int sigfig2 = countSigFigs(s2);

            double quot = stod(s1) / stod(s2);

            int smallestSigFigCount = sigfig1 > sigfig2 ? sigfig2 : sigfig1;
        
            res.actualVal = quot;
            
            // for(int i = 0; i<to_string(quot).size(); i++) {
            // this part needs some edits.
            // edge cases being when the quot/ prod is less than 1. 
            // }
            if(quot < 1) {
                res.sVal= to_string(quot).substr(0,smallestSigFigCount+2);
            } else {
                res.sVal= to_string(quot).substr(0,smallestSigFigCount+1);
            }
            return res;
        }


        string getSVal() {
            return sVal;
        }

        double getActualVal() {
            return actualVal;
        }


};



int main() {

    string s("0");
    //cout << countSigFigs(s);
    cout << countSigFigs("0.123") << "\n";
    SigFigs a("0.122");
    SigFigs b("0.123");
    SigFigs d("129.1134");
    SigFigs c = d/b;
    cout << c.getSVal() << "\n";
    cout << "Actual val" << c.getActualVal()<< "\n";
    
}