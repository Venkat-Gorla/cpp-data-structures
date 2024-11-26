//----------------------------------------
// This code shows how to use unique_ptr that will do automatic memory cleanup of the binary tree when it goes out of scope

#include <iostream>
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

    // this is to ensure the tree gets cleaned up through the unique_ptr
    ~Node()
    {
        cout << "Deleting node with value " << data << endl;
    }
};

unique_ptr<Node> Create(int value)
{
    return make_unique<Node>(value);
}

// recursive preorder traversal that will show usage of unique_ptr
void preorder(Node* root)
{
    if (root)
    {
        cout << root->data << " ";
        preorder(root->left.get());
        preorder(root->right.get());
    }
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

        unique_ptr<Node> root = Create(1);
        root->left = Create(2);
        root->right = Create(3);
        root->left->right = Create(4);
        root->right->left = Create(5);

        cout << "Preorder traversal is ";
        preorder(root.get());
        cout << endl << endl;
    }

    return 0;
}

/*
Output:
Preorder traversal is 1 2 4 3 5

Deleting node with value 1
Deleting node with value 3
Deleting node with value 5
Deleting node with value 2
Deleting node with value 4
*/
