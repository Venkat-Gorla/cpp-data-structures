//----------------------------------------
// Binary search tree
// Topics covered:
// - tree creation, node insertion with and without recursion

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

// recursive insert function for bst
Node* rInsert(Node* root, int value)
{
    if (root == nullptr)
        return Create(value);

    if (value < root->data)
    {
        root->left = rInsert(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = rInsert(root->right, value);
    }
    else
    {
        // ignore dupe values; an alternate solution is to have a ref count
        // inside every node and increment it when we get a dupe value
    }

    return root;
}

// wrapper function to create bst from a list of keys
Node* rCreate(const vector<int> & input)
{
    Node* root = nullptr;
    for (auto value : input)
        root = rInsert(root, value);

    return root;
}

// bst insert function without using recursion
Node* Insert(Node* root, int value)
{
    if (root == nullptr)
        return Create(value);

    Node* current = root;
    while (true)
    {
        if (value == current->data)
        {
            // dupe value, ignore
            break;
        }

        if (value < current->data)
        {
            if (current->left == nullptr)
            {
                current->left = Create(value);
                break;
            }
            else
            {
                current = current->left;
            }
        }
        else
        {
            if (current->right == nullptr)
            {
                current->right = Create(value);
                break;
            }
            else
            {
                current = current->right;
            }
        }
    }

    return root;
}

// wrapper function
Node* Create(const vector<int> & input)
{
    Node* root = nullptr;
    for (auto value : input)
        root = Insert(root, value);

    return root;
}

// for testing
void Inorder(Node* root)
{
    if (root)
    {
        Inorder(root->left);
        cout << root->data << " ";
        Inorder(root->right);
    }
}

void testcase(const vector<int> & input)
{
    {
        auto root = rCreate(input);
        cout << "Inorder traversal of bst created using recursion is ";
        Inorder(root);
        cout << endl;
    }

    {
        auto root = Create(input);
        cout << "Inorder traversal of bst created *WITHOUT* recursion is ";
        Inorder(root);
        cout << endl;
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

        const vector<int> input{3, 1, 2, 5, 4};
        testcase(input);
    }

    return 0;
}

/*
Output:
Inorder traversal of bst created using recursion is 1 2 3 4 5
Inorder traversal of bst created *WITHOUT* recursion is 1 2 3 4 5

*/
