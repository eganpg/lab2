// Program description
// This file contains a main function that takes an input from the user based on a prompt
// The user can enter a prompt or type 'exit' to quit. If the user types exit, the program aborts otherwise it continues
// Upon entering an input, the input is passed to the 'evaluatePrefixExpress' function
// In the 'evaluatePrefixExpress' function, the passed expression is looped over, taking consideration to remove spaces
// The function then performs the stack operations utilizing the provided stock code in ArraySTack.cpp ArraySTack.h and StackInterfaceh
// The function checks to determine if each operator or number is valid. The function does not support letters and will throw an error.
// On completion the main function displays results or errors.


#include <iostream>
#include <string>
#include "ArrayStack.h" 

// Function prototype
int evaluatePrefixExpression(const std::string& expression);

// main function
int main() {
    // define string expression
    std::string expression;
    // intial input prompt; this accepts operators and numbers
    std::cout << "Enter a valid prefix expression or type 'exit' to quit: ";
    // take the input as long as it is not exit
    while (std::getline(std::cin, expression) && expression != "exit") {
        // send input to the eval function
        try {
            int result = evaluatePrefixExpression(expression);
            // display results
            std::cout << "Result: " << result << std::endl;
        } catch (const std::exception& e) { // display error when there is an error
            std::cout << "Error evaluating expression: " << e.what() << std::endl;
        }

        // take another input
        std::cout << "\nEnter a valid prefix expression or type 'exit' to quit: ";
    }

    return 0;
}

// stack evaluation function
int evaluatePrefixExpression(const std::string& expression) {
    ArrayStack<int> stack;
    // Iterate from the end of the string
    for (int i = expression.length() - 1; i >= 0; i--) {
        // display the stack for debugging
        
        // Skip spaces
        if (expression[i] == ' ') continue;

        // If the character is an operand (digit), push it to the stack
        if (isdigit(expression[i])) {
            stack.push(expression[i] - '0'); // Convert char to int and push
        } else {
            // The character is an operator, pop two operands
            int op1 = stack.peek(); stack.pop();
            // std::cout << op1 << '\n'; // for debugging
            int op2 = stack.peek(); stack.pop();
            // std::cout << op2 << '\n'; // for debugging

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
