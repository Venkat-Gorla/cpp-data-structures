
// Solutions for some commonly asked backtracking questions

//----------------------------------------
// - Given a number and an unlimited amount of coin change denominations, print all possible ways in which the input number can be broken down.
// For example: given 2, you should print (1, 1), (2)
// Given 3, print (1, 1, 1), (1, 2), (3)
// Assumptions/ constraints: assume only whole numbers (no fractions), assume only positive numbers (greater than 0), coin denominations in increments of 1.

#include <iostream>
#include <vector>
#include <iterator> // ostream_iterator
using namespace std;

// fwd declarations
void testcase(const int sum);
// end fwd declarations

void printBuffer(const vector<int> & buffer)
{
    std::copy(buffer.begin(), buffer.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

// solution function
void printCoinCombinations(
    const int sum, // program input
    const int currentDenomination,
    vector<int> & buffer)
{
    if (sum == 0 || currentDenomination > sum)
    {
        if (sum == 0)
        {
            printBuffer(buffer);
        }

        return;
    }

    // for every coin denomination, you have two possibilities, either consider it or not
    buffer.push_back(currentDenomination);
    printCoinCombinations(sum - currentDenomination, currentDenomination, buffer);
    buffer.pop_back();

    printCoinCombinations(sum, currentDenomination + 1, buffer);
}

int main(int argc, char *argv[])
{
    {
        testcase(3);
    }

    {
        testcase(4);
    }

    {
        testcase(5);
    }

    return 0;
}

void testcase(const int sum)
{
    cout << "Input sum: " << sum << endl;
    vector<int> buffer;
    printCoinCombinations(sum, 1, buffer);
    cout << endl;
}

/*
Output:
Input sum: 3
1 1 1
1 2
3

Input sum: 4
1 1 1 1
1 1 2
1 3
2 2
4

Input sum: 5
1 1 1 1 1
1 1 1 2
1 1 3
1 2 2
1 4
2 3
5

*/

//----------------------------------------

