#include <iostream>
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

        Node* left_rotate(Node* node) {
            Node* node_right = node -> right;
            Node* node_right_left = node_right -> left;

            node_right -> left = node;
            node -> right = node_right_left;

            node -> height = std::max(get_height(node -> left), get_height(node -> right)) + 1;
            node_right -> height = std::max(get_height(node_right -> left), get_height(node_right -> right)) + 1;

            return node_right;
        }

        Node* right_rotate(Node* node) {
            Node* node_left = node -> left;
            Node* node_left_right = node_left -> right;

            node_left -> right = node;
            node -> left = node_left_right;

            node -> height = std::max(get_height(node -> left), get_height(node -> right)) + 1;
            node_left -> height = std::max(get_height(node_left -> left), get_height(node_left -> right)) + 1;

            return node_left;
        }

        Node* max_value_node(Node* node) {
            Node* curr = node;

            while (curr -> right) {
                curr = curr -> right;
            }

            return curr;
        }

        Node* insert_node(Node* node, int val) {
            if (!node) {
                return new Node(val);
            }

            if (val < node -> val) {
                node -> left = insert_node(node -> left, val);
            }

            else if (val > node -> val) {
                node -> right = insert_node(node -> right, val);
            }

            // duplicate
            else {
                return node;
            }

            node -> height = std::max(get_height(node->left), get_height(node->right)) + 1;
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
                return right_rotate(node);
            }

            // right-left
            if (balance < -1 && val < node -> right -> val) {
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
                if (!(node -> left) || !(node -> right)) {
                    Node* temp = (node -> left) ? (node -> left) : (node -> right);

                    if (!temp) {
                        temp = node;
                        node = nullptr;
                    }

                    else {
                        *node = *temp; // copy content of temp to node
                    }

                    delete temp;
                }

                else {
                    Node* temp = max_value_node(node -> right);
                    node -> val = temp -> val;
                    node -> right = delete_node(node -> right, temp -> val);
                }
            }

            if (!node) {
                return node;
            }

            node->height = 1 + std::max(get_height(node -> left), get_height(node -> right));
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
            if (node) {
                std::cout << node -> val << " ";
                pre_order(node -> left);
                pre_order(node -> right);
            }
        }

        void post_order(Node* node) {
            if (node) {
                post_order(node -> left);
                post_order(node -> right);
                std::cout << node -> val << " "; 
            }
        }

        void in_order(Node* node) {
            if (node) {
                in_order(node -> left);
                std::cout << node -> val << " ";
                in_order(node -> right);
            }
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