#include "Calculator.h"

using namespace std;

#include "stack"
#include "../Numbers/FloatNumber.h"
#include "../Numbers/IntegerNumber.h"
#include <iostream>

Calculator::Calculator() : ImpCalc(this) {}


const map<string, shared_ptr<Number>>& Calculator::getVariables() const {
    return variables;
}


queue<string> Calculator::shuntingYard(const string &exp) {
    // Two structures to hold operators and output
    stack<string> ops;
    queue<string> output;
    // Tokenizing the input expression for processing
    vector<string> tokens = splitExpression(exp);

    // Iterating over each token in the input
    for (const string &token : tokens) {
        // If token is an open bracket, it is pushed onto the operators stack
        if (token == "(") {
            ops.push(token);
        } else if (token == ")") {
            // If token is a closing bracket, all operators are popped from stack to queue until an opening bracket is found
            while (!ops.empty() && ops.top() != "(") {
                output.push(ops.top());
                ops.pop();
            }
            ops.pop(); // remove "("
        } else if (token == "+" || token == "-") {
            // If token is '+' or '-', operators are popped from stack to queue until the stack is empty or an opening bracket is found
            while (!ops.empty() && ops.top() != "(") {
                output.push(ops.top());
                ops.pop();
            }
            ops.push(token); // Push the current operator onto the stack
        } else if (token == "*" || token == "/" || token == "%") {
            // If token is '*' or '/' or '%', higher precedence operators are popped from stack to queue until the stack is empty or an operator with lower precedence is found
            while (!ops.empty() && (ops.top() == "*" || ops.top() == "/" || ops.top() == "%" ||
                                    ops.top() == "!" || ops.top() == "~" || ops.top() == "^")) {
                output.push(ops.top());
                ops.pop();
            }
            ops.push(token);
        } else if (token == "!" || token == "~" || token == "^") {
            // If token is '!', '~', or '^', similar precedence operators are popped from stack to queue until an operator with lower precedence is found
            while (!ops.empty() && (ops.top() == "!" || ops.top() == "~" || ops.top() == "^")) {
                output.push(ops.top());
                ops.pop();
            }
            ops.push(token);
        } else {
            // If token is a number, it is pushed onto the output queue
            output.push(token);
        }
    }
    // Pop any remaining operators from the stack to the queue
    while (!ops.empty()) {
        output.push(ops.top());
        ops.pop();
    }

    return output; // Returning the output in postfix form
}


void Calculator::executeCommand(const string &command) {
    if (command.empty()) {
        throw runtime_error("Input must not be empty");
    }
    // Check if command is for importing or exporting memory
    if (command.substr(0, 7) == "IMPORT ") { //index
        ImpCalc.importMemory(command.substr(7));
        return;
    } else if (command.substr(0, 7) == "EXPORT ") {
        ImpCalc.exportMemory(command.substr(7));
        return;
    }
    size_t equal_pos = command.find("=");
    if (equal_pos != string::npos) {
        // If the command is an assignment operation
        string var_name = command.substr(0, equal_pos - 1);
        string expression = command.substr(equal_pos + 2);

        // Replace variable in expression with its value
        for (auto& var : variables) {
            size_t pos = expression.find(var.first);
            while (pos != string::npos) {
                expression.replace(pos, var.first.size(), var.second->toString());
                pos = expression.find(var.first);
            }
        }
        // Calculate the result of the expression and store it in the variable
        queue<string> RPN = shuntingYard(expression);
        shared_ptr<Number> result = calculateRPN(RPN);
        variables[var_name] = result;
        cout << var_name << " = " << result->toString() << endl;
    } else {
        // Replace variable in command with its value
        // If the command is an expression to be evaluated
        string expression = command;
        for (auto& var : variables) {
            size_t pos = expression.find(var.first);
            while (pos != string::npos) {
                expression.replace(pos, var.first.size(), var.second->toString());
                pos = expression.find(var.first);
            }
        }
        // Calculate and print the result of the expression
        queue<string> RPN = shuntingYard(expression);
        shared_ptr<Number> result = calculateRPN(RPN);
        cout << "Result = " << result->toString() << endl;
    }
}

