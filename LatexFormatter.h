#include <math.h>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <SigFigs.h>



using std::cout;
using std::stack;
using std::vector;
using std::string;
using std::stod;
using std::to_string;

const string pm("\pm");

class LatexFormatter {
    SigFigs val;
    SigFigs uncertainty;
    

    public:
        LatexFormatter(SigFigs val, SigFigs uncertainty) {
            this->val = val;
            this->uncertainty = uncertainty;
        }

        LatexFormatter format(vector<string> args) const {
            string msg("");
            
            for(int i = 0; i<args.size(); i++) {
                msg += " " + args[i];
                if(args[i] == "=") msg+= "\n";
            }
            
            
        }
};