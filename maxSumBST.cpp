#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
    int maxSum = INT_MIN;
public:
    int maxSumBST(TreeNode* root) {
        function<vector<int>(TreeNode*)> findmaxSum = [&](TreeNode* node) -> vector<int> {
            if (node == nullptr) return {INT_MAX, INT_MIN, 0};

            vector<int> left = findmaxSum(node->left);
            vector<int> right = findmaxSum(node->right);

            if (left[1] >= node->val || right[0] <= node->val) return {INT_MIN, INT_MAX, 0};

            int sum = left[2] + right[2] + node->val;
            maxSum = max(maxSum, sum);

            return {min(node->val, left[0]), max(right[1], node->val), sum};
        };

        vector<int> ans = findmaxSum(root);
        if (maxSum < 0) return 0;
        return maxSum;
    }
};
