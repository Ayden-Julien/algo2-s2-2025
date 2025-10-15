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
    int hash(std::string inp) {
        // - 'a' to allign char to int range 0 - 25
        int hashed = inp.back() - 'a';
        return hashed;
    }

    int find(std::string inp_key) {
        int inp_hash = hash(inp_key);
        if (table[inp_hash]->status == "occupied") {
            return 
        }
        else if (table[inp_hash]->status != "occupied") {
            return -1;
        }
    };

    void insertion(std::string inp) {

    };

    void deletion(std::string inp) {
        int slot_status = find(inp);
        
    };

};

int main() {


    return 0;
}

