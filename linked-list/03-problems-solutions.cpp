// Solutions for some commonly asked Linked list questions

//----------------------------------------
// - Given a singly linked list, write a function to swap elements pairwise. 
// - both recursive and iterative solutions along with relevant test cases

/*
For example, if the linked list is 1->2->3->4->5->6->7 then the function should change it to 2->1->4->3->6->5->7, 
and if the linked list is 1->2->3->4->5->6 then the function should change it to 2->1->4->3->6->5
*/

#include <iostream>
#include <vector>
#include <numeric> // iota
using namespace std;

struct Node
{
    int data;
    Node* next; // for auto memory management, consider using unique_ptr
};

Node* create(int value)
{
    return new Node{value, nullptr};
}

Node* createList(const vector<int> & input)
{
    Node* head{nullptr};
    Node* tail{nullptr};

    for (auto value : input)
    {
        if (head == nullptr)
        {
            head = create(value);
            tail = head;
        }
        else
        {
            tail->next = create(value);
            tail = tail->next;
        }
    }

    return head;
}
// end list creation functions

void printList(Node* head)
{
    cout << "Printing list: ";
    for (auto current = head; current; current = current->next)
    {
        cout << current->data << " ";
    }
    cout << endl;
}

// recursive solution
Node* pairwiseSwap(Node* head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    auto subResult = pairwiseSwap(head->next->next);

    head->next->next = head;
    auto result = head->next;
    head->next = subResult;

    return result;
}

// iterative solution
Node* pairwiseSwap_iter(Node* head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    Node* answer = head->next;

    Node* previous = nullptr;
    Node* current = head;

    while (current && current->next)
    {
        if (previous)
            previous->next = current->next;

        Node* next = current->next->next;
        current->next->next = current;
        current->next = nullptr;

        previous = current;
        current = next;
    }

    previous->next = current;

    return answer;
}

// fwd declarations
void testPairwiseSwap(const vector<int> & input);
// end fwd declarations

int main(int argc, char *argv[])
{
    vector<int> listSizes(5);
    iota(listSizes.begin(), listSizes.end(), 1);

    for (auto listSize : listSizes)
    {
        vector<int> input(listSize);
        iota(input.begin(), input.end(), 1);
        testPairwiseSwap(input);
        cout << endl;
    }

    return 0;
}

void testPairwiseSwap(const vector<int> & input)
{
    {
        auto head{createList(input)};
        printList(head);

        cout << "List after calling recursive pairwiseSwap()" << endl;
        head = pairwiseSwap(head);
        printList(head);
    }

    {
        cout << endl;
        auto head{createList(input)};
        printList(head);

        cout << "List after calling iterative pairwiseSwap()" << endl;
        head = pairwiseSwap_iter(head);
        printList(head);
    }
}

/*
Output:
Printing list: 1
List after calling recursive pairwiseSwap()
Printing list: 1

Printing list: 1
List after calling iterative pairwiseSwap()
Printing list: 1

Printing list: 1 2
List after calling recursive pairwiseSwap()
Printing list: 2 1

Printing list: 1 2
List after calling iterative pairwiseSwap()
Printing list: 2 1

Printing list: 1 2 3
List after calling recursive pairwiseSwap()
Printing list: 2 1 3

Printing list: 1 2 3
List after calling iterative pairwiseSwap()
Printing list: 2 1 3

Printing list: 1 2 3 4
List after calling recursive pairwiseSwap()
Printing list: 2 1 4 3

Printing list: 1 2 3 4
List after calling iterative pairwiseSwap()
Printing list: 2 1 4 3

Printing list: 1 2 3 4 5
List after calling recursive pairwiseSwap()
Printing list: 2 1 4 3 5

Printing list: 1 2 3 4 5
List after calling iterative pairwiseSwap()
Printing list: 2 1 4 3 5

*/

//----------------------------------------

