
// Here we will explore a collection of binary tree problems and their solutions

//----------------------------------------
// Inorder iteration without using recursion

#include <iostream>
#include <stack>
using namespace std;

// In a future implementation we will look into how to do automatic memory
// management when the tree goes out of scope; this code will focus on the
// inorder algorithm
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

void Inorder(Node* root)
{
    stack<Node*> nodeStack;

    Node* current = root;

    do
    {
        while (current)
        {
            nodeStack.push(current);
            current = current->left;
        }

        if (!nodeStack.empty())
        {
            current = nodeStack.top();
            nodeStack.pop();

            cout << current->data << " ";
            current = current->right;
        }
    } while (current || !nodeStack.empty());

    cout << endl;
}

int main(int argc, char *argv[])
{ 
    {
        // creating a BST to verify the sorted nature of inorder but can be any binary tree
        Node* root = Create(2);
        root->left = Create(1);
        root->right = Create(3);
        root->right->right = Create(4);

        Inorder(root);
    }

    return 0;
}

/*
Expected output:
1 2 3 4

Actual output:
1 2 3 4
*/

//----------------------------------------
// Binary tree using unique_ptr

#include <iostream>
#include <stack>
#include <memory> // unique_ptr
using namespace std;

struct Node
{
    int data;
    unique_ptr<Node> left;
    unique_ptr<Node> right;

    Node(int val)
      : data(val)
    {}
};

unique_ptr<Node> Create(int value)
{
    return make_unique<Node>(value);
}

void Inorder(Node* root)
{
    stack<Node*> nodeStack;

    Node* current = root;

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

            cout << current->data << " ";
            current = current->right.get();
        }
    } while (current || !nodeStack.empty());

    cout << endl;
}

int main(int argc, char *argv[])
{ 
    {
        unique_ptr<Node> root = Create(2);
        root->left = Create(1);
        root->right = Create(3);
        root->right->right = Create(4);

        Inorder(root.get());
    }

    return 0;
}

/*
Expected output:
1 2 3 4

Actual output:
1 2 3 4
*/

//----------------------------------------
// Given a binary tree, print all root to leaf paths

#include <iostream>
#include <vector>
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

// caller should ensure "current" is not null
bool isLeaf(const Node* current)
{
    return !(current->left || current->right);
}

// utility function to print one path
void print(const vector<Node*> & buffer)
{
    for (const auto current : buffer)
    {
        cout << current->data << " ";
    }
    cout << endl;
}

// In the future we will look into how this can be done without using recursion
void printRootToLeafPaths(Node* current, vector<Node*> & buffer)
{
    if (!current)
    {
        return;
    }

    buffer.push_back(current);

    if (isLeaf(current))
    {
        print(buffer);
    }
    else 
    {
        printRootToLeafPaths(current->left, buffer);
        printRootToLeafPaths(current->right, buffer);
    }

    buffer.pop_back();
}

void printRootToLeafPaths(Node* root)
{
    vector<Node*> dummy;
    printRootToLeafPaths(root, dummy);
}

int main(int argc, char *argv[])
{ 
    {
        Node* root = Create(2);
        root->left = Create(1);
        root->right = Create(3);
        root->right->right = Create(4);

        printRootToLeafPaths(root);
    }

    return 0;
}

/*
Expected output:
2 1
2 3 4

Actual output:
2 1
2 3 4

*/

//----------------------------------------
// preorder traversal without recursion

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

void preorder(Node* root)
{
    if (!root)
    {
        return;
    }

    stack<Node*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty())
    {
        auto current = nodeStack.top();
        nodeStack.pop();
        cout << current->data << " ";

        if (current->right)
            nodeStack.push(current->right);

        if (current->left)
            nodeStack.push(current->left);
    }

    cout << endl;
}

int main(int argc, char *argv[])
{ 
    {
        Node* root = Create(2);
        root->left = Create(1);
        root->right = Create(3);
        root->right->right = Create(4);

        preorder(root);
    }

    return 0;
}

/*
Expected output:
2 1 3 4

Actual output:
2 1 3 4

*/

//----------------------------------------
// given a binary tree and a key (that may or may not be present in it) find the key's Inorder successor

/*
    1
   /  \
   2   3

Inorder: 2 1 3

Key  Output
2    1
1    3
3    null

*/

#include <iostream>
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

// we will solve this problem using recursion, a different solution using iteration
// will be discussed separately.

// The idea is to keep track of the previously visited node while doing recursive Inorder;
// In C++ it can be done with a double pointer i.e. pointer to pointer
Node* inorderSuccessor(
    Node* current,
    const int K,
    Node** prev)
{
    if (!current)
        return nullptr;

    auto result = inorderSuccessor(current->left, K, prev);
    if (result)
        return result;

    if (*prev && (*prev)->data == K)
        return current;

    *prev = current;

    return inorderSuccessor(current->right, K, prev);
}

Node* inorderSuccessor(Node* root, const int K)
{
    Node* prev{nullptr};

    return inorderSuccessor(root, K, &prev);
}

void testcase(Node* root, const int K)
{
    auto result = inorderSuccessor(root, K);
    if (result)
        cout << "Inorder successor for key " << K << " is " << result->data << endl;
    else
        cout << "Inorder successor for key " << K << " Not found" << endl;
}

int main(int argc, char *argv[])
{ 
    {
        Node* root = Create(1);
        root->left = Create(2);
        root->right = Create(3);
        
        testcase(root, 2);
        testcase(root, 1);
        testcase(root, 3);
    }

    return 0;
}

/*
Expected output:

Actual output:
Inorder successor for key 2 is 1
Inorder successor for key 1 is 3
Inorder successor for key 3 Not found

*/
