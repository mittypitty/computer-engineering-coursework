#include <iostream>

class BranchNode {
public:
    int value;
    BranchNode* left_child;
    BranchNode* right_child;

    BranchNode(int item) : value(item), left_child(nullptr), right_child(nullptr) {}

    ~BranchNode() {
        delete left_child;
        delete right_child;
    }
};

class TreeStructure {
private:
    BranchNode* tree_root;

    BranchNode* add_node_recursive(BranchNode* current_node, int value_to_add) {
        if (current_node == nullptr) {
            return new BranchNode(value_to_add);
        }

        if (value_to_add < current_node->value) {
            current_node->left_child = add_node_recursive(current_node->left_child, value_to_add);
        }
        else if (value_to_add > current_node->value) {
            current_node->right_child = add_node_recursive(current_node->right_child, value_to_add);
        }

        return current_node;
    }

public:
    TreeStructure() : tree_root(nullptr) {}

    ~TreeStructure() {
        delete tree_root;
    }

    void add_node(int value_to_add) {
        tree_root = add_node_recursive(tree_root, value_to_add);
    }

    BranchNode* find_lowest_common_ancestor(int val_a, int val_b) {
        BranchNode* current_search_node = tree_root;
        while (current_search_node != nullptr) {
            if (current_search_node->value > val_a && current_search_node->value > val_b) {
                current_search_node = current_search_node->left_child;
            }
            else if (current_search_node->value < val_a && current_search_node->value < val_b) {
                current_search_node = current_search_node->right_child;
            }
            else {
                break;
            }
        }
        return current_search_node;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    TreeStructure main_tree;

    int number_of_elements;
    std::cin >> number_of_elements;

    for (int i = 0; i < number_of_elements; ++i) {
        int input_value;
        std::cin >> input_value;
        main_tree.add_node(input_value);
    }

    int value_one, value_two;
    std::cin >> value_one >> value_two;

    BranchNode* ancestor_node = main_tree.find_lowest_common_ancestor(value_one, value_two);

    if (ancestor_node != nullptr) {
        std::cout << ancestor_node->value << std::endl;
    } else {
        std::cout << "Lowest Common Ancestor not found. Either the tree is empty or one/both values are not present." << std::endl;
    }

    return 0;
}
