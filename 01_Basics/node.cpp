#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────
// TreeNode Structure — the base of all tree problems
// Time : O(1) for node creation
// Space : O(1) per node
// ─────────────────────────────────────────────────────────────
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    // Default constructor
    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    // Constructor with value
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    // Constructor with value + children
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

// ─────────────────────────────────────────────────────────────
// Build a simple tree manually
//
//        1
//       / \
//      2   3
//     / \
//    4   5
//
// ─────────────────────────────────────────────────────────────
TreeNode* buildTree() {
    TreeNode* root        = new TreeNode(1);
    root->left            = new TreeNode(2);
    root->right           = new TreeNode(3);
    root->left->left      = new TreeNode(4);
    root->left->right     = new TreeNode(5);
    return root;
}

// ─────────────────────────────────────────────────────────────
// Count total number of nodes
// ─────────────────────────────────────────────────────────────
int countNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ─────────────────────────────────────────────────────────────
// Find height of tree
// ─────────────────────────────────────────────────────────────
int height(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// ─────────────────────────────────────────────────────────────
// Check if tree is empty
// ─────────────────────────────────────────────────────────────
bool isEmpty(TreeNode* root) {
    return root == nullptr;
}

// ─────────────────────────────────────────────────────────────
// Check if node is a leaf (no children)
// ─────────────────────────────────────────────────────────────
bool isLeaf(TreeNode* root) {
    return root && !root->left && !root->right;
}

// ─────────────────────────────────────────────────────────────
// Print tree inorder (Left -> Root -> Right)
// ─────────────────────────────────────────────────────────────
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

// ─────────────────────────────────────────────────────────────
// Delete entire tree (free memory)
// ─────────────────────────────────────────────────────────────
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    TreeNode* root = buildTree();

    cout << "Inorder print  : ";
    printInorder(root);
    cout << "\n";

    cout << "Total nodes    : " << countNodes(root) << "\n";  // 5
    cout << "Height         : " << height(root) << "\n";      // 3
    cout << "Is empty       : " << isEmpty(root) << "\n";     // 0 (false)
    cout << "Is root leaf   : " << isLeaf(root) << "\n";      // 0 (false)
    cout << "Is node 4 leaf : " << isLeaf(root->left->left) << "\n"; // 1 (true)

    deleteTree(root);
    cout << "Tree deleted!\n";

    return 0;
}