#pragma once

namespace TreeNode {
struct TreeNode {
public:
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
    TreeNode(int _val, TreeNode* _left, TreeNode* _right) : val(_val), left(_left), right(_right) {}

public:
    int val;
    TreeNode* left;
    TreeNode* right;
};
}  // namespace TreeNode
