//----------------------------------------
// Binary search tree
// Topics covered:
// - node deletion
// - the tree should remain a bst after the deletion
// - pretty print that will show the tree structure

#include <iostream>
#include <vector>
#include <memory> // unique_ptr
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
void TestCreation(const vector<int> & input);
void TestDeletion(const vector<int> & input, const vector<int> & keysToDelete);
Node* rCreate(const vector<int> & input);
Node* rInsert(Node* root, int value);
bool IsLeaf(const Node* current);
Node* LeftMost(Node* current);
void PrettyDfs(Node* root, int depth = 0, const char* name = "");
// end fwd declarations

/* bst node deletion cases to handle:
if the deleted node:
- is a leaf, nothing to do
- has one child, the child will take it's place
- has two children, find the inorder successor of the deleted node that will take it's place
  - the inorder successor will be the smallest element inside the right sub-tree
*/

// this is the main deletion code
Node* DeleteNode(Node* root, int key)
{
    if (root == nullptr)
        return nullptr;

    if (key < root->data)
    {
        root->left = DeleteNode(root->left, key);
        return root;
    }
    else if (key > root->data)
    {
        root->right = DeleteNode(root->right, key);
        return root;
    }
    else
    {
        // root is being deleted, handle all cases listed above

        if (IsLeaf(root))
        {
            unique_ptr<Node> deleteRootAfterExit(root);
            return nullptr;
        }
        else if (root->left == nullptr)
        {
            unique_ptr<Node> deleteRootAfterExit(root);
            return root->right;
        }
        else if (root->right == nullptr)
        {
            unique_ptr<Node> deleteRootAfterExit(root);
            return root->left;
        }
        else
        {
            auto successor = LeftMost(root->right);
            root->data = successor->data;
            root->right = DeleteNode(root->right, successor->data);

            return root;
        }
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
        TestCreation(input);

        // the delete test case will cover all cases:
        // leaf node, node with one child and node with two children (root of the tree)
        const vector<int> keysToDelete{4, 1, 3};
        TestDeletion(input, keysToDelete);
    }

    return 0;
}

void TestCreation(const vector<int> & input)
{
    {
        auto root = rCreate(input);

        cout << "Printing bst created using recursion" << endl;
        PrettyDfs(root, 0, "root");
    }
}

void TestDeletion(const vector<int> & input, const vector<int> & keysToDelete)
{
    auto root = rCreate(input);

    for (auto key : keysToDelete)
    {
        root = DeleteNode(root, key);
        cout << endl << "Printing tree after deleting key " << key << endl;
        PrettyDfs(root, 0, "root");
    }
}

// wrapper function to create bst from a list of keys
Node* rCreate(const vector<int> & input)
{
    Node* root = nullptr;
    for (auto value : input)
        root = rInsert(root, value);

    return root;
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

bool IsLeaf(const Node* current)
{
    return !(current->left || current->right);
}

Node* LeftMost(Node* current)
{
    while (current && current->left)
        current = current->left;

    return current;
}

void PrettyDfs(Node* root, int depth, const char* name)
{
    if (root)
    {
        for (int counter = 0; counter < depth; ++counter)
        {
            cout << "   |";
        }

        cout << "-->" << root->data << "(" << name << ")" << endl;

        PrettyDfs(root->left, depth + 1, "L");
        PrettyDfs(root->right, depth + 1, "R");
    }
}

/*
Output:
Printing bst created using recursion
-->3(root)
   |-->1(L)
   |   |-->2(R)
   |-->5(R)
   |   |-->4(L)

Printing tree after deleting key 4
-->3(root)
   |-->1(L)
   |   |-->2(R)
   |-->5(R)

Printing tree after deleting key 1
-->3(root)
   |-->2(L)
   |-->5(R)

Printing tree after deleting key 3
-->5(root)
   |-->2(L)

*/
