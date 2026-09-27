class Solution {
public:
    string reverseParentheses(string s) {
        vector<string> st(1);

        for (char c : s) {
            if (c == '(') st.push_back("");
            else if (c == ')') {
                reverse(st.back().begin(), st.back().end());
                string x = st.back();
                st.pop_back();
                st.back() += x;
            } else {
                st.back() += c;
            }
        }

        return st[0];
    }
};