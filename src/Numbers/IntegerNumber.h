#pragma once


#include "Number.h"
#include "IntegerNumber.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <memory>



/**
 * @brief Represents a integer number.
 * Derived from Number.
 */
class IntegerNumber : public Number {
private:
    std::vector<int> digits; ///< Digits of the integer number
    bool sign; ///< Sign of the integer number (true for negative, false for positive)
    unsigned long long tenExponent;

public:
    /**
     * @brief Construct an IntegerNumber from a string
     * @param number String to convert to IntegerNumber
     */
    explicit IntegerNumber(const std::string &number);
    /**
     * @brief Construct an IntegerNumber from a vector of integers
     * @param digits Vector of digits to construct the IntegerNumber
     */
    explicit IntegerNumber(const std::vector<int> &digits);
    /**
    * @brief Overridden addition operator for integer numbers.
     * @param other Other number to add
     * @return Result of the addition operation as a shared_ptr to a Number
     */
    std::shared_ptr<Number> operator+(const Number &other) const override;
    /**
     * @brief Overridden arithmetic operation subtraction for integer numbers
     * @param other Other number to subtract
     * @return Result of the  operation as a shared_ptr to a Number
     */
    std::shared_ptr<Number> operator-(const Number &other) const override;
    /**
     * @brief Overridden arithmetic operation multiplication for integer numbers
     * @param other Other number to multiply
     * @return Result of the  operation as a shared_ptr to a Number
     */
    std::shared_ptr<Number> operator*(const Number &other)const override;
    /**
     * @brief Overridden arithmetic operation factorial for integer numbers
     * @return Result of the  operation as a shared_ptr to a Number
     */
    std::shared_ptr<Number> operator!() const override;
    /**
     * @brief Overridden arithmetic operation round for integer numbers
     * @return Result of the  operation as a same shared_ptr to a Number
     */
    std::shared_ptr<Number> operator~() const override;
    /**
     * @brief Overridden modulo operator for integer numbers.
     * @param other The divisor.
     * @throws logic_error for modulo .
     * @return Result of the  operation as a same shared_ptr to a Number
     */
    std::shared_ptr<Number> operator%(const Number &other)const override;
    /**
    * @brief Overridden exponentiation operator for integer number.
    * @param other Other number to raise the current number to.
    * @return Result of the exponentiation operation as a shared_ptr to a Number.
    */
    std::shared_ptr<Number> operator^(const Number &other) const override;
    /**
     * @brief Overridden division operator for integer numbers.
     * @param other The divisor.
     * @throws error for division by zero.
     * @return Result of the division operation as a shared_ptr to a Number.
     */
    std::shared_ptr<Number> operator/(const Number &other) const override;
    /**
    * @brief Pure virtual function for creating a copy of the current object
    * @return Copy of the current object
    */
    std::shared_ptr<Number> clone() const override ;
    /**
    * @brief Pure virtual function for reverse the current number
     * @return Result of the  operation as a shared_ptr to a Number
    */
    std::shared_ptr<Number> negateNumber() const  override;
    /**
     * @brief Function to set sign of the number
     * @param signs Sign to be set (true for negative, false for positive)
     */
    void setSign(bool signs) override { this->sign = signs; }
    /**
    * @brief Function to get the sign of the number
    * @return Sign of the number (true for negative, false for positive)
    */
    bool getSign() const override { return sign; }

    /**
     * @brief Function to convert the number to string
     * @return String representation of the number
     */
    std::string toString() const override;
    /**
       * @brief Function for accessing the  integer number
       * @return vector of  number
     */
    const std::vector<int>& getIntegerDigits() const override { return digits; }
    /**
       * @brief Function for accessing the fractional part of a float number
       * @return vector of  integer number
      */
    const std::vector<int>& getFractionalDigits() const override {
        static const std::vector<int> emptyVector;
        return emptyVector;
    }
    /**
       * @brief Function for accessing the integer part of a float number
       * @return empty vector of  number because of no fractional part
      */
    const std::vector<int>& getIntegerPartFloat() const override { return digits; } // Same as integer part.
    /**
     * @brief Subtract two numbers represented as vectors of integers.
     * @param largerNumb Vector of integers representing the larger number.
     * @param smallerNumb Vector of integers representing the smaller number.
     * @return Vector of integers representing the result of the subtraction.
     */
    std::vector<int> subtractIntegerDigits(const std::vector<int>& largerNumb, const std::vector<int>& smallerNumb) const ;
    /**
     * @brief Convert a vector of integers into an unsigned long long.
     * @param digits Vector of integers to convert.
     * @return The resulting unsigned long long number.
     */
    unsigned long long vectorToUnsignedLongLong(const std::vector<int>& digits) const ;
    /**
     * @brief Convert an unsigned long long into a vector of integers.
     * @param num Unsigned long long to convert.
     * @return The resulting vector of integers.
     */
    std::vector<int> unsignedLongLongToVector(unsigned long long num) const ;


    std::shared_ptr<Number> toExponent() const override;

    std::shared_ptr<Number> fromExponent() const override;
};



