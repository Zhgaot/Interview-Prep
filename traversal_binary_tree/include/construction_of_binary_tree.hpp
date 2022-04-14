#pargma once

#include <vector>
#include "tree_node.hpp"

using namespace TreeNode;

TreeNode* construct_binary_tree(const vector<int>& value_arr) {
    int len = value_arr.size();
    if (len == 0)
        return nullptr;
    std::vector<TreeNode*> tree_arr(len, nullptr);
    tree_arr.reserve(len);
    for (int i = 0; i < len; ++i) {
        TreeNode* temp = new TreeNode(value_arr[i]);
        tree_arr.push_back(temp);
    }
    TreeNode* root = tree_arr[0];
    for (int i = 0; i <= len / 2 - 1; ++i) {  // i * 2 + 2 < len
        if (tree_arr[i] != nullptr) {
            tree_arr[i]->left = tree_arr[i * 2 + 1];
            tree_arr[i]->right = tree_arr[i * 2 + 2];
        }
    }
    return root;
}
