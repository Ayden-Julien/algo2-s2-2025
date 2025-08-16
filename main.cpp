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

    int inp1_digit = 0;
    int inp2_digit = 0;

    // actual addition
    for (int i = 0; i < max_length; i++) {
        // fetching the i-th digit of both inp1 and inp2
        
        // finding the i-th digit in input1, with error catcher
        if (i < inp1_length) {
            inp1_digit = Inp1[inp1_length - i - 1];
        } 
        else {
            inp1_digit = 0;
        }

        // finding the i-th digit in input2, with error catcher
        if (i < inp2_length) {
            inp2_digit = Inp2[inp1_length - i - 1];
        }
        else {
            inp2_digit = 0;
        }

        
    }

};

int main() {
    // getting user input
    string Input1; // input1
    string Input2; // input2
    string Base; // base

    cin >> Input1 >> Input2 >> Base;

    string additionOutput = schoolAddition(Input1, Input2, Base);

    // processing user input into something usable

    // not sure if ^ is required

    return;
};