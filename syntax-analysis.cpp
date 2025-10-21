#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Node structure for parse tree
struct ParseNode {
    string symbol;
    vector<ParseNode*> children;

    ParseNode(string s) : symbol(s) {}
};

// Input string and pointer
string input = "ab";
int inputPointer = 0;

// Function to match terminal symbols
bool match(char expected) {
    if (inputPointer < input.size() && input[inputPointer] == expected) {
        inputPointer++;
        return true;
    }
    return false;
}

// Recursive function for non-terminal A → b
ParseNode* parseA() {
    ParseNode* node = new ParseNode("A");
    if (match('b')) {
        node->children.push_back(new ParseNode("b"));
        return node;
    } else {
        cout << "Syntax Error at A\n";
        return nullptr;
    }
}

// Recursive function for non-terminal S → aA
ParseNode* parseS() {
    ParseNode* node = new ParseNode("S");
    if (match('a')) {
        node->children.push_back(new ParseNode("a"));
        ParseNode* aNode = parseA();
        if (aNode) {
            node->children.push_back(aNode);
            return node;
        }
    }
    cout << "Syntax Error at S\n";
    return nullptr;
}

// Function to print the parse tree (preorder)
void printTree(ParseNode* node, int depth = 0) {
    if (!node) return;
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << node->symbol << "\n";
    for (ParseNode* child : node->children) {
        printTree(child, depth + 1);
    }
}

int main() {
    // Step 1: Create one-node tree with S
    ParseNode* treeRoot = parseS();

    // Step 2: Print the parse tree
    if (treeRoot && inputPointer == input.size()) {
        cout << "Parse successful!\n";
        printTree(treeRoot);
    } else {
        cout << "Parsing failed.\n";
    }

    return 0;
}
