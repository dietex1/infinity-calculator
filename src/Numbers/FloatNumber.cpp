#include "FloatNumber.h"
#include "IntegerNumber.h"
#include <stdexcept>
#include <cmath>
#include <ios>
#include <sstream>
#include <iomanip>

using namespace std;



shared_ptr<Number> FloatNumber::negateNumber() const {
    auto revNumber = make_shared<FloatNumber>(this->getIntegerPartFloat(), this->getFractionalDigits());
    revNumber->setSign(!sign);
    revNumber->integerPart.setSign(!sign);
    return revNumber;
}

shared_ptr<Number> FloatNumber::clone() const  {
    auto newNumber = make_shared<FloatNumber>(this->integerPart.toString() + "." + this->vectorToString(this->fractionalPart));
    newNumber->setSign(this->integerPart.getSign());
    return newNumber;
}

// This works by negating the other number and then adding it to this number.
shared_ptr<Number> FloatNumber::operator-(const Number &other) const {
    auto negativvdOther = other.negateNumber();
    return operator+(*negativvdOther);
}


shared_ptr<Number> FloatNumber::operator!() const {
    throw runtime_error("Factorial is not defined for floating-point numbers.");
}


shared_ptr<Number> FloatNumber::operator~() const { // // rounding
    if (fractionalPart.empty() || fractionalPart[0] < 5) {
        return make_shared<IntegerNumber>(integerPart.toString());
    } else {
        auto incrementedIntegerPart = integerPart + IntegerNumber("1");
        return make_shared<IntegerNumber>(incrementedIntegerPart->toString());
    }
}

shared_ptr<Number> FloatNumber::operator%(const Number &/*other*/) const {
    throw runtime_error("Modulo operation is not defined for floating-point numbers.");
}


shared_ptr<Number> FloatNumber::operator/(const Number &/*other*/) const {
    throw runtime_error("Division operation is not defined for floating-point numbers.");
}




FloatNumber::FloatNumber(const string &number) : integerPart("0") {
    size_t pointIndex = number.find(".");
    if (pointIndex != string::npos) {
        // Extract integer part
        string intPartStr = number.substr(0, pointIndex);
        integerPart = IntegerNumber(intPartStr);
        sign = integerPart.getSign();

        // Extract fractional part
        for (std::size_t i = number.length() - 1; i > pointIndex; --i) {
            fractionalPart.push_back(number[i] - '0');
        }
    }
    else {
        integerPart = IntegerNumber(number);
        sign = integerPart.getSign();
    }
}

string FloatNumber::toString() const {
    string result = integerPart.toString();
    if (!fractionalPart.empty()) {
        result += ".";
        for (std::size_t i = fractionalPart.size(); i-- > 0; ) {
            result += to_string(fractionalPart[i]);
        }
    }
    return result;
}



shared_ptr<Number> FloatNumber::operator+(const Number &other) const {
    shared_ptr<Number> result;

    if (other.getFractionalDigits().empty()) {

        auto intPa = make_shared<IntegerNumber>(getIntegerPartFloat());
        intPa->setSign(this->integerPart.getSign());
        shared_ptr<Number> integerPartSum = intPa->operator+(other);
        result = make_shared<FloatNumber>(integerPartSum->getIntegerDigits(), getFractionalDigits());
        result->setSign(integerPartSum->getSign());
        return result;

    }
    else   {
        auto intPa = make_shared<IntegerNumber>(getIntegerPartFloat());
        intPa->setSign(this->getSign());
        auto secPa = make_shared<IntegerNumber>(other.getIntegerPartFloat());
        secPa->setSign(other.getSign());
        shared_ptr<Number> integerPartSum ;

        integerPartSum = intPa->operator+(*secPa);

        vector<int> fractionalPartSum;
        vector<int> otherFractionalPart = other.getFractionalDigits();
        vector<int> mainFrac = getFractionalDigits();

        // Pad the smaller fractional part with zero to the right to make the same length
        while (mainFrac.size() < otherFractionalPart.size()) {
            mainFrac.insert(mainFrac.begin(), 0);
        }
        while (otherFractionalPart.size() < mainFrac.size()) {
            otherFractionalPart.insert(otherFractionalPart.begin(), 0);
        }

        // Initialize the sum of fractional parts with the same size and set each digit to 0
        fractionalPartSum.resize(mainFrac.size(), 0);


        if ( intPa->getSign() == secPa->getSign()) // adding
        {
            int carry = 0;
            for (std::size_t i = 0; i < mainFrac.size(); i++) {
                int digitSum = mainFrac[i] + otherFractionalPart[i] + carry;

                fractionalPartSum[i] = digitSum % 10; // current digit is remainder of division by 10
                carry = digitSum / 10; // carry for the next digit is the quotient of division by 10
            }

            // Handle the case when the sum of the fractional parts have to carry
            auto caryOne = make_shared<IntegerNumber>("1");
            if (carry > 0) {
                integerPartSum = integerPartSum->operator+(*caryOne);
            }
        }
        else
        {
            int borrow = 0;
            for (std::size_t i = 0; i < mainFrac.size(); i++) {
                int digitDifference = mainFrac[i] - otherFractionalPart[i] - borrow;

                if (digitDifference < 0) {
                    digitDifference += 10;
                    borrow = 1;
                }
                else {
                    borrow = 0;
                }

                fractionalPartSum[i] = digitDifference;
            }

            // Handle the case when  difference of  fractional parts have a borrow
            auto borrowOne = make_shared<IntegerNumber>("1");
            if (borrow > 0) {
                integerPartSum = integerPartSum->operator-(*borrowOne);
            }
        }


        // Remove  zero from the fractional part
        while (!fractionalPartSum.empty() && fractionalPartSum.front() == 0) {
            fractionalPartSum.erase(fractionalPartSum.begin());
        }

        result = make_shared<FloatNumber>(integerPartSum->getIntegerDigits(), fractionalPartSum);
        result->setSign(integerPartSum->getSign());
    }

    return result;
}


