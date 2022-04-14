#include <iostream>
#include <vector>
#include "tree_node.hpp"
#include "traversal_binary_tree.hpp"

using namespace std;
using namespace TreeNode;

TreeNode* binary_tree_construction() {
    TreeNode* root = new TreeNode(23);
    TreeNode* a = new TreeNode(20);
    TreeNode* b = new TreeNode(36);
    TreeNode* c = new TreeNode(9);
    TreeNode* d = new TreeNode(21);
    TreeNode* e = new TreeNode(30);
    TreeNode* f = new TreeNode(50);
    TreeNode* g = new TreeNode(6);
    TreeNode* h = new TreeNode(8);
    TreeNode* i = new TreeNode(15);
    TreeNode* j = new TreeNode(26);
    TreeNode* k = new TreeNode(32);
    TreeNode* l = new TreeNode(60);
    TreeNode* m = new TreeNode(2);
    TreeNode* n = new TreeNode(7);
    TreeNode* o = new TreeNode(10);
    TreeNode* p = new TreeNode(31);

    root->left = a; root->right = b;
    a->left = c; a->right = d; b->left = e; b->right = f;
    c->left = g; c->right = h; d->left = i;
    e->left = j; e->right = k; f->right = l;
    g->left = m; g->right = n; h->right = o;
    i->left = nullptr; i->right = nullptr; j->left = nullptr; j->right = nullptr;
    k->left = p; l->left = nullptr; l->right = nullptr;

    return root;
}

TreeNode* binary_tree_construction() {
    
}

int main() {
    TreeNode* root = binary_tree_construction();
}
