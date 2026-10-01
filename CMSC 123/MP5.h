#include <string>
using namespace std;

class Fraction{
public:
int nume, deno;
};

class MixedFraction : public Fraction{
public:
int whole;

MixedFraction();
MixedFraction(string);

MixedFraction add(MixedFraction);
MixedFraction minus(MixedFraction);
MixedFraction times(MixedFraction);
MixedFraction divide(MixedFraction);

void display();
};