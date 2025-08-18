// Assignment 1
// 
// input: I1 I2 B; all in 1 line, in presented format
// I1 = inputNum1; can be from 0-100 digits long
// I2 = inputNum2; can be from 1-100 digits long
// B = base number of I1 and I2; can be from 2-10
// 
// output: X Y Z; all in 1 line, in presented format
// X = sum of I1 and I2; using school method
// Y = product of I1 and I2; using Karatsuba algorithm
// Z = ratio between I1 and I2; N/A; !! SET TO = 0 !!

// !! All operations must take place in the base given; not converted
// to an intermediary base, calculated, and then converted back !!

// potential note in lect2; 31:30

// compile command:
// g++ -std=c++11 -o main.out -O2 -Wall main.cpp

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// function for preforming school addition (Input1, Input2, Base)
string schoolAddition (string Inp1, string Inp2, string B) {
    // var setup
    int inp1_length = Inp1.length();
    int inp2_length = Inp2.length();
    int max_length = max(inp1_length, inp2_length);
    int base = stoi(B);

    int holder = 0;
    int inp1_digit = 0;
    int inp2_digit = 0;
    int carry = 0;
    int remainder;

    string output;

    // actual addition
    for (int i = 0; i < max_length; i++) {
        // fetching the i-th digit of both inp1 and inp2

        // the - '0' in the fist case of both if statements is to 
        // properly index the char to the number  
        if (i < inp1_length) {
            inp1_digit = Inp1[inp1_length - i - 1] - '0';
        } 
        else {
            inp1_digit = 0;
        }

        if (i < inp2_length) {
            inp2_digit = Inp2[inp2_length - i - 1] - '0';
        }
        else {
            inp2_digit = 0;
        }

        holder = inp1_digit + inp2_digit + carry;
        carry = holder / base;
        remainder = holder % base;

        output = to_string(remainder) + output;
    }

    // for if output has more digits than either inputs (overflow condition)
    if (carry > 0) {
        output = to_string(carry) + output;
    }

    return output;

};


// function required for karatsubaMultiplication
// Inp1 - Inp2; of base: Base
// presuming Inp1 > Inp2 because thats seems like a pain otherwise
string subtraction(string Inp1, string Inp2, string B) {
    int inp1_length = Inp1.length();
    int inp2_length = Inp2.length();
    int max_length = max(inp1_length, inp2_length);
    int base = stoi(B);

    int inp1_digit = 0;
    int inp2_digit = 0;
    int carry = 0;
    int holder = 0;

    string output;

    for (int i = 0; i < max_length; i ++) {
        if (i < inp1_length) {
            inp1_digit = Inp1[inp1_length - i - 1] - '0';
        }
        else {
            inp1_digit = 0;
        }

        if (i < inp2_length) {
            inp2_digit = Inp2[inp2_length - i - 1] - '0';
        }
        else {
            inp2_digit = 0;
        }

        holder = inp1_digit - inp2_digit + carry;
        
        if (holder < 0) {
            carry = -1;
            holder = holder + base;
        }
        else {
            carry = 0;
        }

        output = to_string(holder) + output;
    }
    
    return output;
};


// function for preforming karatsuba algo multiplication
// (a, b, base)
string karatsubaMultiplication(string a, string b, string B) {
    // karatsuba algo
    // (a1 * b1)*B^(2*k) +
    // ((a1 + a0) * (b1 + b0) - (a1 * b1 + a0 * b0)) * B^(k) +
    // (a0 * b0)
    
    int a_length = a.length();
    int b_length = b.length();

    string output = "0";

    // base case
    // to enable first funcitonal case of k = 1
    if (a_length == 1 || b_length == 1) {
        for (int i = 0; i < stoi(b); i++) {
            output = schoolAddition(output, a, B);
        }

        return output;
    }

    
    // establishment of recursive case vars
    int max_length = max(a_length, b_length);
    int k = max_length / 2;

    // ensuring same length of a and b so it doesnt bork itself
    // at the splitting stage
    if (a_length < max_length) {
        string preppended_zeros(max_length - a_length, '0');
        a = preppended_zeros + a;
        a_length = a.length();
    }
    if (b_length < max_length) {
        string preppended_zeros(max_length - b_length, '0');
        b = preppended_zeros + b;
        b_length = b.length();
    }

    // splitting a and b
    string a0 = a.substr(max_length - k);
    string a1 = a.substr(0, max_length - k);
    string b0 = b.substr(max_length - k);
    string b1 = b.substr(0, max_length - k);

    // recursive case
    // a1 * b1
    string section2 = karatsubaMultiplication(a1, b1, B);
    // (a1 + a0) * (b1 + b0)
    string section1 = karatsubaMultiplication((a1 + a0), (b1 + b0), B);
    // a0 * b0
    string section0 = karatsubaMultiplication(a0, b0, B);

    
    // post recursion processing 

    // middle section arithmetic
    section1 = subtraction(section1, schoolAddition(section2, section0, B), B);
    
    // preforming the multiples by base; equivalent to adding
    // zeros to the end
    string zeros_section2(2 * k, '0');
    section2 = section2 + zeros_section2;
    
    string zeros_section1(k, '0');
    section1 = section1 + zeros_section1;
    
    // section0 unchanged

    output = schoolAddition(schoolAddition(section2, section1, B), section0, B);
    
    return output;
};


int main() {
    // getting user input
    string Input1;
    string Input2;
    string Base;

    cin >> Input1 >> Input2 >> Base;

    // calling calculation functions
    string additionOutput = schoolAddition(Input1, Input2, Base);

    //string multiplicationOutput = karatsubaMultiplication(Input1, Input2, Base);
    string multiplicationOutput = subtraction(Input1, Input2, Base);

    // combining and then outputing
    string output = additionOutput + " "
                  + multiplicationOutput + " "
                  + "0";
    
    cout << output << endl;

    return 0;
};