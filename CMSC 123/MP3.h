#include <string>

using namespace std;

class BigNum{
    public:
        string number;

        BigNum add(BigNum);

        BigNum();
        BigNum(string);
        string getNum();
};

BigNum fibonacci(unsigned int);