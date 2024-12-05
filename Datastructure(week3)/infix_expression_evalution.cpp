#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

// Function to define the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to apply an operator to two operands
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

// Function to evaluate an infix expression
int evaluateInfix(string expression) {
    stack<int> values; // Stack for values
    stack<char> ops;   // Stack for operators

    for (int i = 0; i < expression.length(); i++) {
        // Skip spaces
        if (expression[i] == ' ') continue;

        // If the current character is a number, push it to the values stack
        if (isdigit(expression[i])) {
            int val = 0;
            // There might be more than one digit in a number
            while (i < expression.length() && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            values.push(val);
            i--;  // To ensure we process the current operator after the number
        }
        // If the current character is an opening parenthesis, push it to the operator stack
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        // If the current character is a closing parenthesis, solve the entire expression inside the parentheses
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.pop(); // Pop the '('
        }
        // If the current character is an operator
        else {
            // While the top of the operator stack has the same or greater precedence, apply the operator
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]);
        }
    }

    // Apply remaining operators to remaining values
    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    // The final result is the top of the values stack
    return values.top();
}

int main() {
    string expression;
    cout << "Enter infix expression: ";
    getline(cin, expression);
    
    cout << "Result: " << evaluateInfix(expression) << endl;

    return 0;
}
