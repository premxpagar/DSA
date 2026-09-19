class Solution {
public:
    bool checkOverlap(int r, int xc, int yc,
                      int x1, int y1, int x2, int y2) {
        int x = max(x1, min(xc, x2));
        int y = max(y1, min(yc, y2));
        return (x-xc)*(x-xc) + (y-yc)*(y-yc) <= r*r;
    }
};