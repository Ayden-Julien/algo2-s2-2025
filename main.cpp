// assignment 3, Ayden Julien, a1848337
// g++ -std=c++11 -o main.out -O2 -Wall main.cpp

// hash table has 26 slots, 1 for every lower case letter of
// the alphabet
// total number of keys is at most 26,
// max key length of 10

// each slot has statuses:
// "never used",
// "tombstone",
// "occupied"

#include <vector>
#include <string>

class slot {
    private:
    std::string key;
    std::string status;

    public:
    slot() {
        key = "";
        status = "never used";
    };

    friend class table;

};

class table {
    private:


    public:
    

};

int main() {


    return 0;
}