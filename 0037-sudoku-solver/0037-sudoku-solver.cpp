class Solution {
public:
    bool solve(vector<vector<char>>& board, int pos) {
        if (pos == 81) return true;

        int r = pos / 9, c = pos % 9;
        if (board[r][c] != '.') return solve(board, pos + 1);

        for (char ch = '1'; ch <= '9'; ch++) {
            bool valid = true;

            for (int i = 0; i < 9; i++) {
                if (board[r][i] == ch || board[i][c] == ch)
                    valid = false;
            }

            for (int i = r / 3 * 3; i < r / 3 * 3 + 3; i++)
                for (int j = c / 3 * 3; j < c / 3 * 3 + 3; j++)
                    if (board[i][j] == ch) valid = false;

            if (valid) {
                board[r][c] = ch;
                if (solve(board, pos + 1)) return true;
                board[r][c] = '.';
            }
        }
        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        solve(board, 0);
    }
};