# Add two numbers as a linked list

<p>
<em>This problem was recently asked by Microsoft!</em>

You are given two linked-lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

**Example:**<br />
**Input:** (2 -> 4 -> 3) + (5 -> 6 -> 4)<br />
**Output:** 7 -> 0 -> 8<br />
**Explanation:** 342 + 465 = 807.<br />

Here is the function signature as a starting point (in C++):
</p>

```cpp
// Definition for singly-linked list.
class ListNode
{
public:
    ListNode(x)
    {
        this->val = x;
        this->next = nullptr;
    }
    int val;
    ListNode* next;
};

class Solution
{
public:
    Solution(){}
    void addTwoNumbers(ListNode &l1, ListNode &l2, c = 0):
    // Fill this in.
    ListNode result;
};


int main()
{
    ListNode l1(2);
    l1.next = ListNode(4);
    l1.next.next = ListNode(3);

    ListNode l2(5);
    l2.next = ListNode(6);
    l2.next.next = ListNode(4);


    Solution solution;
    solution.addTwoNumbers(l1, l2);
    ListNode result = solution.result;

    do
    {
        std::cout << result.val << " ";
        result = result.next
    }while(result);

    fflush(stdout);
    //7 0 8
    return 0;
}
```