shared_ptr<Number> FloatNumber::operator*(const Number &other) const {
    if (!other.getFractionalDigits().empty()) {

        // Convert both  numbers to string
        string firstNum = this->toString();
        string secondNum = other.toString();

        // Remove the decimal point from the numbers and convert them to integers
        firstNum.erase(remove(firstNum.begin(), firstNum.end(), '.'), firstNum.end());
        secondNum.erase(remove(secondNum.begin(), secondNum.end(), '.'), secondNum.end());
        auto firstInt = make_shared<IntegerNumber>(firstNum);
        auto secondInt = make_shared<IntegerNumber>(secondNum);

        // Multiply the numbers as if they are whole numbers
        shared_ptr<Number> result = firstInt->operator*(*secondInt);

        // Count the number of decimal places in the original numbers
        size_t decimalPlaces = this->getFractionalDigits().size() + other.getFractionalDigits().size();

        // Convert the result to a string
        string resultStr = result->toString();

        // Ensure the string is long enough to insert the decimal point at the correct place
        while (resultStr.size() < decimalPlaces + 1) {
            resultStr = "0" + resultStr;
        }

        // Insert the decimal point
        resultStr.insert(resultStr.size() - decimalPlaces, 1, '.');

        // Create a new FloatNumber from the resulting string
        auto finalResult = make_shared<FloatNumber>(resultStr);
        finalResult->setSign(!(this->getSign() ^ other.getSign()));

        // If the result is 0, set the sign to positive
        if (finalResult->getIntegerPartFloat()[0] == 0 && finalResult->getFractionalDigits()[0] == 0) {
            return make_shared<IntegerNumber>("0");
        }

        return finalResult;
    }
    else   {
        if ( other.getIntegerDigits()[0] == 0 &&  other.getIntegerDigits().size() == 1)
            return make_shared<IntegerNumber>("0");
        vector<int>vecZero ;
        vecZero.push_back(0);
        auto floatInt = make_shared<FloatNumber>(other.getIntegerDigits(),vecZero);
        floatInt->setSign(other.getSign());
        auto result  = this->operator*(*floatInt);
        result->setSign(!(this->getSign() ^ other.getSign()));
        return result;
    }
}



shared_ptr<Number> FloatNumber::operator^(const Number &other) const {
    if ((!other.getFractionalDigits().empty()) || !other.getSign() || (other.getIntegerDigits().size() == 1 && other.getIntegerDigits()[0] < 0)) {
        throw runtime_error("The tenExponent must be a non-negative integer.");
    }
    auto one = make_shared<IntegerNumber>("1");
    auto decrement = make_shared<IntegerNumber>("1");
    auto base = this->clone();
    auto exponent = other.clone();
    if (other.getIntegerDigits().size() == 1 && other.getIntegerDigits()[0] == 0) {
        // Any number  pow  0 is 1
        return make_shared<IntegerNumber>("1");
    }
    auto result = base;
    // Decrease the tenExponent by one  because we always have one instance of 'this' in 'result'
    exponent = exponent->operator-(*decrement);
    while (!(exponent->getIntegerDigits().size() == 1 && exponent->getIntegerDigits()[0] == 0)) {
        result = result->operator*(*base);
        exponent = exponent->operator-(*decrement);
    }
    return result;
}


std::shared_ptr<Number> FloatNumber::toExponent() const
{ return integerPart.toExponent(); }


std::shared_ptr<Number> FloatNumber::fromExponent() const
{ return integerPart.fromExponent(); }
