// ADSA, assignment 2
// a1848337; Ayden Julien

// start w/empty AVL tree
// single input line of n modification moves
// (1 <= n <= 100)
// 
// valid moves:
// Aint; A followed by number (1 - 100); eg A3
// means insert number; if in tree do nothing
// Dint; D followed by number (1 - 100); eg D3
// meand delete number; if not in tree do nothing
//
// input followed by (this is not included in the mod moves)
// PRE; 
// POST; 
// IN; 
// check slides for specifics 

#include <string>
#include <iostream>

// node class for the binary tree
class Node {
    private:
    // base requirements to the node and tree
    int element;
    Node* right_branch;
    Node* left_branch;

    // for ease of tree balancing
    int height;

    // in place of a bunch of access functions
    friend class ALV;

    public:
    Node(int elem) {
        element = elem;
        right_branch = nullptr;
        left_branch = nullptr;
        height = 1;
    };
};

// AVL binary tree
class AVL {

};

int main() {


    return 0;
}