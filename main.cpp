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
#include <iostream>
#include <sstream>

class h_slot {
    private:
    std::string key;
    std::string status;

    public:
    h_slot() {
        key = "";
        status = "never used";
    };
    friend class h_table;

};

class h_table {
    private:
    h_slot** table;
    // for the 26 letters
    int num_keys = 26;

    // valid changed states
    std::string occu = "occupied";
    std::string tomb = "tombstone";

    public:
    // creation deletion
    h_table() {
        table = new h_slot*[num_keys];
        // setting each of the letter slots to be blank
        for (int i = 0; i < num_keys; i++) {
            table[i] = new h_slot();
        }
    };

    ~h_table() {
        for (int i = 0; i < num_keys; i++) {
            delete table[i];
        }
        delete[] table;
    };

    // functions
    int hash(std::string inp_key) {
        // - 'a' to allign char to int range 0 - 25
        int hashed = inp_key.back() - 'a';
        return hashed;
    }

    int find(std::string inp_key) {
        int inp_hash = hash(inp_key);
        if (table[inp_hash]->status == occu) {
            return -1;
        }
        else if (table[inp_hash]->status != occu) {
            return inp_hash;
        }
    };

    void insertion(std::string inp_key) {
        int found_hash = find(inp_key);
        if (found_hash == -1) {
            return;
        }
        else {
            table[found_hash]->status = occu;
            table[found_hash]->key = inp_key;
        }
    };

    void deletion(std::string inp) {
        int found_hash = find(inp);
        // slot is already empty
        if (found_hash == -1) {
            return;
        }
        // slot needs to be emptied
        else {
            table[found_hash]->status = tomb;
            return;
        }
    };

};

int main() {
    

    return 0;
}

