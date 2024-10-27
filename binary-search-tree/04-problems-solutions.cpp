// Solutions for some commonly asked Binary tree/ BST questions

//----------------------------------------
// - check if a binary tree is BST or not

/*
There are many solutions to this problem, we will explore a solution that uses recursion and min-max range for every node in the tree.
- given a root node, all the nodes in its left sub-tree must be less than the root, so the max is decided by the root; there is no min value.
- for the same root, all the nodes in its right sub-tree must be greater than the root, so the min is the root
- we will apply this check as we recursively traverse the tree
-
- **Solution 2: use the Inorder iterator class and ensure the nodes are present in sorted order.
*/

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

// fwd declarations
bool isBst(const Node* root, int minVal, int maxVal);
void testPositive();
void testNegative();
void testcase(const Node* root);
// end fwd declarations

bool isBst(const Node* root)
{
    return isBst(root, INT_MIN, INT_MAX);
}

bool isBst(const Node* root, int minVal, int maxVal)
{
    if (root == nullptr)
        return true;

    if (root->data < minVal || root->data > maxVal)
        return false;

    return isBst(root->left, minVal, root->data) &&
        isBst(root->right, root->data, maxVal);
}

class InorderIterator
{
  public:
    InorderIterator(const Node* root, bool fwd = true)
      : m_fwd(fwd)
    {
        pushNodes(root);
    }

    const Node* next()
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
    void pushNodes(const Node* current)
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
    stack<const Node*> m_stack;

    // prevent object copy
    InorderIterator(const InorderIterator&) = delete;
};
// end InorderIterator

// **Solution 2: use the Inorder iterator class and ensure the nodes are present in sorted order.
bool isBst_iter(const Node* root)
{
    InorderIterator it(root);

    const Node* previous{nullptr};
    for (auto current = it.next(); current; current = it.next())
    {
        if (previous && previous->data > current->data)
            return false;

        previous = current;
    }

    return true;
}

int main(int argc, char *argv[])
{ 
    {
        testPositive();
        cout << endl;
        testNegative();
    }

    return 0;
}

void testPositive()
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

void testNegative()
{
        /*
            3 
          /   \
          1     5 
         / \    /
        -1  6  4 

        */

    Node* root = Create(3);
    root->left = Create(1);
    root->right = Create(5);
    root->left->left = Create(-1);
    root->left->right = Create(6);
    root->right->left = Create(4);

    testcase(root);
}

void testcase(const Node* root)
{
    {
        if (isBst(root))
            cout << "The given binary tree is a BST" << endl;
        else
            cout << "The given binary tree is *Not* a BST" << endl;
    }

    {
        if (isBst_iter(root))
            cout << "Calling isBst_iter(), The given binary tree is a BST" << endl;
        else
            cout << "Calling isBst_iter(), The given binary tree is *Not* a BST" << endl;
    }
}

/*
Output:
The given binary tree is a BST
Calling isBst_iter(), The given binary tree is a BST

The given binary tree is *Not* a BST
Calling isBst_iter(), The given binary tree is *Not* a BST

*/

//----------------------------------------
// - kthSmallest element in BST

/*
- **Solution: use the Inorder iterator class and return the kth node
- k is assumed to be >= 1 and <= number of nodes in the BST
*/

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

// fwd declarations
void testKthSmallest();
// end fwd declarations

class InorderIterator
{
  public:
    InorderIterator(const Node* root, bool fwd = true)
      : m_fwd(fwd)
    {
        pushNodes(root);
    }

    const Node* next()
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
    void pushNodes(const Node* current)
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
    stack<const Node*> m_stack;

    // prevent object copy
    InorderIterator(const InorderIterator&) = delete;
};
// end InorderIterator

const Node* kthSmallest(const Node* root, int k)
{
    InorderIterator it(root);

    for (auto current = it.next(); current; current = it.next())
    {
        k--;
        if (k == 0)
            return current;
    }

    return nullptr;
}

int main(int argc, char *argv[])
{ 
    {
        testKthSmallest();
    }

    return 0;
}

void testKthSmallest()
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

    for (int k = 3; k <= 6; k++)
    {
        auto answer = kthSmallest(root, k);

        if (answer)
            cout << "For k = " << k << ", the answer is " << answer->data << endl;
        else
            cout << "For k = " << k << ", the answer is *Not* found" << endl;
    }
}

/*
Output:
For k = 3, the answer is 3
For k = 4, the answer is 4
For k = 5, the answer is 5
For k = 6, the answer is *Not* found

*/

