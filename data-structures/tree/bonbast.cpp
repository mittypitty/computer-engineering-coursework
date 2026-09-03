#include <iostream>
const int CUSTOM_INT_MAX = 2147483647;

class TreeNode {
public:
    int data_val;
    TreeNode* left_ptr;
    TreeNode* right_ptr;

    TreeNode(int item) : data_val(item), left_ptr(nullptr), right_ptr(nullptr) {}

    ~TreeNode() {
        delete left_ptr;
        delete right_ptr;
    }
};

class SearchTree {
private:
    TreeNode* tree_base;

    TreeNode* add_element_recursive(TreeNode* current_node, int val_to_add) {
        if (current_node == nullptr) {
            return new TreeNode(val_to_add);
        }

        if (current_node->data_val > val_to_add) {
            current_node->left_ptr = add_element_recursive(current_node->left_ptr, val_to_add);
        } else if (current_node->data_val < val_to_add) {
            current_node->right_ptr = add_element_recursive(current_node->right_ptr, val_to_add);
        }
        return current_node;
    }

    bool check_blocked_path(TreeNode* current_node, int current_min_limit, int current_max_limit) {
        if (current_node == nullptr)
            return false;
        if (current_min_limit == current_max_limit)
            return true;
        return check_blocked_path(current_node->left_ptr, current_min_limit, current_node->data_val - 1) ||
               check_blocked_path(current_node->right_ptr, current_node->data_val + 1, current_max_limit);
    }

public:
    SearchTree() : tree_base(nullptr) {}

    ~SearchTree() {
        delete tree_base;
    }

    void add_element(int val) {
        tree_base = add_element_recursive(tree_base, val);
    }

    bool tree_has_blocked_path() {
        return check_blocked_path(tree_base, 1, CUSTOM_INT_MAX);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    SearchTree main_tree;
    int count_of_elements;
    std::cin >> count_of_elements;

    for (int i = 0; i < count_of_elements; ++i) {
        int current_element_val;
        std::cin >> current_element_val;
        main_tree.add_element(current_element_val);
    }

    bool is_path_blocked = main_tree.tree_has_blocked_path();
    if (is_path_blocked) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
