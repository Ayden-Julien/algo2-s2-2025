// ADSA, assignment 2
// a1848337; Ayden Julien

// comp command:
// g++ -std=c++11 -o main.out -O2 -Wall main.cpp

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
#include <sstream>
#include <vector>

using namespace std;

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
    Node(int num) {
        element = num;
        right_branch = nullptr;
        left_branch = nullptr;
        // nullptr height being 0
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
    // mostly to compensate for the nullptr case  
    int get_height(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        return node->height;
    }

    // pos if leftside > rightside
    // neg if rightside > leftside
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

        // going leaf to root to propagate height
        node->height = max(get_height(node->right_branch), get_height(node->left_branch)) + 1;
        right_branch->height = max(get_height(right_branch->right_branch), get_height(right_branch->left_branch)) + 1;

        // returning right_branch acts equivalent to changing the 
        // pointer in the above (if existing) node
        return right_branch;
    }

    Node* rotate_right(Node* node) {
        Node* left_branch = node->left_branch;
        Node* left_right_branch = left_branch->right_branch;

        left_branch->right_branch = node;
        node->left_branch = left_right_branch;

        node->height = max(get_height(node->right_branch), get_height(node->left_branch)) + 1;
        left_branch->height = max(get_height(left_branch->right_branch), get_height(left_branch->left_branch)) + 1;
        
        return left_branch;
    }

    // helper for balancing a tree
    //Node* balance_this(Node* node) {
    //    int balance = get_balance(node);
        // recursively balancing up from new leaf
        // theoretiacl case where both secondary nodes 
        // != nullptr cannot exist due to balancing happening 
        // upwards

        // case left ___
    //    if (balance > 1) {
            // case left left sturcture bellow node
    //        if (node->left_branch->left_branch != nullptr) {
    //            node = rotate_right(node);
    //            return node;
    //        }

            // case left right structure bellow node
    //        if (node->left_branch->right_branch != nullptr) {
    //            node->left_branch = rotate_left(node->left_branch);
    //            node = rotate_right(node);
    //            return node;
    //        }
    //    }

        // case right ___
    //    if (balance < -1) {
            // case right right structure bellow node
    //        if (node->right_branch->right_branch != nullptr) {
    //            node = rotate_left(node);
    //            return node;
    //        }

            // case right left sturture bellow node
    //        if (node->right_branch->left_branch != nullptr) {
    //            node->right_branch = rotate_right(node->right_branch);
    //            node = rotate_left(node);
    //            return node;
    //        }
    //    }

        // if all else fails 
    //    return node;
    //}

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

        // num has been inserted increasing height of all traveled nodes
        // if appropriate
        current_node->height = max(get_height(current_node->left_branch), get_height(current_node->right_branch)) + 1;

        // checking if insertion has unbalanced the tree
        //int balance = get_balance(current_node);
        //if (balance > 1 || balance < -1) {
        //    current_node = balance_this(current_node);
        //    return current_node;
        //}

        int balance = get_balance(current_node);
        // recursively balancing up from new leaf
        // theoretiacl case where both secondary nodes 
        // != nullptr cannot exist due to balancing happening 
        // upwards

        // case left ___
        if (balance > 1) {
            // case left left sturcture bellow node
            if (current_node->left_branch->left_branch != nullptr) {
                current_node = rotate_right(current_node);
                return current_node;
            }

            // case left right structure bellow node
            if (current_node->left_branch->right_branch != nullptr) {
                current_node->left_branch = rotate_left(current_node->left_branch);
                current_node = rotate_right(current_node);
                return current_node;
            }
        }

        // case right ___
        if (balance < -1) {
            // case right right structure bellow node
            if (current_node->right_branch->right_branch != nullptr) {
                current_node = rotate_left(current_node);
                return current_node;
            }

            // case right left sturture bellow node
            if (current_node->right_branch->left_branch != nullptr) {
                current_node->right_branch = rotate_right(current_node->right_branch);
                current_node = rotate_left(current_node);
                return current_node;
            }
        }

        // case if insetion doesnt excede a balance of
        // [-1, 1]
        return current_node;
    };

    Node* private_deletion(Node* current_node, int num) {
        // base case of DNE
        if (current_node == nullptr) {
            return current_node;
        }

        // downwards navigation of binary tree
        if (num < current_node->element) {
            current_node->left_branch = private_deletion(current_node->left_branch, num);
        }
        else if (num > current_node->element) {
            current_node->right_branch = private_deletion(current_node->right_branch, num);
        }
        
        // num found
        // actual deletion
        else if (current_node->element == num) {
            // if node containing num has less that 2 children
            if (current_node->left_branch == nullptr || current_node->right_branch == nullptr) {
                // if node containing num has 0 children
                if (current_node->left_branch == nullptr && current_node->right_branch == nullptr) {
                    delete current_node;
                    return nullptr;
                }

                // if node containing num has 1 child
                // left branch
                if (current_node->left_branch != nullptr) {
                    Node* to_be_returned = current_node->left_branch;
                    delete current_node;
                    return to_be_returned;
                }
                // right branch
                if (current_node->right_branch != nullptr) {
                    Node* to_be_returned = current_node->right_branch;
                    delete current_node;
                    return to_be_returned;
                }
            }

            // if node has 2 children
            if (current_node->left_branch != nullptr && current_node->right_branch != nullptr) {
                // going down to rightmost subbranch of the left subbranch
                Node* rightmost_left = current_node->left_branch;
                while (rightmost_left->right_branch != nullptr) {
                    rightmost_left = rightmost_left->right_branch;
                }

                // replacing the "to be deleted" with the rightmost of the left
                // branch, then deleting the rightmost_left, this will not recursively
                // call this section (if node has 2 children) 
                int holder = rightmost_left->element;
                current_node->element = holder;
                current_node->left_branch = private_deletion(current_node->left_branch, rightmost_left->element);

                // open ended so that it will run through the balance for the main "to be deleted"
            }
        }

        // to correct height values post deletion
        current_node->height = max(get_height(current_node->left_branch), get_height(current_node->right_branch)) + 1;

        // if rebalancing is required once num is deleted
        int balance = get_balance(current_node);
        
        // requires a different balancing system because deletion
        // can happen anywhere in the tree, compared to insertion
        // that can only happen at the leaves

        // left bias
        if (balance > 1) {
            // left left
            if (get_balance(current_node->left_branch) >= 0) {
                current_node = rotate_right(current_node);
                return current_node;
            }
            // left right
            else if (get_balance(current_node->left_branch) < 0) {
                current_node->left_branch = rotate_left(current_node->left_branch);
                current_node = rotate_right(current_node);
                return current_node;
            }
        }

        // right bias
        if (balance < -1) {
            // right right
            if (get_balance(current_node->right_branch) >= 0) {
                current_node = rotate_left(current_node);
                return current_node;
            }
            // right left
            else if (get_balance(current_node->right_branch) < 0) {
                current_node->right_branch = rotate_right(current_node->right_branch);
                current_node = rotate_left(current_node);
                return current_node;
            }
        }

        // no rebalancing needed, backtracking to start
        return current_node;
    };

    // varying traversal methods
    void private_preorder(Node* root) {
        if (root != nullptr) {
            cout << root->element << " ";
            private_preorder(root->left_branch);
            private_preorder(root->right_branch);
        }
    };

    void private_postorder(Node* root) {
        if (root != nullptr) {
            private_postorder(root->left_branch);
            private_postorder(root->right_branch);
            cout << root->element << " ";
        }
    };

    void private_inorder(Node* root) {
        if (root != nullptr) {
            private_inorder(root->left_branch);
            cout << root->element << " ";
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
            cout << "EMPTY";
        }
        else {
            private_preorder(root);
        }
    }

    void postorder() {
        if (root == nullptr) {
            cout << "EMPTY";
        }
        else {
            private_postorder(root);
        }
    }

    void indorder() {
        if (root == nullptr) {
            cout << "EMPTY";
        }
        else {
            private_inorder(root);
        }
    }
};

