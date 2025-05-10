#include <iostream>
#include <unordered_set>
#include <sstream>

struct Node {
    int val;
    int height;
    Node* left;
    Node* right;

    Node(int val) {
        this -> val = val;
        this -> height = 1;
        this -> left = nullptr;
        this -> right = nullptr;
    }
};

class AVLTree {
    public:
        Node* root;
        std::unordered_set<int> st;

        AVLTree() {
            this -> root = nullptr;
        }

        int get_height(Node* node) {
            if (!node) {
                return 0;
            }

            return node -> height;
        }

        int get_balance(Node* node) {
            if (!node) {
                return 0;
            }

            else {
                return get_height(node -> left) - get_height(node -> right);
            }
        }

        void update_node(Node* node) {
            if (!node) {
                return;
            }

            node -> height = std::max(get_height(node -> left), get_height(node -> right)) + 1;
        }

        Node* left_rotate(Node* node) {
            Node* node_right = node -> right;
            Node* node_right_left = node_right -> left;

            node_right -> left = node;
            node -> right = node_right_left;

            update_node(node);
            update_node(node_right);

            return node_right;
        }

        Node* right_rotate(Node* node) {
            Node* node_left = node -> left;
            Node* node_left_right = node_left -> right;

            node_left -> right = node;
            node -> left = node_left_right;

            update_node(node);
            update_node(node_left);

            return node_left;
        }

        Node* max_value_node(Node* node) {
            Node* curr = node;

            while (curr && curr -> right) {
                curr = curr -> right;
            }

            return curr;
        }

        Node* insert_node(Node* node, int val) {
            if (st.find(val) != st.end()) {
                return node;
            }

            if (!node) {
                st.insert(val);
                return new Node(val);
            }

            if (val < node -> val) {
                node -> left = insert_node(node -> left, val);
            }

            else if (val > node -> val) {
                node -> right = insert_node(node -> right, val);
            }

            update_node(node);
            int balance = get_balance(node);

            // left-left
            if (balance > 1 && val < node -> left -> val) {
                return right_rotate(node);
            }

            // right-right
            if (balance < -1 && val > node -> right -> val) {
                return left_rotate(node);
            }

            // left-right
            if (balance > 1 && val > node -> left -> val) {
                node -> left = left_rotate(node -> left);
                return right_rotate(node);
            }

            // right-left
            if (balance < -1 && val < node -> right -> val) {
                node -> right = right_rotate(node -> right);
                return left_rotate(node);
            }

            return node;
        }

        Node* delete_node(Node* node, int val) {
            if (!node) {
                return node;
            }

            if (val < node -> val) {
                node -> left = delete_node(node -> left, val);
            }

            else if (val > node -> val) {
                node -> right = delete_node(node -> right, val);
            }

            else {
                st.erase(val);

                if (!(node -> left) || !(node -> right)) {
                    Node* temp = (node -> left) ? (node -> left) : (node -> right);
                    delete node;
                    return temp;
                }

                Node* temp = max_value_node(node -> left);
                node -> val = temp -> val;
                node -> left = delete_node(node -> left, temp -> val);
            }

            update_node(node);
            int balance = get_balance(node);

            // left-left
            if (balance > 1 && get_balance(node -> left) >= 0) {
                return right_rotate(node);
            }

            // right-right
            if (balance < -1 && get_balance(node -> right) <= 0) {
                return left_rotate(node);
            }

            // left-right
            if (balance > 1 && get_balance(node -> left) < 0) {
                node -> left = left_rotate(node -> left);
                return right_rotate(node);
            }

            // right-left
            if (balance < -1 && get_balance(node -> right) > 0) {
                node -> right = right_rotate(node -> right);
                return left_rotate(node);
            }

            return node;
        }

        void pre_order(Node* node) {
            if (!node) {
                return;
            }

            std::cout << node -> val << " ";
            pre_order(node -> left);
            pre_order(node -> right);
        }

        void post_order(Node* node) {
            if (!node) {
                return;
            }

            post_order(node -> left);
            post_order(node -> right);
            std::cout << node -> val << " "; 
        }

        void in_order(Node* node) {
            if (!node) {
                return;
            }

            in_order(node -> left);
            std::cout << node -> val << " ";
            in_order(node -> right);
        }
};

int main() {
    AVLTree* tree = new AVLTree();
    std::string input;
    getline(std::cin, input);

    std::stringstream ss(input);
    std::string command;

    while (ss >> command) {
        if (command[0] == 'A') {
            int val = std::stoi(command.substr(1));
            tree -> root = tree -> insert_node(tree -> root, val);
        }

        else if (command[0] == 'D') {
            int val = std::stoi(command.substr(1));
            tree -> root = tree -> delete_node(tree -> root, val);
        }

        else if (command == "PRE") {
            if (!tree -> root) {
                std::cout << "EMPTY" << std::endl;
            }

            else {
                tree -> pre_order(tree -> root);
                std::cout << std::endl;
            }
        }

        else if (command == "POST") {
            if (!tree->root) {
                std::cout << "EMPTY" << std::endl;
            } 
            
            else {
                tree -> post_order(tree -> root);
                std::cout << std::endl;
            }
        }

        else if (command == "IN") {
            if (!tree -> root) {
                std::cout << "EMPTY" << std::endl;
            } 
            
            else {
                tree -> in_order(tree -> root);
                std::cout << std::endl;
            }
        }
    }

    delete tree;
}