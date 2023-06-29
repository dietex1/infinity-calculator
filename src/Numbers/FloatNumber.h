#pragma once


#include <stdexcept>
#include <cmath>
#include <ios>
#include <sstream>
#include <iomanip>
#include <map>
#include "Number.h"
#include "FloatNumber.h"
#include "IntegerNumber.h"



/**
 * @brief Represents a floating point number.
 * Derived from Number.
 */

class FloatNumber : public Number {
private:
    IntegerNumber integerPart; ///< Integer part of the float number.
    std::vector<int> fractionalPart; ///< Fractional part of the float number.
    bool sign =  integerPart.getSign()  ; ///< Sign of the float number.

public:
    /**
    * @brief Sets the sign of the floating point number.
    * @param signs The boolean value to set the sign (true for negative, false for positive).
    */
    void setSign(bool signs) override { integerPart.setSign(signs); }
    /**
     * @brief Gets the sign of the floating point number.
     * @return The boolean value of the sign (true for negative, false for positive).
     */
    bool getSign() const override{ return sign; }
    /**
     * @brief Constructs a FloatNumber from a string.
     * @param number String representation of the floating point number to convert.
     */
    FloatNumber(const std::string &number);
    /**
     * @brief Constructs a FloatNumber from two vectors of integers.
     * @param integerDigits Vector of integers to construct the integer part of the floating point number.
     * @param fractionalDigits Vector of integers to construct the fractional part of the floating point number.
     */
    FloatNumber(const std::vector<int>& integerDigits, const std::vector<int>& fractionalDigits )
            : integerPart(integerDigits), fractionalPart(fractionalDigits), sign(integerPart.getSign()) {}
    /**
     * @brief Converts the floating point number to a string.
     * @return String representation of the floating point number.
     */
    std::string toString() const override;
    /**
    * @brief Overridden addition operator for floating point numbers.
    * @param other Other number to add.
    * @return Result of the addition operation as a shared_ptr to a Number.
    */
    std::shared_ptr<Number> operator+(const Number &other) const override;
    /**
    * @brief Overridden multiplication operator for floating point numbers.
    * @param other Other number to multiply with.
    * @return Result of the multiplication operation as a shared_ptr to a Number.
    */
    std::shared_ptr<Number> operator*(const Number &other)const override;
    /**
    * @brief Overridden exponentiation operator for floating point numbers.
    * @param other Other number to raise the current number to.
    * @return Result of the exponentiation operation as a shared_ptr to a Number.
    */
    std::shared_ptr<Number> operator^(const Number &other) const override;
    /**
    * @brief Overridden subtraction operator for floating point numbers.
    * @param other Other number to subtract from the current number.
    * @return Result of the subtraction operation as a shared_ptr to a Number.
    */
    std::shared_ptr<Number> operator-(const Number &other) const override;
    /**
     * @brief Overridden factorial operator for floating point numbers. Throws an error because factorials for float numbers are undefined.
     * @throws logic_error for factorial of a floating point number.
     * @return A error, as factorial is not defined for float numbers.
     */
    std::shared_ptr<Number> operator!() const override;
    /**
     * @brief Overridden rounding operator for floating point numbers.
     * @return Rounded floating point number as a shared_ptr to a Number.
     */
    std::shared_ptr<Number> operator~() const override;
    /**
     * @brief Overridden modulo operator for floating point numbers. Throws an error because modulo for float numbers is undefined.
     * @param other The divisor.
     * @throws logic_error for modulo of a floating point number.
     * @return A error, as modulo is not defined for float numbers.
     */
    std::shared_ptr<Number> operator%(const Number &other)const override;
    /**
     * @brief Overridden division operator for floating point numbers.
     * @param other The divisor.
     * @throws error for division by zero.
     * @return Result of the division operation as a shared_ptr to a Number.
     */
    std::shared_ptr<Number> operator/(const Number &other) const override;
    /**
    * @brief Creates a copy of the floating point number.
    * @return A shared_ptr to a copy of the floating point number.
    */
    std::shared_ptr<Number> clone() const override ;

    /**
    * @brief Accesses the fractional part of the floating point number.
    * @return A const reference to the vector of integers representing the fractional part.
    */
    const std::vector<int>& getFractionalDigits() const override { return fractionalPart; }
    /**
    * @brief Accesses the integer part of the floating point number.
    * @return A const reference to the vector of integers representing the integer part.
    */
    const std::vector<int>& getIntegerPartFloat() const override { return integerPart.getIntegerDigits(); }
    /**
    * @brief Accesses the integer part of the floating point number.
    * @return A const reference to the vector of integers representing the integer part.
    */
    const std::vector<int>& getIntegerDigits() const override { return integerPart.getIntegerDigits(); }
    /**
        * @brief Negates the floating point number.
        * @return A shared_ptr to the negated number.
     */
    std::shared_ptr<Number> negateNumber() const override;

    std::shared_ptr<Number> toExponent() const override;

    std::shared_ptr<Number> fromExponent() const override;
};



