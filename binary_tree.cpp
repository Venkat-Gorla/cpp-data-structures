
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
