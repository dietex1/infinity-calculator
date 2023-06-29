#pragma once


#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <cmath>


/**
 * @class Number
 * @brief Abstract base class for numbers.
 */
 class Number {
public:
    /**
    * @brief Virtual destructor.
    */
    virtual ~Number() = default;
     /**
         * @brief Pure virtual function for addition
         * @param other Other number to add
         * @return Result of the operation as a shared_ptr to a Number
      */
    virtual std::shared_ptr<Number> operator+(const Number &other) const = 0;
     /**
     * @brief Pure virtual function for subtraction
     * @param other Number to subtract
     * @return Result of the operation as a shared_ptr to a Number
     */
    virtual std::shared_ptr<Number> operator-(const Number &other) const = 0;
     /**
    * @brief Pure virtual function for multiply
    * @param other Number to multiply
    * @return Result of the operation as a shared_ptr to a Number
    */
    virtual std::shared_ptr<Number> operator*(const Number &other) const = 0;
     /**
      * @brief Pure virtual function for factorial
      * @return Result of the operation as a shared_ptr to a Number
      */
    virtual  std::shared_ptr<Number> operator!() const = 0;
    /**
    * @brief Pure virtual function for modulo
    * @param other Number to modulo
    * @return Result of the operation as a shared_ptr to a Number
    */
    virtual std::shared_ptr<Number> operator%(const Number &other) const = 0;
     /**
      * @brief Pure virtual function for round
      * @return Result of the operation as a shared_ptr to a Number
      */
    virtual  std::shared_ptr<Number> operator~() const = 0;
     /**
    * @brief Pure virtual function for ^ operation
    * @return Result of the operation as a shared_ptr to a Number
    */
    virtual std::shared_ptr<Number> operator^(const Number &other) const = 0;
     /**
    * @brief Pure virtual function for / operation
    * @param other Number to /
    * @return Result of the operation as a shared_ptr to a Number
    */
    virtual std::shared_ptr<Number> operator/(const Number &other) const = 0;
     /**
     * @brief Pure virtual function for creating a copy of the current object
     * @return Copy of the current object
     */
    virtual std::shared_ptr<Number> clone() const = 0;
     /**
     * @brief Function to convert the number to string
     * @return String representation of the number
     */
    virtual std::string toString() const = 0;
     /**
     * @brief Function to get the sign of the number
     * @return Sign of the number (true for negative, false for positive)
     */
    virtual bool getSign() const = 0;

     /**
      * @brief Helper function for converting vector of integers to string.
      * @param vVector Vector of integers to convert.
      * @return String representation of the vector.
      */
    std::string vectorToString(const std::vector<int> &vVector) const;
     /**
       * @brief Helper function for comparing two vectors representing numbers.
       * @param a First vector.
       * @param b Second vector.
       * @return True if the first vector is greater or equal to the second one, false otherwise.
      */
    bool isGreaterOrEqual(const std::vector<int> &a, const std::vector<int> &b) const ;
     /**
       * @brief Function for accessing the integer  number
       * @return vector of  number
       */
     virtual const std::vector<int>& getIntegerDigits() const = 0;
     /**
       * @brief Function for accessing the fractional part of a float number
       * @return vector of  number
       */
     virtual const std::vector<int>& getFractionalDigits() const = 0;
     /**
       * @brief Function for accessing the integer part of a float number
       * @return vector of  number
       */
     virtual const std::vector<int>& getIntegerPartFloat() const = 0;
     /**
      * @brief Function to set sign of the number
      * @param signs Sign to be set (true for negative, false for positive)
      */
    virtual void setSign(bool signs) = 0;
     /**
       * @brief Pure virtual function for reverse the current number
       * @return Result of the  operation as a shared_ptr to a Number
      */
     virtual std::shared_ptr<Number> negateNumber() const { return {}; }

     virtual std::shared_ptr<Number> toExponent() const = 0 ;

     virtual std::shared_ptr<Number> fromExponent() const = 0;
};




