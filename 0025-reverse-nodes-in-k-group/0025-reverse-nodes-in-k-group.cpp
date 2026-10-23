class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, head), *prev = &dummy;
        while (true) {
            ListNode *end = prev;
            for (int i = 0; i < k && end; i++) end = end->next;
            if (!end) break;
            ListNode *cur = prev->next, *next = end->next, *p = next;
            while (cur != next) {
                ListNode* t = cur->next;
                cur->next = p;
                p = cur;
                cur = t;
            }
            ListNode* old = prev->next;
            prev->next = end;
            prev = old;
        }
        return dummy.next;
    }
};