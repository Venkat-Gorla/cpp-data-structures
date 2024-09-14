//----------------------------------------
// Threaded binary tree and inorder traversal with O(1) space complexity

/*
With a normal binary tree you need a stack (recursive or explicit) to do inorder traversal. The additional space needed for the stack is O(height).

Threaded binary tree allows you to do inorder traversal without using a stack, so the space complexity is O(1).

Points to note for a threaded tree:
- any node that does Not have a right child instead stores a pointer to it's inorder successor
- that is how you eliminate the need for a stack
- you have a bool inside every node that differentiates between a normal right pointer and a thread pointer
- converting a normal tree to threaded involves doing an inorder traversal and populate the thread connections
- during the conversion from normal to threaded, any node that has a left sub-tree is visited twice; once when going down the tree and again when coming up the tree
- when going down, you create the thread connection
- when coming up, it means you have already visited the left sub-tree, so you print the current node and move to it's right child
- understanding all these points will help you do the actual coding!

*/

#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
    bool isThread; // true if right pointer is a thread connection, false otherwise
};

Node* Create(int value)
{
    return new Node{value, nullptr, nullptr, false};
}

void convertToThreaded(Node* root)
{
    auto current{root};

    while (current)
    {
        if (current->left == nullptr)
        {
            // this is the simple case, when moving to the right child there is no bookkeeping to be done

            // print current
            current = current->right;
        }
        else
        {
            // find the inorder predecessor of "current" and set it's thread connection
            // the predecessor by definition will not have a right child

            auto predecessor{current->left};
            while (predecessor->right && predecessor->right != current)
            {
                predecessor = predecessor->right;
            }

            if (predecessor->right == nullptr)
            {
                // thread connection is yet to be created and we are visiting "current" for the first time;
                // we are going down the tree
                predecessor->right = current;
                predecessor->isThread = true;
                current = current->left;
            }
            else
            {
                // thread connection is already created and we are visiting "current" for the second time;
                // it means we are coming up the tree after visiting the left sub-tree of "current"

                // print current
                current = current->right;
            }
        }
    }
}

// "current" can be null
Node* leftMost(Node* current)
{
    while (current && current->left)
        current = current->left;

    return current;
}

// when you have a threaded tree, you can do inorder traversal with O(1) space
void threadedInorder(Node* root)
{
    cout << "Inorder traversal of threaded binary tree is ";

    auto current{leftMost(root)};

    while (current)
    {
        cout << current->data << " ";

        if (current->isThread)
            current = current->right;
        else
            current = leftMost(current->right);
    }

    cout << endl;
}

void testcase(Node* root)
{
    convertToThreaded(root);
    threadedInorder(root);
}

int main(int argc, char *argv[])
{ 
    {
        /*
            3 
          /   \
          2    4 
         /
        1

        */

        Node* root = Create(3);
        root->left = Create(2);
        root->right = Create(4);
        root->left->left = Create(1);

        testcase(root);
    }

    return 0;
}

/*
Output:
Inorder traversal of threaded binary tree is 1 2 3 4

*/

