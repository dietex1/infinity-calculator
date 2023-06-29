#pragma once
#include "ImportExport.h"


#include "../Numbers/Number.h"

#include <string>
#include <queue>

#include <iostream>
#include <fstream>


/**
 * @brief The Calculator class performs parsing,logic of program and import/export of variables.
 */
class Calculator {
public:
    /**
     * @brief  Constructs a new Calculator object.
     */
    Calculator();
/**
     * @brief Executes a command, which can involve arithmetic operations or variable assignments.
     * @param command The command to execute as a string.
     */
    void executeCommand(const std::string &command) ;
    /**
        * @brief Retrieves the map of variables currently stored in the calculator.
        * @return A constant reference to the map of variables.
        */
    const std::map<std::string, std::shared_ptr<Number>>& getVariables() const;
    ImportExport  ImpCalc;
private:
    /**
     * @brief Stores the variables used in the calculator operations. Each variable is a shared pointer to a Number object.
     */
    std::map<std::string, std::shared_ptr<Number>> variables;
    /**
    * @brief Converts an infix mathematical expression to a postfix expression using the Shunting Yard algorithm.
    * @param exp The infix expression to convert.
    * @return The postfix expression as a queue of strings.
    */
    std::queue<std::string> shuntingYard(const std::string &exp);
    /**
    * @brief Calculates the result of a postfix mathematical expression.
    * @param RPN The postfix expression to calculate.
    * @return The result of the calculation as a shared pointer to a Number object.
    */
    std::shared_ptr<Number> calculateRPN(std::queue<std::string> &RPN);
    /**
     * @brief Splits a mathematical expression into a list of tokens.
     * @param exp The expression to split.
     * @return A vector of tokens as strings.
     */
    std::vector<std::string> splitExpression(const std::string &exp);
    /**
    * @brief Checks if a token is a valid number or variable.
    * @param token The token to check.
    */
    void checkToken(const std::string &token) ;
};

