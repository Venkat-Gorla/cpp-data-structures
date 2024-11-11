//----------------------------------------
// - Object oriented Singly Linked list using unique_ptr for memory management
// - test cases for insert: sequential, reverse and random

#include <iostream>
#include <cassert>
#include <vector>
#include <memory> // unique_ptr
using namespace std;

class LinkedList
{
  public:
    LinkedList()
      : m_length(0)
    {
    }

    bool insert(const int index, int value);
    void print() const;

  private:
    struct Node
    {
        int data;
        unique_ptr<Node> next;

        Node(int value, Node* nextPtr = nullptr)
          : data(value)
          , next(nextPtr)
        {
        }

        ~Node()
        {
            cout << "Deleting Node with value " << data << endl;
        }
    };

  private:
    unique_ptr<Node> m_head;
    int m_length;
};

// this might seem like a normal method, but the presence of 
// the unique_ptr makes it interesting and tricky :)
bool LinkedList::insert(const int index, int value)
{
    if (index < 0 || index > m_length)
        return false;

    if (index == 0)
    {
        // this will handle the case whether m_head is null or not
        unique_ptr<Node> newNode(new Node(value, m_head.release()));
        m_head = std::move(newNode);
    }
    else
    {
        Node* current = m_head.get();
        Node* prev = current;

        for (int pos = 0; pos < index; pos++)
        {
            prev = current;
            current = current->next.get();
        }

        // the ownership of "current" (which is the same as prev->next) will be
        // given to newNode, so this is needed to ensure unique ownership of every node
        prev->next.release();

        unique_ptr<Node> newNode(new Node(value, current));
        prev->next = std::move(newNode);
    }

    m_length++;
    return true;
}

void LinkedList::print() const
{
    cout << "Printing linked list: ";

    for (auto current = m_head.get(); current; current = current->next.get())
    {
        cout << current->data << " ";
    }
    cout << endl;
}
// end class LinkedList

// fwd declarations
void testSequentialInsert();
void testReverseInsert();
void testRandomInsert();
// end fwd declarations

int main(int argc, char *argv[])
{ 
    testSequentialInsert();

    cout << endl;
    testReverseInsert();

    cout << endl;
    testRandomInsert();

    return 0;
}

void testSequentialInsert()
{
    cout << "testSequentialInsert()" << endl;

    const vector<int> input{1, 2, 3};

    LinkedList list;
    for (int i = 0; i < (int)input.size(); i++)
    {
        assert(list.insert(i, input[i]));
    }

    list.print();

    // some additional cout when the list goes out of scope
}

void testReverseInsert()
{
    cout << "testReverseInsert()" << endl;

    const vector<int> input{1, 2, 3};

    LinkedList list;
    for (auto value : input)
    {
        assert(list.insert(0, value));
    }

    list.print();
}

void testRandomInsert()
{
    cout << "testRandomInsert()" << endl;

    const vector<int> input{1, 2};

    LinkedList list;
    for (int i = 0; i < (int)input.size(); i++)
    {
        assert(list.insert(i, input[i]));
    }

    assert(list.insert(1, 3));

    list.print();
}

/*
Output:
testSequentialInsert()
Printing linked list: 1 2 3
Deleting Node with value 1
Deleting Node with value 2
Deleting Node with value 3

testReverseInsert()
Printing linked list: 3 2 1
Deleting Node with value 3
Deleting Node with value 2
Deleting Node with value 1

testRandomInsert()
Printing linked list: 1 3 2
Deleting Node with value 1
Deleting Node with value 3
Deleting Node with value 2

*/

