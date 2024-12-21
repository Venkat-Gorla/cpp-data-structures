
//----------------------------------------
// - Question: Given a matrix and start and ending positions, help a robot navigate through the matrix and print all possible paths.
// The matrix might have obstacles in which case the current path must be abandoned and a new path (if available) must be searched.
// At every cell of the matrix, the robot can move down one step or move right one step or move diagonally down right one step

#include <iostream>
#include <vector>
#include <iterator> // ostream_iterator
using namespace std;

// macro to define limits for the input matrix
#define MAX_X 4
#define MAX_Y 9

// coordinates of the robot destination cell
#define END_X 3
#define END_Y 8

struct Point
{
    int x;
    int y;
};

bool isValid(int current_x, int current_y)
{
    return current_x >= 0 && current_x < MAX_X && current_y >= 0 && current_y < MAX_Y;
}

ostream& operator<<(ostream& output, const Point& p)
{
    output << "(" << p.x << "," << p.y << ")";
    return output;
}

void printCurrentPath(const vector<Point>& currentPath)
{
    copy(currentPath.begin(), currentPath.end(), ostream_iterator<Point>(cout, " "));
    cout << endl;
}

Point neighbors[]{{1, 1}, {1, 0}, {0, 1}};

// recursive helper function that implements backtracking
void printPathsHelper(
    int M[MAX_X][MAX_Y],
    int current_x,
    int current_y,
    vector<Point> & currentPath)
{
    if (!(isValid(current_x, current_y) && M[current_x][current_y] == 0))
    {
        return;
    }

    currentPath.push_back(Point{current_x, current_y});

    if (current_x == END_X && current_y == END_Y)
    {
        printCurrentPath(currentPath);
    }
    else
    {
        M[current_x][current_y] = 1;
        for (auto neighbor : neighbors)
        {
            int next_x = current_x + neighbor.x;
            int next_y = current_y + neighbor.y;
            printPathsHelper(M, next_x, next_y, currentPath);
        }
        M[current_x][current_y] = 0;
    }

    currentPath.pop_back();
}

// driver function for the solution
void printPaths(
    int M[MAX_X][MAX_Y],
    int start_x, 
    int start_y)
{
    vector<Point> currentPath;
    printPathsHelper(M, start_x, start_y, currentPath);
}

int main(int argc, char *argv[])
{
    int start_x = 0, start_y = 0;
    int M[MAX_X][MAX_Y]=
    {
        // 0 means the position/ path is available for exploring.
        // 1 means it is a wall/ obstacle and we cannot proceed further.
        {0,0,0,1,1,1,0,0,0},
        {1,1,0,0,0,0,0,0,0},
        {1,0,1,0,0,1,0,1,0},
        {0,0,1,1,0,1,1,1,0}
    };

    printPaths(M, start_x, start_y);

    return 0;
}

/*
Output:
(0,0) (0,1) (1,2) (1,3) (1,4) (1,5) (1,6) (1,7) (2,8) (3,8)
(0,0) (0,1) (1,2) (1,3) (1,4) (1,5) (1,6) (1,7) (1,8) (2,8) (3,8)
(0,0) (0,1) (0,2) (1,3) (1,4) (1,5) (1,6) (1,7) (2,8) (3,8)
(0,0) (0,1) (0,2) (1,3) (1,4) (1,5) (1,6) (1,7) (1,8) (2,8) (3,8)
(0,0) (0,1) (0,2) (1,2) (1,3) (1,4) (1,5) (1,6) (1,7) (2,8) (3,8)
(0,0) (0,1) (0,2) (1,2) (1,3) (1,4) (1,5) (1,6) (1,7) (1,8) (2,8) (3,8)

*/

