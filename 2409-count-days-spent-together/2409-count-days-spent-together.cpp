class Solution {
public:
    int countDaysTogether(string a, string b, string c, string d) {
        auto day = [](string s) {
            int m[] = {31,28,31,30,31,30,31,31,30,31,30,31};
            int n = stoi(s.substr(3));
            for (int i = 0; i < stoi(s.substr(0,2)) - 1; i++)
                n += m[i];
            return n;
        };
        return max(0, min(day(b), day(d)) - max(day(a), day(c)) + 1);
    }
};