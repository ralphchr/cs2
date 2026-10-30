#include <stack>
#include <iomanip>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int main(){
    stack<double> s;
    string input;
    getline(cin, input);
    stringstream ss(input);
    string item = "";
    double a, b;
    double final;

    while(ss >> item){
        if (item == "+"){
            a = s.top();
            s.pop();
            b = s.top();
            s.pop();
            final = b + a;
            s.push(final);
        }
        else if (item == "-"){
            a = s.top();
            s.pop();
            b = s.top();
            s.pop();
            final = b - a;
            s.push(final);
        }
        else if (item == "*"){
            a = s.top();
            s.pop();
            b = s.top();
            s.pop();
            final = a * b;
            s.push(final);
        }
        else if (item == "/"){
            a = s.top();
            s.pop();
            b = s.top();
            s.pop();
            final = b / a;
            s.push(final);
        }
        else{
            s.push(stod(item));
        }

    }

    cout<<fixed<<setprecision(2)<<s.top()<<endl;


}