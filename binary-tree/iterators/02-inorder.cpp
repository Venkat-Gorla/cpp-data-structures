//----------------------------------------
// Inorder iterator
// - this comes very handy when dealing with BST since the nodes will be returned in sorted order
// Topics covered
// - iterator implementation
// - getting inorder successor with the iterator becomes trivial (almost)

#include <iostream>
#include <vector>
#include <stack>
#include <numeric> // iota
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
// end InorderIterator

// fwd declarations
void TestIterator(Node* root);
void print(InorderIterator & it);
void TestSuccessor(Node* root, const vector<int> & keys);
// end fwd declarations

// get inorder successor via the iterator
Node* GetSuccessor(Node* root, const int key)
{
    InorderIterator it(root);
    auto current = it.next();

    while (current)
    {
        const auto prev = current;
        current = it.next();

        if (prev->data == key)
            return current;
    }

    return nullptr;
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

        TestIterator(root);

        vector<int> keys(4);
        iota(keys.begin(), keys.end(), 3);
        TestSuccessor(root, keys);
    }

    return 0;
}

void TestIterator(Node* root)
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

void print(InorderIterator & it)
{
    for (auto current = it.next(); current; current = it.next())
    {
        cout << current->data << " ";
    }

    cout << endl;
}

void TestSuccessor(Node* root, const vector<int> & keys)
{
    for (auto key : keys)
    {
        auto successor = GetSuccessor(root, key);
        if (successor)
            cout << "Inorder successor for " << key << " is " << successor->data << endl;
        else
            cout << "Inorder successor for " << key << " is *Not* found" << endl;
    }
}

/*
Output:
Fwd inorder traversal: 1 2 3 4 5
Reverse inorder traversal: 5 4 3 2 1
Inorder successor for 3 is 4
Inorder successor for 4 is 5
Inorder successor for 5 is *Not* found
Inorder successor for 6 is *Not* found

*/

