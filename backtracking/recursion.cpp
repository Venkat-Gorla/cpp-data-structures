
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
// - Question: Lets say someone accidentally deleted all the whitespace from a sentence. Write a program to reconstruct the sentence from that stripped out string. Assume you have access to a dictionary function that returns if a given string is a valid word or not. 

// If multiple solutions are possible, any one valid solution should be given. If a sentence cannot be formed, print an error message.

#include <iostream>
#include <vector>
#include <string>
#include <iterator> // ostream_iterator
using namespace std;

// Note: this solution uses backtracking and brute force technique, we will
// consider how to better solve it using Trie
const char* WORD_TABLE[] {"this", "is", "a", "valid", "sentence", 
    "with", "sample", "backtrack", "which", "requires", "straightforward", "question", 
    "the", "here", "we", "go"};

bool isWord(const std::string& input)
{
    for (auto word : WORD_TABLE)
    {
        if (0 == input.compare(word))
        {
            return true;
        }
    }

    return false;
}

void printSolution(const vector<string> & solution)
{
    std::copy(solution.begin(), solution.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}

// solution function
bool getSentence(const char* input, vector<string> & solution)
{
    if (*input == 0)
    {
        return true;
    }

    // consider every possible word than can be formed with the current input
    // and try to make a sentence out of it
    for (int index = 0; input[index] != 0; index++)
    {
        string temp(input, input + index + 1);
        if (isWord(temp))
        {
            solution.push_back(std::move(temp));
            if (getSentence(input + index + 1, solution))
            {
                return true;
            }

            solution.pop_back();
        }
    }

    return false;
}

// fwd declarations
void testcase(const char* input);
// end fwd declarations

int main(int argc, char *argv[])
{
    const char* samples[] = {"straightforwardquestion", "herewego", "herere"};
    for (auto s : samples)
    {
        testcase(s);
        cout << endl;
    }

    return 0;
}

// "input" is 0 terminated
void testcase(const char* input)
{
    cout << "Input: \"" << input << "\"" << endl;
    vector<string> solution;
    if (getSentence(input, solution))
    {
        printSolution(solution);
    }
    else
    {
        cout << "No solution found" << endl;
    }
}

/*
Output:
Input: "straightforwardquestion"
straightforward question

Input: "herewego"
here we go

Input: "herere"
No solution found

*/

