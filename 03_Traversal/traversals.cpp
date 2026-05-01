#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ─────────────────────────────────────────────────────────────
// 1. INORDER  →  Left → Root → Right
//    Use case : gives SORTED output for BST
//    Time : O(n)  |  Space : O(h)
// ─────────────────────────────────────────────────────────────
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";   // process root BETWEEN children
    inorder(root->right);
}

// ─────────────────────────────────────────────────────────────
// 2. PREORDER  →  Root → Left → Right
//    Use case : copy or serialize a tree
//    Time : O(n)  |  Space : O(h)
// ─────────────────────────────────────────────────────────────
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";   // process root FIRST
    preorder(root->left);
    preorder(root->right);
}

// ─────────────────────────────────────────────────────────────
// 3. POSTORDER  →  Left → Right → Root
//    Use case : delete a tree, calculate folder size
//    Time : O(n)  |  Space : O(h)
// ─────────────────────────────────────────────────────────────
void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";   // process root LAST
}

// ─────────────────────────────────────────────────────────────
// 4. LEVEL ORDER (BFS)  →  level by level left to right
//    Use case : find min depth, right side view
//    Uses QUEUE not recursion
//    Time : O(n)  |  Space : O(n)
// ─────────────────────────────────────────────────────────────
void levelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();       // nodes at this level
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            cout << node->val << " ";
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << "\n";                   // new line after each level
    }
}

// ─────────────────────────────────────────────────────────────
// 5. ITERATIVE INORDER  →  using stack (asked in interviews!)
//    Time : O(n)  |  Space : O(h)
// ─────────────────────────────────────────────────────────────
void iterativeInorder(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* curr = root;

    while (curr || !st.empty()) {
        // go as left as possible
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top();
        st.pop();
        cout << curr->val << " ";
        curr = curr->right;
    }
}

// ─────────────────────────────────────────────────────────────
// 6. ITERATIVE PREORDER  →  using stack
//    Time : O(n)  |  Space : O(h)
// ─────────────────────────────────────────────────────────────
void iterativePreorder(TreeNode* root) {
    if (!root) return;
    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();
        cout << node->val << " ";
        // push right first so left is processed first
        if (node->right) st.push(node->right);
        if (node->left)  st.push(node->left);
    }
}

// ─────────────────────────────────────────────────────────────
// 7. REVERSE LEVEL ORDER  →  bottom level first
//    Time : O(n)  |  Space : O(n)
// ─────────────────────────────────────────────────────────────
void reverseLevelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    vector<vector<int>> levels;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            currentLevel.push_back(node->val);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        levels.push_back(currentLevel);
    }

    // print in reverse
    for (int i = levels.size() - 1; i >= 0; i--) {
        for (int val : levels[i])
            cout << val << " ";
        cout << "\n";
    }
}

int main() {
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5