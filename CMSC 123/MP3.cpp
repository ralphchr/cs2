#include <iostream>
#include "MP3.h"
#include <string>

using namespace std;

BigNum BigNum::add(BigNum x){
    BigNum final;
    final.number = "";

    int len1 = number.length() - 1;
    int lenx = x.number.length() - 1;
    int carry = 0;

    while (len1 >= 0 || lenx >= 0 || carry > 0){
        int currentsum = carry;

        if (len1 >= 0){
            currentsum += number[len1] - '0';
            len1--;
        }
        if (lenx >= 0){
            currentsum += x.number[lenx] - '0';
            lenx--;
        }

        final.number += (currentsum % 10) + '0';

        carry = currentsum / 10;

    }

    int l = 0, r = final.number.length() - 1;

    while (l < r){
        char temp = final.number[l];
        final.number[l] = final.number[r];
        final.number[r] = temp;
        l++;
        r--;
    }

    return final;
}

BigNum::BigNum(){
    number = "0";
}

BigNum::BigNum(string x){
    if (x.length() == 0)
        number = "0";

    for (int i = 0; i < x.length(); i++){
        if (x[i] < '0' || x[i] > '9'){
            number = "0";
            break;
        }
    }

    number = x;
}

string BigNum::getNum(){
    return number;
}

BigNum fibonacci(unsigned int x){
    BigNum a("0");
    BigNum b("1");
    BigNum c;

    if (x == 0)
        return a;
    else if (x == 1)
        return b;
    else {
        for (int i = 1; i < x; i++){
            c = a.add(b);
            a = b;
            b = c;
        }

        return b;
    }

}