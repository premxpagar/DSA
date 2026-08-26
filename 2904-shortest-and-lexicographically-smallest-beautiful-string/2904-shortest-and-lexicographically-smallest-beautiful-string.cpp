class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        string answer = "";

        for (int left = 0; left < n; left++) {
            int ones = 0;

            for (int right = left; right < n; right++) {
                ones += (s[right] == '1');

                if (ones == k) {
                    string candidate = s.substr(left, right - left + 1);

                    if (answer.empty() ||
                        candidate.size() < answer.size() ||
                        (candidate.size() == answer.size() &&
                         candidate < answer)) {
                        answer = candidate;
                    }

                    // Extending further only increases length
                    break;
                }
            }
        }

        return answer;
    }
};