#include <math.h>
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include "SigFigs.h"

using std::cout;
using std::stack;
using std::stod;
using std::string;
using std::to_string;
using std::vector;




class ErrorComputer
{
    SigFigs val;
    SigFigs uncertainty;
    vector<string> computationLayers;

public:
    ErrorComputer(SigFigs val, SigFigs uncertainty)
    {
        this->val = val;
        this->uncertainty = uncertainty;
    }

    ErrorComputer(double val, double uncertainty) 
    {
        this->val = SigFigs(to_string(val));
        this->uncertainty = SigFigs(to_string(uncertainty));
    }

    ErrorComputer operator +(ErrorComputer const &ot) const {

            SigFigs val("0");
            SigFigs uncertainty("0");

            SigFigs ecVal1 = this->val;
            SigFigs ecVal2 = ot.val;

            SigFigs ecError1 = this->uncertainty;
            SigFigs ecError2 = ot.uncertainty;

            val = ecVal1 + ecVal2;
            uncertainty = pow((pow(ecError1,2) + pow(ecError2,2)),0.5);
            
            

            return ErrorComputer(val,uncertainty);


    }

    ErrorComputer operator -(ErrorComputer const &ot) const {

            SigFigs val("0");
            SigFigs uncertainty("0");

            SigFigs ecVal1 = this->val;
            SigFigs ecVal2 = ot.val;

            SigFigs ecError1 = this->uncertainty;
            SigFigs ecError2 = ot.uncertainty;

            val = ecVal1 - ecVal2;
            uncertainty = pow((pow(ecError1,2) + pow(ecError2,2)),0.5);
            
            

            return ErrorComputer(val,uncertainty);


    }

    ErrorComputer operator *(ErrorComputer const &ot) const {

            SigFigs val("0");
            SigFigs uncertainty("0");

            SigFigs ecVal1 = this->val;
            SigFigs ecVal2 = ot.val;

            SigFigs ecError1 = this->uncertainty/ecVal1;
            SigFigs ecError2 = ot.uncertainty/ecVal2;

            val = ecVal1 * ecVal2;
            uncertainty = val * pow((pow(ecError1,2) + pow(ecError2,2)),0.5);
            
            

            return ErrorComputer(val,uncertainty);


    }

    ErrorComputer operator /(ErrorComputer const &ot) const {

            SigFigs val("0");
            SigFigs uncertainty("0");

            SigFigs ecVal1 = this->val;
            SigFigs ecVal2 = ot.val;

            SigFigs ecError1 = this->uncertainty/ecVal1;
            SigFigs ecError2 = ot.uncertainty/ecVal2;

            val = ecVal1 / ecVal2;
            uncertainty = val * pow((pow(ecError1,2) + pow(ecError2,2)),0.5);
            
            

            return ErrorComputer(val,uncertainty);


    }

    ErrorComputer operator *(string const &ot) {
        SigFigs val("0");
            SigFigs uncertainty("0");

            SigFigs ecVal = this->val;

            SigFigs ecError = this->uncertainty;

            val = ecVal * ot;
            uncertainty = uncertainty * ot;

            
            

            return ErrorComputer(val,uncertainty);


    }

    ErrorComputer operator ^(double const &ot) {
        SigFigs val = pow(this->val, ot);
        SigFigs error =  SigFigs(to_string(ot)) * this->uncertainty* pow(this->val, ot-1);

        return ErrorComputer(val, error);
    }

    double getVal(){
        return stod(val.getSVal());
    }

    double getUncertainty() {
        return stod(uncertainty.getSVal());
    }

    

    
};


ErrorComputer pow(ErrorComputer base, double exponent) {
    double val = pow(base.getVal(), exponent);
    double error = base.getUncertainty() * exponent * pow(base.getVal(), exponent-1);

    return ErrorComputer(val, error);
}

// double round_up(double value, int decimal_places)
// {
//     const double multiplier = std::pow(10.0, decimal_places);
//     return std::round(value * multiplier) / multiplier;
// }

// int main() {
//     int c = 5;
//     double val = 174.4973;
//     for(int i = -c; i<c; i++) {
//         cout << round_up(val, i) << "\n";
//     }
//     // ErrorComputer ec1(103, 0.5);
//     // ErrorComputer ec2(405, 0.5);

//     // cout <<"Val: " << (ec1 + ec2).getVal();
//     // cout <<"Uncertainty: " << (ec1 + ec2).getUncertainty();

// }