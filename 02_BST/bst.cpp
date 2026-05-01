#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────
// Binary Search Tree — Insert, Search, Delete
// Property : left < root < right (always!)
// Time : O(h) average | O(n) worst case (skewed tree)
// Space : O(h) recursion stack
// ─────────────────────────────────────────────────────────────
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ─────────────────────────────────────────────────────────────
// INSERT
// If val < root  → go left
// If val > root  → go right
// If null        → place node here
// ─────────────────────────────────────────────────────────────
TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val)
        root->left  = insert(root->left,  val);
    else if (val > root->val)
        root->right = insert(root->right, val);
    return root;
}

// ─────────────────────────────────────────────────────────────
// SEARCH
// Returns the node if found, nullptr if not found
// ─────────────────────────────────────────────────────────────
TreeNode* search(TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    if (val < root->val)
        return search(root->left,  val);
    else
        return search(root->right, val);
}

// ─────────────────────────────────────────────────────────────
// FIND MINIMUM node in tree (goes all the way left)
// ─────────────────────────────────────────────────────────────
TreeNode* findMin(TreeNode* root) {
    while (root->left) root = root->left;
    return root;
}

// ─────────────────────────────────────────────────────────────
// FIND MAXIMUM node in tree (goes all the way right)
// ─────────────────────────────────────────────────────────────
TreeNode* findMax(TreeNode* root) {
    while (root->right) root = root->right;
    return root;
}

// ─────────────────────────────────────────────────────────────
// DELETE — 3 cases:
// Case 1 : Node has no children     → just remove it
// Case 2 : Node has one child       → replace with that child
// Case 3 : Node has two children    → replace with inorder
//                                     successor (min of right)
// ─────────────────────────────────────────────────────────────
TreeNode* deleteNode(TreeNode* root, int val) {
    if (!root) return nullptr;

    if (val < root->val) {
        root->left  = deleteNode(root->left,  val);
    } else if (val > root->val) {
        root->right = deleteNode(root->right, val);
    } else {
        // Case 1 and 2 : 0 or 1 child
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Case 3 : 2 children
        TreeNode* successor = findMin(root->right);
        root->val   = successor->val;
        root->right = deleteNode(root->right, successor->val);
    }
    return root;
}

// ─────────────────────────────────────────────────────────────
// COUNT total nodes in BST
// ─────────────────────────────────────────────────────────────
int countNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ─────────────────────────────────────────────────────────────
// HEIGHT of BST
// ─────────────────────────────────────────────────────────────
int height(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

// ─────────────────────────────────────────────────────────────
// INORDER print — gives sorted output for BST
// ─────────────────────────────────────────────────────────────
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

int main() {
    TreeNode* root = nullptr;

    // Build BST
    for (int val : {5, 3, 7, 1, 4, 6, 8})
        root = insert(root, val);

    //        5
    //       / \
    //      3   7
    //     / \ / \
    //    1  4 6  8

    cout << "Inorder (sorted) : ";
    inorder(root);
    cout << "\n";

    cout << "Total nodes      : " << countNodes(root) << "\n";  // 7
    cout << "Height           : " << height(root) << "\n";      // 3
    cout << "Min value        : " << findMin(root)->val << "\n"; // 1
    cout << "Max value        : " << findMax(root)->val << "\n"; // 8

    cout << "Search 4         : " << (search(root, 4) ? "Found" : "Not found") << "\n";
    cout << "Search 9         : " << (search(root, 9) ? "Found" : "Not found") << "\n";

    // Delete node with 2 children
    root = deleteNode(root, 5);
    cout << "After delete 5   : ";
    inorder(root);
    cout << "\n";

    // Delete leaf node
    root = deleteNode(root, 1);
    cout << "After delete 1   : ";
    inorder(root);
    cout << "\n";

    // Delete node with 1 child
    root = deleteNode(root, 7);
    cout << "After delete 7   : ";
    inorder(root);
    cout << "\n";

    return 0;
}