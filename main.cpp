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

    // base AVL operations    
    int get_height(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        return node->height;
    }

    int get_balance(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int balance = get_height(node->left_branch) - get_height(node->right_branch);
        return balance;
    }

    // base rotations
    Node* rotate_left(Node* node) {
        Node* right_branch = node->right_branch;
        Node* right_left_branch = right_branch->left_branch;

        right_branch->left_branch = node;
        node->right_branch = right_left_branch;

        right_branch->height = std::max(get_height(right_branch->right_branch), get_height(right_branch->left_branch)) + 1;
        node->height = std::max(get_height(node->right_branch), get_height(node->left_branch)) + 1;

        return right_branch;
    }

    Node* rotate_right(Node* node) {
        Node* left_branch = node->left_branch;
        Node* left_right_branch = left_branch->right_branch;

        left_branch = node;
        node->left_branch = left_right_branch;

        left_branch->height = std::max(get_height(left_branch->right_branch), get_height(left_branch->left_branch)) + 1;
        node->height = std::max(get_height(node->right_branch), get_height(node->left_branch)) + 1;


        return left_branch;
    }

    // insertion and deletion
    Node* private_insertion(Node* current_node, int num) {
        // base case where valid empty slot is found
        if (current_node == nullptr) {
            current_node = new Node(num);
            return current_node;
        }

        // recursive cases where direction is chosen
        if (num < current_node->element) {
            current_node->left_branch = private_insertion(current_node->left_branch, num);
        }
        else if (num > current_node->element) {
            current_node->right_branch = private_insertion(current_node->right_branch, num);
        }
        // case where to_be_inserted already exists
        else {
            return current_node;
        }

        // balancing for if tree is traversed before placement

    };

    Node* private_deletion(Node* current_node, int num) {
        
    };

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
    AVL() {
        root = nullptr;
    };

    // public access of insertion and deletion
    void insertion(int num) {
        root = private_insertion(root, num);
    };

    void deletion(int num) {
        root = private_deletion(root, num);
    };

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