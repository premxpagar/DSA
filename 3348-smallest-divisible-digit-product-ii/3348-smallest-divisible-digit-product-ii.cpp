class Solution {
public:
    using State = array<int, 4>;

    int A, B, C, D;
    vector<int> memo;

    // factor[digit] = powers of 2,3,5,7 in that digit
    int factor[10][4] = {
        {0, 0, 0, 0}, // 0
        {0, 0, 0, 0}, // 1
        {1, 0, 0, 0}, // 2
        {0, 1, 0, 0}, // 3
        {2, 0, 0, 0}, // 4
        {0, 0, 1, 0}, // 5
        {1, 1, 0, 0}, // 6
        {0, 0, 0, 1}, // 7
        {3, 0, 0, 0}, // 8
        {0, 2, 0, 0}  // 9
    };

    int id(int a, int b, int c, int d) {
        return (((a * (B + 1) + b) * (C + 1) + c)
                * (D + 1) + d);
    }

    State removeFactors(State s, int digit) {
        s[0] = max(0, s[0] - factor[digit][0]);
        s[1] = max(0, s[1] - factor[digit][1]);
        s[2] = max(0, s[2] - factor[digit][2]);
        s[3] = max(0, s[3] - factor[digit][3]);

        return s;
    }

    /*
        dp(state) =
        minimum number of digits required to satisfy
        all remaining prime factors in state.
    */
    int minDigits(State s) {

        int idx = id(s[0], s[1], s[2], s[3]);

        if (memo[idx] != -1)
            return memo[idx];

        // Nothing left to satisfy.
        if (s[0] == 0 &&
            s[1] == 0 &&
            s[2] == 0 &&
            s[3] == 0) {

            return memo[idx] = 0;
        }

        const int INF = 1e9;

        int ans = INF;

        // Digits 2..9 are useful.
        for (int digit = 2; digit <= 9; digit++) {

            State next = removeFactors(s, digit);

            // Digit must actually reduce the state.
            if (next == s)
                continue;

            int sub = minDigits(next);

            if (sub != INF) {
                ans = min(ans, 1 + sub);
            }
        }

        return memo[idx] = ans;
    }


    /*
        Build the lexicographically smallest suffix
        of EXACTLY len digits.

        Once all required factors are satisfied,
        remaining positions can simply be '1'.
    */
    string buildSuffix(int len, State need) {

        string ans;

        for (int pos = 0; pos < len; pos++) {

            int remainingPositions = len - pos - 1;

            for (int digit = 1; digit <= 9; digit++) {

                State next = removeFactors(need, digit);

                /*
                    We need to be able to finish the remaining
                    factor requirements using at most the
                    remaining number of positions.

                    Extra positions can always be filled with 1.
                */
                if (minDigits(next) <= remainingPositions) {

                    ans += char('0' + digit);

                    need = next;

                    break;
                }
            }
        }

        return ans;
    }


    string smallestNumber(string num, long long t) {

        // ---------------------------------------------
        // 1. Factorize t
        // ---------------------------------------------

        State need = {0, 0, 0, 0};

        int primes[4] = {2, 3, 5, 7};

        for (int i = 0; i < 4; i++) {

            while (t % primes[i] == 0) {

                need[i]++;
                t /= primes[i];
            }
        }

        // If t contains a prime other than 2,3,5,7,
        // no decimal digit product can produce it.
        if (t != 1)
            return "-1";


        // ---------------------------------------------
        // 2. Initialize DP
        // ---------------------------------------------

        A = need[0];
        B = need[1];
        C = need[2];
        D = need[3];

        int total =
            (A + 1) *
            (B + 1) *
            (C + 1) *
            (D + 1);

        memo.assign(total, -1);


        // ---------------------------------------------
        // 3. If num itself is valid, return it
        // ---------------------------------------------

        State rem = need;

        bool valid = true;

        for (char ch : num) {

            int digit = ch - '0';

            /*
                A zero makes the digit product zero,
                so it cannot divide positive t.
            */
            if (digit == 0) {

                valid = false;
                break;
            }

            rem = removeFactors(rem, digit);
        }

        if (valid &&
            rem[0] == 0 &&
            rem[1] == 0 &&
            rem[2] == 0 &&
            rem[3] == 0) {

            return num;
        }


        // ---------------------------------------------
        // 4. Try to find answer with SAME length
        // ---------------------------------------------

        int n = num.size();

        vector<State> prefixNeed(n + 1);

        vector<bool> prefixValid(n + 1, true);

        prefixNeed[0] = need;

        for (int i = 0; i < n; i++) {

            prefixNeed[i + 1] = prefixNeed[i];

            int digit = num[i] - '0';

            if (digit == 0) {

                prefixValid[i + 1] = false;

            } else {

                prefixValid[i + 1] = prefixValid[i];

                prefixNeed[i + 1] =
                    removeFactors(
                        prefixNeed[i + 1],
                        digit
                    );
            }
        }


        /*
            Work from right to left.

            This lets us change the number at the latest
            possible position, making the result as small
            as possible.
        */

        for (int i = n - 1; i >= 0; i--) {

            if (!prefixValid[i])
                continue;

            State base = prefixNeed[i];

            int original = num[i] - '0';

            int start = original + 1;

            // First digit cannot be zero.
            if (i == 0)
                start = max(start, 1);

            for (int digit = start; digit <= 9; digit++) {

                State remaining =
                    removeFactors(base, digit);

                int suffixLength = n - i - 1;

                /*
                    Can the suffix satisfy the remaining
                    factors within suffixLength positions?
                */
                if (minDigits(remaining) <= suffixLength) {

                    string ans = num.substr(0, i);

                    ans += char('0' + digit);

                    ans += buildSuffix(
                        suffixLength,
                        remaining
                    );

                    return ans;
                }
            }
        }


        // ---------------------------------------------
        // 5. Same length impossible
        //
        // Find minimum possible length.
        // ---------------------------------------------

        int requiredLength = minDigits(need);

        int length = max(n + 1, requiredLength);


        // ---------------------------------------------
        // 6. Construct smallest number of that length
        // ---------------------------------------------

        while (true) {

            for (int first = 1; first <= 9; first++) {

                State remaining =
                    removeFactors(need, first);

                int suffixLength = length - 1;

                if (minDigits(remaining) <= suffixLength) {

                    string ans;

                    ans += char('0' + first);

                    ans += buildSuffix(
                        suffixLength,
                        remaining
                    );

                    return ans;
                }
            }

            length++;
        }
    }
};