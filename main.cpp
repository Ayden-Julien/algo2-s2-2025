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

    public:
    Node(int elem) {
        element = elem;
        right_branch = nullptr;
        left_branch = nullptr;
        height = 1;
    };

    // in place of a bunch of access functions
    friend class AVL;
};

// AVL binary tree
class AVL {
    private:
    Node* root;

    // varying traversal methods
    void private_preorder(Node* root) {
        if (root != nullptr) {
            std::cout << root->element << " ";
            private_preorder(root->left_branch);
            private_preorder(root->right_branch);
        }
    };

    void private_postorder(Node* root) {
        if (root != nullptr) {
            private_postorder(root->left_branch);
            private_postorder(root->right_branch);
            std::cout << root->element << " ";
        }
    };

    void private_inorder(Node* root) {
        if (root != nullptr) {
            private_inorder(root->left_branch);
            std::cout << root->element << " ";
            private_inorder(root->right_branch);
        }
    };

    public:

    // the public access of the traversal methods
    void preorder() {
        if (root == nullptr) {
            std::cout << "EMPTY";
        }
        else {
            private_preorder(root);
        }
    }

    void postorder() {
        if (root == nullptr) {
            std::cout << "EMPTY";
        }
        else {
            private_postorder(root);
        }
    }

    void indorder() {
        if (root == nullptr) {
            std::cout << "EMPTY";
        }
        else {
            private_inorder(root);
        }
    }
};

int main() {
    AVL tree;

    return 0;
}