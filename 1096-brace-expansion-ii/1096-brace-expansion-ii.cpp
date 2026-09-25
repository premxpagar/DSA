class Solution {
    string s;
    int i;

    set<string> parse() {
        set<string> res, cur = {""};

        while (i < s.size() && s[i] != '}') {
            if (s[i] == ',') {
                res.insert(cur.begin(), cur.end());
                cur = {""};
                i++;
            } else {
                set<string> part;
                if (s[i] == '{') {
                    i++;
                    part = parse();
                    i++;
                } else {
                    part.insert(string(1, s[i++]));
                }

                set<string> next;
                for (auto &a : cur)
                    for (auto &b : part)
                        next.insert(a + b);
                cur = next;
            }
        }

        res.insert(cur.begin(), cur.end());
        return res;
    }

public:
    vector<string> braceExpansionII(string expression) {
        s = expression;
        i = 0;
        set<string> ans = parse();
        return vector<string>(ans.begin(), ans.end());
    }
};