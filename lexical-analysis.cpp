#include <iostream>
#include <vector>
#include <string>
#include <cctype> // For isalpha
#include <set>    // For a list of keywords

using namespace std;

vector<string> keywords;
vector<string> variables;

// Create a set for fast keyword lookup
const set<string> KEYWORDS = {"int", "char", "float", "double"};

void tokenize(const string& statement);
void displayTokens();

int main() {
    string statement;
    cout << "enter a variable declaration (eg. int a; or char a,b,c;): ";
    getline(cin, statement);

    tokenize(statement);
    displayTokens();

    return 0;
}

void tokenize(const string& statement) {
    string currentToken;

    for (char c : statement) {
        // Build the token from characters
        if (isalpha(c)) {
            currentToken += c;
        } 
        // A delimiter was found, so the token is complete
        else {
            if (!currentToken.empty()) {
                // Check if the token is a keyword or a variable
                if (KEYWORDS.count(currentToken)) {
                    keywords.push_back(currentToken);
                } else {
                    variables.push_back(currentToken);
                }
                currentToken.clear(); // Reset for the next token
            }

            // Handle non-alphabetic characters (delimiters)
            if (c == ';') {
                // End of statement
                break;
            }
            // You can add more logic here for other symbols if needed
        }
    }
}

void displayTokens() {
    cout << "Keywords: ";
    for (const string& kw : keywords) {
        cout << kw << " ";
    }
    cout << endl;

    cout << "Variables: ";
    for (const string& var : variables) {
        cout << var << " ";
    }
    cout << endl;
}