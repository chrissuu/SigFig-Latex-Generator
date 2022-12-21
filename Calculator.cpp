#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using std::cout;
using std::vector;
using std::string;
using std::find;
const vector<char> storeDelim = {'-', '+', '^', '/', '*', '(', ')'};
void normalizeString(string &args) {
    while(args.find(" ")!=string::npos) {
        args= args.substr(0, args.find(" ")) + args.substr(args.find(" ") + 1, args.size());
    }
}

string expandAroundIndex(string args, int index) {
    vector<char> copyStoreDelim = storeDelim;
    copyStoreDelim.erase(find(copyStoreDelim.begin(), copyStoreDelim.end(), args[index]));
    int indexBegin = 0;
    for(int i = index-1; i>=0; i--) {
        while(find(copyStoreDelim.begin(), copyStoreDelim.end(),args[i]) ==copyStoreDelim.end()) {
            indexBegin =i;
        }
    }

    int indexEnd = 0;
    for(int i = index+1; i<args.size(); i++) {
        while(find(copyStoreDelim.begin(), copyStoreDelim.end(),args[i]) ==copyStoreDelim.end()) {
            indexEnd=i; 
        }
    }

    return args.substr(indexBegin, index) + args.substr(index, indexEnd);
}
// string calculate(string args, int priority) {
//     normalizeString(args);
//     if(priority ==4) {
//         // vector<string> s;
//         while(args.find_last_of("(")!=string::npos){
//             string temp = args.substr(args.find_last_of("("),args.size());
//             temp = temp.substr(1,temp.find(")")-1);
//             args = args.substr(0,args.find_last_of("(")) +calculate(temp,4) + args.substr(args.find(")")+1,args.size());
//             return calculate(args, 3);
//         }

//         calculate(args , 3);
//     }

//     if(priority ==3) {
//         while(args.find("^")!=string::npos) {
//             string temp = args.substr(args.find("^")-1, args.find("^")+1);
            
//         }
//     }
// }


int main() {
    string t("1.333- (56.19 + 9311.23) * 9.827");
    cout << expandAroundIndex(t, t.find("+")) << "\n";
    string s("((a+b)*c) + (9+11*3)" );
    normalizeString(s);
    cout << s << "\n";
    string temp = s.substr(s.find_last_of("("),s.size());
    temp = temp.substr(1,temp.find(")")-1);
    cout << temp;
}