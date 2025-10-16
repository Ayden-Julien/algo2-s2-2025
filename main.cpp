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
    std::string n_us = "never used";
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
        int test_hash = inp_hash;
        int not_found = -1;        

        while (table[test_hash]->key != inp_key) {
            // never used means that it this hash couldn't be
            // past this test_hash
            if (table[test_hash]->status == n_us) {
                break;
            }
            // if table[test_hash] is occupied and is correct
            if ((table[test_hash]->key == inp_key) && (table[test_hash]->status == occu)) {
                return test_hash;
            }

            // management of itteration through table
            test_hash = (test_hash++) % num_keys;
            // if a full loop has been made, break
            if (test_hash == inp_hash) {
                break;
            }
        }
        // for cases of itterated whole loop and not found or 
        // found a never used slot
        return not_found;
    };

    void insertion(std::string inp_key) {
        int found_hash = find(inp_key);
        
        // already exists; do nothing
        if (found_hash != -1) {
            return;
        }

        int true_hash = hash(inp_key);
        int test_hash = true_hash;

        while (table[test_hash]->key != inp_key) {
            // valid slot found
            if (table[test_hash]->status != occu) {
                table[test_hash]->status = occu;
                table[test_hash]->key = inp_key;
                return;
            }

            // itteration and catching of weirdness to prevent inf loop
            test_hash = (test_hash++) % num_keys;
            // should never trigger
            if (test_hash == true_hash) {
                std::cout << "INSERTION ERROR" << std::endl;
                return;
            }
        }
        // should never trigger
        return;
    };

    void deletion(std::string inp_key) {
        
    };

};

int main() {
    // creating table
    h_table HashTable;

    // input
    std::string raw_input;
    getline(std::cin, raw_input);
    std::stringstream ss(raw_input);
    std::string input;
    std::vector<std::string> inputs;
    while (ss >> input) {
        inputs.push_back(input);
    }

    // alocating based off intructions
    
    

    return 0;
}

