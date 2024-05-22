// cantidad de maneras en que se puede reconstruir un árbol binario de búsqueda (BST) dado un conjunto inicial de elementos
#include <iostream>
using namespace std;

class Solution {
public:
int numOfWays(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> binom(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= n; ++i) {
        binom[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % 1000000007;
        }
    }

    function<int(vector<int>&)> calculateWays = [&](vector<int>& subset) {
        int m = subset.size();
        if (m <= 2) return 1;

        vector<int> leftSubtree, rightSubtree;
        for (int i = 1; i < m; ++i) {
            if (subset[i] < subset[0]) leftSubtree.push_back(subset[i]);
            else rightSubtree.push_back(subset[i]);
        }

        long long ways = binom[m - 1][leftSubtree.size()];
        ways = (ways * calculateWays(leftSubtree)) % 1000000007;
        ways = (ways * calculateWays(rightSubtree)) % 1000000007;
        return (int)ways;
    };

    return calculateWays(nums) - 1;
}

};

int main () {

    vector<int> nums = {2,1,3};
    int result = Solution().numOfWays(nums);
    cout << "Número de maneras de reconstruir el BST: " << result << endl; // Output: 5

    return 0;
}
