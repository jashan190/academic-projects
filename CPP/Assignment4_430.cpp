#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class Stack {
private:
    vector<char> stackVector; // Use vector to store characters

public:
    Stack() {
        stackVector.reserve(255); // Reserve space for 255 characters
    }

    void clear() {
        stackVector.clear();
    }

    bool isEmpty() const {
        return stackVector.empty();
    }

    void push(char c) {
        if (stackVector.size() < stackVector.capacity()) {
            stackVector.push_back(c);
        } else {
            throw out_of_range("Stack Overflow");
        }
    }

    char pop() {
        if (!isEmpty()) {
            char c = stackVector.back();
            stackVector.pop_back();
            return c;
        } else {
            throw out_of_range("Stack Underflow");
        }
    }

    // This function will be used to check for balanced brackets
    bool isBalanced(const string& exp) {
        clear(); // Clear any previous contents in the stack
        for (char c : exp) {
            if (c == '(' || c == '{' || c == '[') {
                push(c);
            } else if (c == ')' || c == '}' || c == ']') {
                if (isEmpty()) return false;
                char topChar = pop();
                if ((c == ')' && topChar != '(') ||
                    (c == '}' && topChar != '{') ||
                    (c == ']' && topChar != '[')) {
                    return false;
                }
            }
        }
        return isEmpty(); // If stack is empty, all brackets were balanced
    }
};

int main() {
    Stack stack;
    string expression;
    cout << "Enter an expression to check (brackets): ";
    getline(cin, expression); // Use getline to allow spaces and multiple characters

    try {
        cout << (stack.isBalanced(expression) ? "true" : "false") << endl;
    } catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

