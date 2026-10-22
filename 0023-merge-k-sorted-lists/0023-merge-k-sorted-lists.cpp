class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>,
            function<bool(ListNode*, ListNode*)>> pq(
            [](ListNode* a, ListNode* b) {
                return a->val > b->val;
            });

        for (auto node : lists)
            if (node) pq.push(node);

        ListNode dummy, *cur = &dummy;
        while (!pq.empty()) {
            auto node = pq.top(); pq.pop();
            cur->next = node;
            cur = node;
            if (node->next) pq.push(node->next);
        }
        cur->next = nullptr;
        return dummy.next;
    }
};