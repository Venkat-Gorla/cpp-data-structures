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

    // the idea is to swap every pair of elements inside the while loop
    // and establish the connection between the previous pair and the current pair;
    // if an odd element is present at the end of the list, it will be done outside the loop

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
// - Print alternate nodes of the given Linked List, first from head to end, and then from end to head. 

/*
If Linked List has even number of nodes, then skip the last node. 
For Linked List 1->2->3->4->5, print 1 3 5 5 3 1. 
For Linked List 1->2->3->4->5->6, print 1 3 5 5 3 1.
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

// solution function
void printAlternate(Node* head)
{
    if (!head)
        return;

    cout << head->data << " ";

    if (head->next)
        printAlternate(head->next->next);

    cout << head->data << " ";
}

// fwd declarations
void testcase(const vector<int> & input);
// end fwd declarations

int main(int argc, char *argv[])
{
    {
        vector<int> input(5);
        iota(input.begin(), input.end(), 1);
        testcase(input);
    }

    {
        cout << endl;
        vector<int> input(6);
        iota(input.begin(), input.end(), 1);
        testcase(input);
    }

    return 0;
}

void testcase(const vector<int> & input)
{
    Node* head{createList(input)};
    cout << "Input list" << endl;
    printList(head);
    cout << "Alternate list: ";
    printAlternate(head);
    cout << endl;
}

/*
Output:
Input list
Printing list: 1 2 3 4 5
Alternate list: 1 3 5 5 3 1

Input list
Printing list: 1 2 3 4 5 6
Alternate list: 1 3 5 5 3 1

*/

//----------------------------------------
// - Given a linked list, write a function to reverse it using O(1) space

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

// solution function
// we will look at a different approach using a previous pointer,
// without using the stack "push" function presented earlier in list intro
Node* listReverse(Node* head)
{
    // special casing not needed for empty list

    Node* current{head};
    Node* previous{nullptr};

    while (current)
    {
        Node* next{current->next};

        current->next = previous;
        previous = current;
        current = next;
    }

    return previous;
}

// fwd declarations
void testReverseList(const vector<int> & input);
// end fwd declarations

int main(int argc, char *argv[])
{
    {
        const vector<int> empty{};
        testReverseList(empty);
    }

    {
        cout << endl;
        vector<int> input(5);
        iota(input.begin(), input.end(), 1);
        testReverseList(input);
    }

    return 0;
}

void testReverseList(const vector<int> & input)
{
    Node* head{createList(input)};
    printList(head);

    head = listReverse(head);
    cout << "Printing reversed list" << endl;
    printList(head);
}

/*
Output:
Printing list:
Printing reversed list
Printing list:

Printing list: 1 2 3 4 5
Printing reversed list
Printing list: 5 4 3 2 1

*/

//----------------------------------------
// - Given a linked list, write a function to reverse every k nodes (where k is an input to the function).

/*
Example:
Inputs:  1->2->3->4->5->6->7->8->NULL and k = 3 
Output:  3->2->1->6->5->4->8->7->NULL. 

Inputs:   1->2->3->4->5->6->7->8->NULL and k = 5
Output:  5->4->3->2->1->8->7->6->NULL. 
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

// solution function using recursion
Node* KReverse(Node* head, const int K)
{
    if (head == nullptr)
        return head;

    Node* previous{nullptr};
    Node* current{head};

    for (int index = 0; current && index < K; index++)
    {
        Node* next{current->next};

        current->next = previous;
        previous = current;
        current = next;
    }

    head->next = KReverse(current, K);

    return previous;
}

// fwd declarations
void testKReverse(const vector<int> & input, const int K);
// end fwd declarations

int main(int argc, char *argv[])
{
    {
        vector<int> input(9);
        iota(input.begin(), input.end(), 1);
        testKReverse(input, 3);

        cout << endl;
        testKReverse(input, 5);
    }

    return 0;
}

void testKReverse(const vector<int> & input, const int K)
{
    Node* head{createList(input)};
    printList(head);

    head = KReverse(head, K);
    cout << "Printing K(=" << K << ") reversed list" << endl;
    printList(head);
}

/*
Output:
Printing list: 1 2 3 4 5 6 7 8 9
Printing K(=3) reversed list
Printing list: 3 2 1 6 5 4 9 8 7

Printing list: 1 2 3 4 5 6 7 8 9
Printing K(=5) reversed list
Printing list: 5 4 3 2 1 9 8 7 6

*/

