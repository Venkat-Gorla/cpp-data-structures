//----------------------------------------
// - Singly Linked list intro
// - reverse list using iteration and O(1) space
// - reverse list using recursion

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

// stack push function to insert at the head, we can use this to build a list in fwd or reverse direction;
// *headref can be null in case of empty list
void push(Node** headref, int value)
{
    auto current{create(value)};
    current->next = *headref;
    *headref = current;
}

Node* createList(const vector<int> & input)
{
    Node* head{nullptr};

    for (int i = input.size()-1; i >= 0; i--)
    {
        push(&head, input[i]);
    }

    return head;
}
// end list creation functions

// in-place push function that doesn't do new memory allocation
void push(Node** headref, Node* current)
{
    current->next = *headref;
    *headref = current;
}

// using iteration and O(1) space
Node* reverseList(Node* head)
{
    Node* reversedHead{nullptr};

    auto current{head};
    while (current)
    {
        auto next{current->next};
        push(&reversedHead, current);
        current = next;
    }

    return reversedHead;
}

Node* recursiveReverse(Node* head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    auto answer = recursiveReverse(head->next);

    head->next->next = head;
    head->next = nullptr;

    return answer;
}

void printList(Node* head)
{
    cout << "Printing list: ";

    for (auto current = head; current; current = current->next)
    {
        cout << current->data << " ";
    }
    cout << endl;
}

// fwd declarations
Node* testCreate();
void testReverseList(Node* head);
// end fwd declarations

int main(int argc, char *argv[])
{ 
    {
        auto head{testCreate()};
        testReverseList(head);
    }

    return 0;
}

Node* testCreate()
{
    vector<int> input(5);
    iota(input.begin(), input.end(), 1);

    auto head{createList(input)};
    printList(head);

    return head;
}

void testReverseList(Node* head)
{
    head = reverseList(head);

    cout << "Printing reversed list" << endl;
    printList(head);

    cout << "Reversing list again, using recursion" << endl;
    head = recursiveReverse(head);
    printList(head);
}

/*
Output:
Printing list: 1 2 3 4 5
Printing reversed list
Printing list: 5 4 3 2 1
Reversing list again, using recursion
Printing list: 1 2 3 4 5

*/

