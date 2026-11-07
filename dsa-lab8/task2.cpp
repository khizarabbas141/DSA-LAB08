#include <iostream>
#include <vector>
#include <queue>

using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x),  next(nullptr) {}
};

struct CompareNode {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, CompareNode> minHeap;


    for (ListNode* list : lists) {
        if (list) {
            minHeap.push(list);
        }
    }

    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (!minHeap.empty()) {
        ListNode* curr = minHeap.top();
        minHeap.pop();

        tail->next = curr;
        tail = tail->next;

        if (curr->next) {
            minHeap.push(curr->next);
        }
    }

    return dummy.next;
    
}

void printList(ListNode* head) {
    while (head) {

        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);

    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);

    ListNode* l3 = new ListNode(2);
    l3->next = new ListNode(6);

    vector<ListNode*> lists = {l1, l2, l3};

    ListNode* result = mergeKLists(lists);
    cout << "Lists to be sorted: " << endl;
    printList(l1);
    printList(l2);
    printList(l3);
    cout << "Merged Sorted Linked List: ";
    printList(result);

    return 0;
}