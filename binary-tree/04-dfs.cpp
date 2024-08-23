//----------------------------------------
// depth first traversal (dfs) of binary tree
// for a binary tree, dfs is the same as preorder traversal
// to illustrate this idea, we will get the connecting path from the root to a key in the binary tree

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

// the input key may or may not be present in the tree
bool dfs(Node* root, const int K, vector<Node*> & path)
{
    if (!root)
        return false;

    path.push_back(root);

    if (root->data == K || dfs(root->left, K, path) || dfs(root->right, K, path))
    {
        return true;
    }
    else
    {
        path.pop_back();
        return false;
    }
}

// utility function to print connecting path
void print(const vector<Node*> & buffer)
{
    for (const auto current : buffer)
    {
        cout << current->data << " ";
    }
    cout << endl;
}

void testcase(Node* root, const int K)
{
    vector<Node*> path;
    if (dfs(root, K, path))
    {
        cout << "Connecting path for key " << K << " is ";
        print(path);
    }
    else
    {
        cout << "Key " << K << " is not found" << endl;
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
        Node* root = Create(1);
        root->left = Create(2);
        root->right = Create(3);
        root->left->right = Create(4);
        root->right->left = Create(5);

        testcase(root, 4);
        testcase(root, 5);
        testcase(root, 6);
    }

    return 0;
}

/*
Output:
Connecting path for key 4 is 1 2 4
Connecting path for key 5 is 1 3 5
Key 6 is not found

*/