shared_ptr<Number> Calculator::calculateRPN(queue<string> &RPN) {
    stack<shared_ptr<Number>> stk;
    // Iterate over each token in the postfix expression
    while (!RPN.empty()) {
        string token = RPN.front();
        RPN.pop();
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^") {
            // If token is a binary operator, pop two numbers from the stack, perform the operation, and push the result back onto the stack
            if (stk.size() < 2) {
                // If there are less than two numbers on the stack, throw an error
                throw runtime_error("Invalid expression: not enough operands for binary operator");
            }
            shared_ptr<Number> num2 = stk.top();
            stk.pop();
            shared_ptr<Number> num1 = stk.top();
            stk.pop();
            if (token == "+") stk.push(*num1 + *num2);
            else if (token == "-") stk.push(*num1 - *num2);
            else if (token == "*") stk.push(*num1 * *num2);
            else if (token == "/") stk.push(*num1 / *num2);
            else if (token == "%") stk.push(*num1 % *num2);
            else if (token == "^") stk.push(*num1 ^ *num2);
        } else if (token == "~" || token == "!") {
            // If token is a unary operator, pop a number from the stack, perform the operation, and push the result back onto the stack
            if (stk.empty()) {
                // If there are no numbers on the stack, throw an error
                throw runtime_error("Invalid expression: not enough operands for unary operator");
            }
            shared_ptr<Number> num = stk.top(); stk.pop();
            if (token == "~") stk.push(~(*num));
            else if (token == "!") stk.push(!(*num));
        } else {
            // If token is a number, push it onto the stack
            if (variables.find(token) != variables.end()) {
                stk.push(variables[token]);
            } else {
                if (token.find(".") != string::npos) {
                    stk.push(make_shared<FloatNumber>(token));
                } else {
                    stk.push(make_shared<IntegerNumber>(token));
                }
            }
        }
    }
    // the stack should have exactly one number on it, which is the result of the expression
    if (stk.size() != 1) {
        throw runtime_error("Invalid expression: too many operands");
    }
    return stk.top();
}


vector<string> Calculator::splitExpression(const string &exp) {
    vector<string> tokens;
    string token;
    bool mayBeUnary = true;
    // Iterate over each character in the expression
    for (char ch : exp) {
        if (ch == ' ') {
            // If the character is a space, add the current token to the list and check a new token
            if (!token.empty()) {
                checkToken(token);
                tokens.push_back(token);
                token.clear();
            }
            // A unary operator can have a space
            mayBeUnary = true;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
                   ch == '%' || ch == '!' || ch == '~' || ch == '^' ||
                   ch == '(' || ch == ')') {
            // If the character is an operator or parentheses, add the current token and the operator to the list, and start a new token
            if (!token.empty()) {
                checkToken(token);
                tokens.push_back(token);
                token.clear();
            }
            // Special case for unary minus ,  if the character is a minus sign and it can be a unary operator, add it to the current token
            if ((ch == '-' && mayBeUnary) || (ch == '-' && !token.empty() && token.back() == '-')) {
                token += ch;
            } else {
                tokens.push_back(string(1, ch));
            }
            // A unary operator can follow an operator or open parenthesis
            mayBeUnary = (ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^');
        } else {
            // If the character is a number or variable, add it to the current token
            token += ch;
            // A unary operator cannot follow a number or variable
            mayBeUnary = false;
        }
    }
    // Add the last token to the list
    if (!token.empty()) {
        checkToken(token);
        tokens.push_back(token);
    }

    return tokens;
}






void Calculator::checkToken(const string &token) {
    bool hasDecimalPoint = false;
    // Iterate over each character in the token
    for (std::size_t i = 0; i < token.size(); i++) {
        char ch = token[i];
        if (!isdigit(ch)) {
            // If the character is not a digit, it must be a decimal point or the token must be a variable
            if (i == 0 && ch == '-') {
                // Allow '-' at the start of the string
                continue;
            }
            if (ch == '.' && !hasDecimalPoint) {
                // Allow one decimal point in the string
                hasDecimalPoint = true;
            } else if (variables.find(token) == variables.end()) {
                // If the token is not a valid variable
                throw runtime_error("Invalid input: '" + token + "' is not a valid number or variable");
            }
        }
    }
}




