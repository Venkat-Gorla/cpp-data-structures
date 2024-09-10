//----------------------------------------
// Inorder iterator
// this comes very handy when dealing with BST since the nodes will be returned in sorted order

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

class InorderIterator
{
  public:
    InorderIterator(Node* root, bool fwd = true)
      : m_fwd(fwd)
    {
        pushNodes(root);
    }

    Node* next()
    {
        if (m_stack.empty())
        {
            // end of iteration
            return nullptr;
        }

        auto current = m_stack.top();
        m_stack.pop();

        if (m_fwd)
            pushNodes(current->right);
        else
            pushNodes(current->left);

        return current;
    }

  private:
    void pushNodes(Node* current)
    {
        while (current)
        {
            m_stack.push(current);
            if (m_fwd)
                current = current->left;
            else
                current = current->right;
        }
    }

  private:
    const bool m_fwd;
    stack<Node*> m_stack;

    // prevent object copy
    InorderIterator(const InorderIterator&) = delete;
};

void print(InorderIterator & it)
{
    for (auto current = it.next(); current; current = it.next())
    {
        cout << current->data << " ";
    }

    cout << endl;
}

void testcase(Node* root)
{
    {
        cout << "Fwd inorder traversal: ";
        InorderIterator it(root);
        print(it);
    }

    {
        cout << "Reverse inorder traversal: ";
        InorderIterator it(root, false);
        print(it);
    }
}

int main(int argc, char *argv[])
{ 
    {
        /*
            3 
          /   \
          1     5 
           \    /
            2  4 

        */

        Node* root = Create(3);
        root->left = Create(1);
        root->right = Create(5);
        root->left->right = Create(2);
        root->right->left = Create(4);

        testcase(root);
    }

    return 0;
}

/*
Output:
Fwd inorder traversal: 1 2 3 4 5
Reverse inorder traversal: 5 4 3 2 1

*/

