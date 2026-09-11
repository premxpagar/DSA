class Solution {
public:
    int totalNumbers(vector<int>& d) {
        set<int> s;
        for(int i=0;i<d.size();i++)
            for(int j=0;j<d.size();j++)
                for(int k=0;k<d.size();k++)
                    if(i!=j && j!=k && i!=k && d[i]!=0 && d[k]%2==0)
                        s.insert(d[i]*100+d[j]*10+d[k]);
        return s.size();
    }
};