class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int first = -1, prev = -1;
        int minDist = INT_MAX;
        int pos = 1;

        ListNode* p = head;
        ListNode* c = head->next;

        while (c->next) {
            if ((c->val > p->val && c->val > c->next->val) ||
                (c->val < p->val && c->val < c->next->val)) {

                if (first == -1)
                    first = pos;
                else {
                    minDist = min(minDist, pos - prev);
                }

                prev = pos;
            }

            p = c;
            c = c->next;
            pos++;
        }

        if (first == prev)
            return {-1, -1};

        return {minDist, prev - first};
    }
};