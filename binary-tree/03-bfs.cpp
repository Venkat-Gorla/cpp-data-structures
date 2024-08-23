
//----------------------------------------
// Breadth first search traversal
// BFS is also referred to as level order traversal
// can assume root of the tree is at level 0

#include <iostream>
#include <queue>
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

void bfs(Node* root)
{
    if (!root)
        return;

    queue<Node*> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty())
    {
        auto current = nodeQueue.front();
        nodeQueue.pop();
        cout << current->data << " ";

        if (current->left)
            nodeQueue.push(current->left);

        if (current->right)
            nodeQueue.push(current->right);
    }

    cout << endl;
}

int main(int argc, char *argv[])
{ 
    {
        Node* root = Create(1);
        root->left = Create(2);
        root->right = Create(3);
        root->left->right = Create(4);

        bfs(root);
    }

    return 0;
}

/*
Expected output:
1 2 3 4

Actual output:
1 2 3 4

*/
