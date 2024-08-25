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

//----------------------------------------
// get the height of a binary tree (length of longest root to leaf path)
// height of empty tree is 0

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

// recursive solution
// next we will solve this problem using a modified version of bfs i.e. without recursion
int getHeight(Node* root)
{
    if (!root)
        return 0;

    return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

int getHeight_bfs(Node* root)
{
    // when processing the bfs queue, the idea is to process one level of nodes at a time;
    // the same technique can be used to print all nodes at a level before processing the next level

    if (!root)
        return 0;

    queue<Node*> nodeQueue;
    nodeQueue.push(root);

    int height{0};
    while (!nodeQueue.empty())
    {
        for (int numNodes = nodeQueue.size(); numNodes > 0; numNodes--)
        {
            auto current = nodeQueue.front();
            nodeQueue.pop();

            if (current->left)
                nodeQueue.push(current->left);

            if (current->right)
                nodeQueue.push(current->right);
        }

        // the for loop will process one level of nodes, so this is where we increment the height
        height++;
    }

    return height;
}

void testcase(Node* root)
{
    cout << "Height of the binary tree using recursion is " << getHeight(root) << endl;
    cout << "Height of the binary tree using bfs is " << getHeight_bfs(root) << endl;
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

        testcase(root);
    }

    return 0;
}

/*
Expected output:

Actual output:
Height of the binary tree using recursion is 3
Height of the binary tree using bfs is 3

*/
