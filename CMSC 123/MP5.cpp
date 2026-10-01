#include "MP5.h"
#include <iostream>

using namespace std;

int gcd(int a, int b) {
if (a < 0)
a = -a;
if (b < 0)
b = -b;

if (b == 0)
return a;

return gcd(b, a % b);
}

MixedFraction::MixedFraction(){
whole = 0;
nume = 0;
deno = 1;
}
MixedFraction::MixedFraction(string s){
int spacePos = -1;
int slashPos = -1;

for (int i = 0; i < s.length(); i++){
if (s[i] == ' ')
spacePos = i;

else if (s[i] == '/')
slashPos = i;
}

if (slashPos == -1){
whole = stoi(s);
nume = 0;
deno = 1;
} else if (spacePos == -1){
whole = 0;

string n = s.substr(0, slashPos);
string d = s.substr(slashPos + 1);

nume = stoi(n);
deno = stoi(d);
} else{
string w = s.substr(0, spacePos);
string n = s.substr(spacePos + 1, slashPos - spacePos - 1);
string d = s.substr(slashPos + 1);

whole = stoi(w);
nume = stoi(n);
deno = stoi(d);
}

}

MixedFraction MixedFraction::add(MixedFraction b){
MixedFraction final;

int aNume = whole * deno + nume;
int bNume = b.whole * b.deno + b.nume;

final.nume = aNume * b.deno + bNume * deno;
final.deno = deno * b.deno;

int xgcd = gcd(final.nume, final.deno);

final.nume = final.nume / xgcd;
final.deno = final.deno / xgcd;

final.whole = final.nume / final.deno;
final.nume = final.nume % final.deno;
if (final.whole != 0 && final.nume < 0)
final.nume = -final.nume;

return final;
}
MixedFraction MixedFraction::minus(MixedFraction b){
MixedFraction final;

int aNume = whole * deno + nume;
int bNume = b.whole * b.deno + b.nume;

final.nume = aNume * b.deno - bNume * deno;
final.deno = deno * b.deno;

int xgcd = gcd(final.nume, final.deno);

final.nume = final.nume / xgcd;
final.deno = final.deno / xgcd;

final.whole = final.nume / final.deno;
final.nume = final.nume % final.deno;
if (final.whole != 0 && final.nume < 0)
final.nume = -final.nume;


return final;
}
MixedFraction MixedFraction::times(MixedFraction b){
MixedFraction final;

int aNume = whole * deno + nume;
int bNume = b.whole * b.deno + b.nume;

final.nume = aNume * bNume;
final.deno = deno * b.deno;

int xgcd = gcd(final.nume, final.deno);

final.nume = final.nume / xgcd;
final.deno = final.deno / xgcd;

final.whole = final.nume / final.deno;
final.nume = final.nume % final.deno;
if (final.whole != 0 && final.nume < 0)
final.nume = -final.nume;

return final;
}
MixedFraction MixedFraction::divide(MixedFraction b){
MixedFraction final;

int aNume = whole * deno + nume;
int bNume = b.whole * b.deno + b.nume;

final.nume = aNume * b.deno;
final.deno = deno * bNume;

int xgcd = gcd(final.nume, final.deno);

final.nume = final.nume / xgcd;
final.deno = final.deno / xgcd;

final.whole = final.nume / final.deno;
final.nume = final.nume % final.deno;
if (final.whole != 0 && final.nume < 0)
final.nume = -final.nume;

return final;
}

void MixedFraction::display(){
if (whole != 0)
cout << whole;

if (nume != 0){
if (whole != 0)
cout << " ";

cout << nume << "/" << deno;
}

if (whole == 0 && nume == 0)
cout << "0";
}