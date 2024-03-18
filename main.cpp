#include <iostream>
#include <string>
#include "ArrayStack.h" // Make sure this path is correct

// Function prototype
int evaluatePrefixExpression(const std::string& expression);

int main() {
    std::string expression;
    std::cout << "Enter a valid prefix expression or type 'exit' to quit: ";

    while (std::getline(std::cin, expression) && expression != "exit") {
        try {
            int result = evaluatePrefixExpression(expression);
            std::cout << "Result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error evaluating expression: " << e.what() << std::endl;
        }
        std::cout << "\nEnter a valid prefix expression or type 'exit' to quit: ";
    }

    return 0;
}

int evaluatePrefixExpression(const std::string& expression) {
    ArrayStack<int> stack;
    // Iterate from the end of the string
    for (int i = expression.length() - 1; i >= 0; i--) {
        // Skip spaces
        if (expression[i] == ' ') continue;

        // If the character is an operand (digit), push it to the stack
        if (isdigit(expression[i])) {
            stack.push(expression[i] - '0'); // Convert char to int and push
        } else {
            // The character is an operator, pop two operands
            int op1 = stack.peek(); stack.pop();
            int op2 = stack.peek(); stack.pop();

            // Perform the operation and push the result back
            switch (expression[i]) {
                case '+': stack.push(op1 + op2); break;
                case '-': stack.push(op1 - op2); break;
                case '*': stack.push(op1 * op2); break;
                case '/': stack.push(op1 / op2); break;
                default: throw std::runtime_error("Invalid operator");
            }
        }
    }
    // The final result should be at the top of the stack
    return stack.peek();
}
