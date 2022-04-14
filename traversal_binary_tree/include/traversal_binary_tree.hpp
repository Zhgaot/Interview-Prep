#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include "tree_node.hpp"

using namespace TreeNode;

class TraversalBinaryTree {
public:
    void preorder_traversal(TreeNode* root);
    void inorder_traversal(TreeNode* root);
    void postorder_traversal(TreeNode* root);
    std::vector<std::vector<int>> levelorder_traversal(TreeNode* root);
    std::vector<std::vector<int>> zigzag_levelorder_traversal(TreeNode* root);
};

TraversalBinaryTree::levelorder_traversal(TreeNode* root) {
    std::vector<std::vector<int>> res;
    if (root == nullptr)
        return res;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        std::vector<int> layout;
        layout.reserve(size);
        for (int i = 0; i < size; ++i) {
            TreeNode* cur = q.front();
            q.pop();
            layout.push_back(cur->val);
            if (cur->left != nullptr)
                q.push(cur->left);
            if (cur->right != nullptr)
                q.push(cur->right);
        }
        res.push_back(layout);
    }
    return res;
}

std::vector<std::vector<int>>
TraversalBinaryTree::zigzag_levelorder_traversal(TreeNode* root) {
    std::vector<std::vector<int>> res;
    if (root == nullptr)
        return res;
    std::queue<TreeNode*> q;
    q.push(root);
    int flag = 0;
    while (!q.empty()) {
        int size = q.size();
        std::deque<int> layout;
        for (int i = 0; i < size; ++i) {
            TreeNode* cur = q.front();
            q.pop();
            if (flag % 2 == 0)
                layout.push_back(cur->val);
            else
                layout.push_front(cur->val);
            if (cur->left != nullptr)
                q.push(cur->left);
            if (cur->right != nullptr)
                q.push(cur->right);
        }
        ++flag;
        res.push_back(std::vector<int>(layout.begin(), layout.end()));
    }
    return res;
}
