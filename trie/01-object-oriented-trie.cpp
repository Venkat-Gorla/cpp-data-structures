//----------------------------------------
// - Object oriented Trie for word lookup: insert, delete, search and autocomplete suggestions
// - use of unique_ptr for auto memory management of the Trie structure

#include <iostream>
#include <memory> // unique_ptr
#include <unordered_map>
#include <vector>
#include <string>
#include <cstring> // strlen
#include <iterator> // ostream_iterator
using namespace std;

class Trie
{
  private:
    struct Node
    {
        bool isFinal{false};
        unordered_map<char, unique_ptr<Node>> table;
    };

    unique_ptr<Node> m_root;

  public:
    Trie()
      : m_root(make_unique<Node>())
    {
    }

  public:
    // to keep things simple, we will assume all input is given in lowercase;
    // we can of course do input normalization inside our class

    // input is assumed to be 0 terminated
    void insertWord(const char* input);
    bool searchWord(const char* input) const;
    vector<string> getSuggestions(const char* prefix) const;
    void deleteWord(const char* input);

  private:
    Node* findFinalNodeForWord(const char* input) const;
    void getSuggestions(Node* current, vector<char> & buffer, vector<string> & output) const;
    bool deleteWord(Node* current, const char* input);
};

void Trie::insertWord(const char* input)
{
    Node* current = m_root.get();
    for (int index = 0; input[index] != 0; ++index)
    {
        const char letter{input[index]};
        if (!current->table[letter])
            current->table[letter] = make_unique<Node>();

        current = current->table[letter].get();
    }

    current->isFinal = true; // this is how you recognize a valid word in the Trie
}

bool Trie::searchWord(const char* input) const
{
    Node* finalNode = findFinalNodeForWord(input);
    return finalNode ? finalNode->isFinal : false;
}

vector<string> Trie::getSuggestions(const char* prefix) const
{
    Node* finalNode = findFinalNodeForWord(prefix);
    if (!finalNode)
        return vector<string>{};

    vector<char> buffer(prefix, prefix + strlen(prefix));
    vector<string> output;
    getSuggestions(finalNode, buffer, output);

    return output;
}

void Trie::deleteWord(const char* input)
{
    deleteWord(m_root.get(), input);
}

Trie::Node* Trie::findFinalNodeForWord(const char* input) const
{
    Node* current = m_root.get();
    for (int index = 0; input[index] != 0; ++index)
    {
        const char letter{input[index]};
        auto it = current->table.find(letter);
        if (it == current->table.end())
            return nullptr;

        current = it->second.get();
    }

    return current;
}

void Trie::getSuggestions(
    Node* current, // cannot be null
    vector<char> & buffer,
    vector<string> & output) const
{
    if (current->isFinal)
    {
        string temp(buffer.begin(), buffer.end());
        output.push_back(std::move(temp));
    }

    for (auto & kvp : current->table)
    {
        buffer.push_back(kvp.first);
        getSuggestions(kvp.second.get(), buffer, output);
        buffer.pop_back();
    }
}

bool Trie::deleteWord(Node* current, const char* input)
{
    if (*input == 0)
    {
        current->isFinal = false;
        return current->table.empty();
    }

    auto it = current->table.find(*input);
    if (it == current->table.end())
    {
        // this means the input word is not found, the Trie remains unchanged in that case
        return false;
    }

    const bool canDelete = deleteWord(it->second.get(), input + 1);
    if (canDelete)
    {
        current->table.erase(it);
        return current->table.empty();
    }

    return false;
}
// end Trie implementation

// fwd declarations
void testSearch(const Trie & t, const vector<string> & searchInput);
void testGetSuggestions(const Trie & t, const vector<string> & searchInput);
void testDeletion(
    Trie & t, 
    const vector<string> & deleteInput, 
    const vector<string> & searchInput);
// end fwd declarations

int main(int argc, char *argv[])
{
    const vector<string> input{
        "the", "there", "answer", "any",
        "bye", "their"};

    Trie t;
    for (const auto & key : input)
    {
        t.insertWord(key.c_str());
    }

    {
        const vector<string> searchInput{"the", "there", "answer", "by"};
        testSearch(t, searchInput);
    }

    {
        cout << endl;
        const vector<string> searchInput{"the", "an"};
        testGetSuggestions(t, searchInput);
    }

    {
        cout << endl;
        const vector<string> deleteInput{"the", "any", "bye"};
        const vector<string> searchInput{"the", "an", "bye"};
        testDeletion(t, deleteInput, searchInput);
    }

    return 0;
}

void testSearch(const Trie & t, const vector<string> & searchInput)
{
    cout << "Test case for search words" << endl;

    for (const auto & word : searchInput)
    {
        const bool found{t.searchWord(word.c_str())};

        if (found)
            cout << word << " --- present in Trie" << endl;
        else
            cout << word << " --- *Not* present in Trie" << endl;
    }
}

void testGetSuggestions(const Trie & t, const vector<string> & searchInput)
{
    cout << "Test case for get suggestions" << endl;
    for (const auto & word : searchInput)
    {
        vector<string> output(t.getSuggestions(word.c_str()));

        cout << "Suggestions for prefix \"" << word << "\" --> ";
        std::copy(output.begin(), output.end(), ostream_iterator<string>(cout, " "));
        cout << endl;
    }
}

void testDeletion(
    Trie & t, 
    const vector<string> & deleteInput, 
    const vector<string> & searchInput)
{
    for (const auto & word : deleteInput)
    {
        cout << "Deleting \"" << word << "\" from Trie" << endl;
        t.deleteWord(word.c_str());
    }

    cout << endl << "Printing suggestions after deletion" << endl;
    testGetSuggestions(t, searchInput);
}

/*
Output:
Test case for search words
the --- present in Trie
there --- present in Trie
answer --- present in Trie
by --- *Not* present in Trie

Test case for get suggestions
Suggestions for prefix "the" --> the their there
Suggestions for prefix "an" --> any answer

Deleting "the" from Trie
Deleting "any" from Trie
Deleting "bye" from Trie

Printing suggestions after deletion
Test case for get suggestions
Suggestions for prefix "the" --> their there
Suggestions for prefix "an" --> answer
Suggestions for prefix "bye" -->

*/

