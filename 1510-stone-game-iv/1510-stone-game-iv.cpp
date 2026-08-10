class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<char> dp(n + 1, false);

        for (int stones = 1; stones <= n; ++stones) {
            for (int k = 1; k * k <= stones; ++k) {
                if (!dp[stones - k * k]) {
                    dp[stones] = true;
                    break;   // found a winning move
                }
            }
        }

        return dp[n];
    }
};