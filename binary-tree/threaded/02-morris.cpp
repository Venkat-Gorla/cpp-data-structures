//----------------------------------------
// Binary tree Morris Inorder/ Preorder traversal

/*
Morris traversal is based on the concept of threaded binary tree and it allows you to do Inorder/ preorder traversal using O(1) space -- i.e. no stack or recursion.
- as you traverse the tree, it involves making temp changes to the tree and later reverting them.
- before visiting the left sub-tree of a node, you save a pointer to the current node inside the tree itself and remove the change after the left sub-tree is visited.
- so if the binary tree is read-only, this technique cannot be used.
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

// fwd declarations
void testInorderMorris(Node* root);
// end fwd declarations

void inorderMorris(Node* root)
{
    cout << "Inorder traversal using Morris method: ";

    auto current{root};

    while (current)
    {
        if (current->left == nullptr)
        {
            cout << current->data << " ";
            current = current->right;
        }
        else
        {
            auto predecessor{current->left};
            while (predecessor->right && predecessor->right != current)
            {
                predecessor = predecessor->right;
            }

            if (predecessor->right == nullptr)
            {
                // first time visiting "current", save it's pointer and move to the left;
                // we are going down
                // cout << current->data << " "; // if you want preorder traversal
                predecessor->right = current;
                current = current->left;
            }
            else
            {
                // thread connection is already created, we are coming up after visiting the
                // left sub-tree; so rollback the change done earlier and print "current"
                predecessor->right = nullptr;
                cout << current->data << " "; // for inorder traversal
                current = current->right;
            }
        }
    }

    cout << endl;
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

        testInorderMorris(root);
    }

    return 0;
}

void testInorderMorris(Node* root)
{
    inorderMorris(root);
}

/*
Output:
Inorder traversal using Morris method: 1 2 3 4 5

*/

