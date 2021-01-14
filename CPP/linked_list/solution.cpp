#include <iostream>

class ListNode
{
public:
    int val;
    ListNode* next;

    ListNode() 
    {
        this->val = -1;
        this->next = nullptr;
    }
    ListNode(int x)
    {
        this->val = x;
        this->next = nullptr;
    }
};

class Solution
{
public:
    ListNode result;

    Solution() {}
    void addTwoNumbers(ListNode& l1, ListNode& l2, int c = 0)
    {
        ListNode *temp = &this->result;

        while ((&l1 != nullptr) && (&l2 != nullptr))
        { 
            int sum = l1.val + l2.val + c;
            c = 0;

            if (10 <= sum)
            {
                sum = sum - 10;
                c = 1;
            }
            
            if (-1 == temp->val)
            {
                temp->val = sum;
                std::cout << "head: " << temp->val << std::endl;
            }
            else
            {
                temp->next =  new ListNode(sum);
                temp = temp->next;
                std::cout << "node: " << temp->val << std::endl;
            }

            if ((l1.next != nullptr) && (l2.next != nullptr))
            {
                l1 = *l1.next;
                l2 = *l2.next;
            }
            else
            {
                break;
            }
        } 
    }

};


int main()
{
    ListNode l1(2);
    l1.next = new ListNode(4);
    l1.next->next = new ListNode(3);

    ListNode l2(5);
    l2.next = new ListNode(6);
    l2.next->next = new ListNode(4);

    Solution solution;
    solution.addTwoNumbers(l1, l2);
    ListNode* result =  &(solution.result);

    do
    {
        std::cout << result->val << " ";
        result = result->next;
    } while (result);

    fflush(stdout);
    //7 0 8
    return 0;
}