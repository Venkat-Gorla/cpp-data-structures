//----------------------------------------
// - Quick sort on linked list

/*
- Quick sort is recursive in nature and is a divide and conquer approach
- The idea is to designate one element in your input as "pivot"
- process the remaining elements and separate them into two sub lists, one that contains all elements that are less than the pivot and the other one with elements that are greater than the pivot
- recursively sort the two sub lists
- join the sub lists and the pivot element together, return to caller
*/

#include <iostream>
#include <vector>
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

void printList(Node* head)
{
    cout << "Printing list: ";
    for (auto current = head; current; current = current->next)
    {
        cout << current->data << " ";
    }
    cout << endl;
}
// end list creation and helper functions

// in-place push function, no memory allocation
void push(Node** headref, Node* current)
{
    current->next = *headref;
    *headref = current;
}

// solution function
Node* quickSort(Node* head)
{
    if (!head)
        return head;

    // assume "head" is pivot

    Node* small{nullptr};
    Node* big{nullptr};
    Node* current{head->next};

    while (current)
    {
        Node* next{current->next};

        if (current->data < head->data)
            push(&small, current);
        else
            push(&big, current);

        current = next;
    }

    small = quickSort(small);
    big = quickSort(big);

    head->next = big;

    if (!small)
        return head;

    // attach last node of "small" to head
    current = small;
    while (current->next)
        current = current->next;

    current->next = head;

    return small;
}

// fwd declarations
void testQuickSort(const vector<int> & input);
// end fwd declarations

int main(int argc, char *argv[])
{
    {
        const vector<int> input;
        testQuickSort(input);
    }

    {
        cout << endl;
        const vector<int> input{5, 4, 3, 2, 1};
        testQuickSort(input);
    }

    {
        cout << endl;
        const vector<int> input{0, 1, -2, 3, 4, 5, -5};
        testQuickSort(input);
    }

    return 0;
}

void testQuickSort(const vector<int> & input)
{
    Node* head{createList(input)};

    cout << "Printing original list" << endl;
    printList(head);

    head = quickSort(head);
    cout << "Printing sorted list" << endl;
    printList(head);
}

/*
Output:
Printing original list
Printing list:
Printing sorted list
Printing list:

Printing original list
Printing list: 5 4 3 2 1
Printing sorted list
Printing list: 1 2 3 4 5

Printing original list
Printing list: 0 1 -2 3 4 5 -5
Printing sorted list
Printing list: -5 -2 0 1 3 4 5

*/

