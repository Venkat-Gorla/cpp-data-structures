//----------------------------------------
// preorder iterator for binary tree
// this is a useful technique to have in your toolkit, encapsulate tree traversals inside an iterator object for reuse
// the postorder iterator will be fun!

#include <iostream>
#include <stack>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
};

Node* Create(int value)
{
    return new Node{value, nullptr, nullptr};
}

class PreorderIterator 
{
  public:
    PreorderIterator(Node* root)
    {
        if (root)
        {
            m_stack.push(root);
        }
    }

    // will return null to signal the end of iteration
    Node* next()
    {
        if (m_stack.empty())
        {
            // end of iteration
            return nullptr;
        }

        auto current = m_stack.top();
        m_stack.pop();

        if (current->right)
            m_stack.push(current->right);

        if (current->left)
            m_stack.push(current->left);

        return current;
    }

  private:
    stack<Node*> m_stack;
};

void testcase(Node* root)
{
    cout << "Preorder traversal: ";
    PreorderIterator it(root);

    for (auto current = it.next(); current; current = it.next())
    {
        cout << current->data << " ";
    }

    cout << endl;
}

int main(int argc, char *argv[])
{ 
    {
        /*
            1
          /    \
          2     3
           \    /
            4  5

        */

        Node* root = Create(1);
        root->left = Create(2);
        root->right = Create(3);
        root->left->right = Create(4);
        root->right->left = Create(5);

        testcase(root);
    }

    return 0;
}

/*
Expected output:
Preorder traversal: 1 2 4 3 5

Actual output:
Preorder traversal: 1 2 4 3 5
*/

