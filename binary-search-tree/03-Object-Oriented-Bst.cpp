//----------------------------------------
// Object oriented BST implementation using class and unique_ptr for memory management
// - we will do Inorder traversal (using stack) of the bst to show it's sorted nature

#include <iostream>
#include <memory> // unique_ptr
#include <vector>
#include <stack>
#include <iterator> // ostream_iterator
using namespace std;

class BinarySearchTree
{
  public:
    bool insert(int value);
    vector<int> getInorder() const;

  private:
    struct Node
    {
        int data;
        unique_ptr<Node> left;
        unique_ptr<Node> right;

        Node(int value)
          : data(value)
        {
        }

        ~Node()
        {
            cout << "Deleting Node with value " << data << endl;
        }
    };

  private:
    unique_ptr<Node> m_root;
};

// Bst implementation
bool BinarySearchTree::insert(int value)
{
    unique_ptr<Node> newNode(new Node(value));
    if (!m_root)
    {
        m_root = std::move(newNode);
        return true;
    }

    Node* temp = m_root.get();
    while (true)
    {
        if (newNode->data == temp->data)
            return false;
        if (newNode->data < temp->data)
        {
            if (temp->left == nullptr)
            {
                temp->left = std::move(newNode);
                return true;
            }
            temp = temp->left.get();
        }
        else
        {
            if (temp->right == nullptr)
            {
                temp->right = std::move(newNode);
                return true;
            }
            temp = temp->right.get();
        }
    }
}

vector<int> BinarySearchTree::getInorder() const
{
    vector<int> inorder;

    stack<Node*> nodeStack;

    Node* current = m_root.get();

    do
    {
        while (current)
        {
            nodeStack.push(current);
            current = current->left.get();
        }

        if (!nodeStack.empty())
        {
            current = nodeStack.top();
            nodeStack.pop();

            inorder.push_back(current->data);
            current = current->right.get();
        }
    } while (current || !nodeStack.empty());

    return inorder;
}
// end Bst implementation

// fwd declarations
void testInorder();
// end fwd declarations

int main(int argc, char *argv[])
{ 
    {
        testInorder();
    }

    return 0;
}

void testInorder()
{
        /*
            3 
          /   \
          1     5 
           \    /
            2  4 

        */

    const vector<int> keys{3, 1, 5, 2, 4};
    BinarySearchTree bst;
    for (auto key : keys)
    {
        bst.insert(key);
    }

    auto inorder = bst.getInorder();

    cout << "Printing Inorder of the Bst: ";
    copy(inorder.begin(), inorder.end(), ostream_iterator<int>(cout, " "));
    cout << endl << endl;

    // you will see some additional cout output when the bst goes out of scope
}

/*
Output:
Printing Inorder of the Bst: 1 2 3 4 5

Deleting Node with value 3
Deleting Node with value 5
Deleting Node with value 4
Deleting Node with value 1
Deleting Node with value 2
*/