int main() {   
    // planting tree
    AVL tree;

    // input
    string raw_input;
    getline(cin, raw_input);
    stringstream ss(raw_input);
    string input;
    vector<string> all_inputs;
    while (ss >> input) {
        all_inputs.push_back(input);
    }

    // sorting the Addition from the Deletion
    string num_string;
    int num;
    for (size_t i = 0; i < (all_inputs.size() - 1); i++) {
        if (all_inputs[i][0] == 'A') {
            num_string = all_inputs[i].substr(1);
            num = stoi(num_string);
            tree.insertion(num);
        }
        else if (all_inputs[i][0] == 'D') {
            num_string = all_inputs[i].substr(1);
            num = stoi(num_string);
            tree.deletion(num);
        }
    }

    // output
    // preorder
    if (all_inputs.back() == "PRE") {
        tree.preorder();
        cout << endl;
    }

    // postorder
    if (all_inputs.back() == "POST") {
        tree.postorder();
        cout << endl;
    }

    // inorder
    if (all_inputs.back() == "IN") {
        tree.indorder();
        cout << endl;
    }


    // test inp:
    // A88 D77 D95 A78 A71 A2 D9 A2 A60 D80 A85 A65 D11 A30 D8 A68 D87 A28 A88 A96 D29 D26 D88 D47 D68 A65 A86 A100 A61 D7 D76 D21 D24 A40 D94 A84 A16 D28 A45 A60 D34 D14 A68 A64 A74 A62 D99 D2 D34 D32 D60 D52 D19 A95 A28 A91 D24 A34 D22 D77 D7 D78 A3 A100 D95 D53 D82 D64 A55 A46 A17 A70 D4 A25 A75 D71 A30 D50 D44 A11 D39 A47 D77 A71 D1 A98 D51 A63 D15 A15 D75 A4 D14 D77 A9 D84 D70 A5 D67 A22 POST
    // cout << "3 5 4 15 11 9 22 17 28 25 16 34 40 46 55 47 63 62 61 45 30 71 68 85 74 91 98 100 96 86 65" << endl;

    return 0;
}

