#include "IntegerNumber.h"
#include <string>
#include <algorithm>

using namespace std;

shared_ptr<Number> IntegerNumber::clone() const  {
    auto newNumber = make_shared<IntegerNumber>(this->getIntegerDigits());
    newNumber->setSign(this->getSign());
    return newNumber;
}

unsigned long long IntegerNumber::vectorToUnsignedLongLong(const vector<int>& digitss) const {
    unsigned long long result = 0;

    for (std::size_t i = digitss.size(); i-- > 0; ) {
        result *= 10;
        result += (unsigned long long)(digitss[i]);
    }

    return result;
}


vector<int> IntegerNumber::unsignedLongLongToVector(unsigned long long num) const {
    vector<int> res;
    if (num == 0) {
        res.push_back(0);
    }
    else {
        while (num > 0) {
            res.push_back(num % 10);
            num /= 10;
        }
    }
    return res;
}

IntegerNumber::IntegerNumber(const string &number) : sign(true) {
    size_t startIndex = 0;
    if (number[0] == '-') {
        sign = false;
        startIndex = 1;
    }

    for (size_t i = number.length(); i-- > startIndex; ) {
        int digit = number[i] - '0';
        digits.push_back(digit);
    }
}


IntegerNumber::IntegerNumber(const vector<int>& digits) : digits(digits) {}


shared_ptr<Number> IntegerNumber::negateNumber() const  {
    auto revNumber = make_shared<IntegerNumber>(*this);
    revNumber->setSign(!sign);
    return revNumber;
}

string IntegerNumber::toString() const {
    string result;
    if (!sign) {
        result.push_back('-');
    }
    for (size_t i = digits.size(); i-- > 0; ) {
        char digit_char = (char)('0' + digits[i]);
        result.push_back(digit_char);
    }
    return result;
}

vector<int> IntegerNumber::subtractIntegerDigits(const vector<int>& largerNumb, const vector<int>& smallerNumb) const {
    vector<int> result(largerNumb.size(), 0);
    int borrow = 0;
    for (size_t i = 0; i < largerNumb.size(); ++i) {
        int diff = largerNumb[i] - borrow;
        if (i < smallerNumb.size()) {
            diff -= smallerNumb[i];
        }
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result[i] = diff;
    }
    // Remove  zero if have
    while (!result.empty() && result.back() == 0) {
        result.pop_back();
    }
    // If the result is empty,  subtraction result in zero
    if (result.empty()) {
        result.push_back(0);
    }
    return result;
}

shared_ptr<Number> IntegerNumber::operator+(const Number &other) const {
    if (other.getFractionalDigits().empty()) {
        const vector<int> &otherDigits = other.getIntegerDigits();

        if (sign == other.getSign()) {
            // Both numbers have the same sign (both positive or both negative)
            vector<int> result(max(digits.size(), otherDigits.size()) + 1, 0);
            int carry = 0;
            for (size_t i = 0; i < result.size() - 1; ++i) {
                int digitSum = carry;
                if (i < digits.size()) {
                    digitSum += digits[i];
                }
                if (i < otherDigits.size())
                    digitSum += otherDigits[i];
                result[i] = digitSum % 10;
                carry = digitSum / 10;
            }
            if (carry > 0)
                result.back() = carry;
            // Remove leading zeros if any
            if (!result.empty() && result.back() == 0) {
                result.pop_back();
            }
            auto resultNumber = make_shared<IntegerNumber>(result);
            resultNumber->setSign(sign);
            return resultNumber;
        } else {
            // One number is positive, and the other is negative

            // Determine which number has a greater absolute value
            bool thisGreater = isGreaterOrEqual(digits, other.getIntegerDigits());
            // Perform subtraction between the integer digits
            vector<int> result = subtractIntegerDigits(thisGreater ? digits : other.getIntegerDigits(),thisGreater ? other.getIntegerDigits() : digits);
            // Remove leading zeros, if any
            while (result.size() > 1 && result.back() == 0) {
                result.pop_back();
            }
            auto resultNumber = make_shared<IntegerNumber>(result);
            // If the result is zero, set the sign to true (positive)
            if (result.size() == 1 && result[0] == 0) {
                resultNumber->setSign(true);
            } else {
                resultNumber->setSign(thisGreater ? sign : other.getSign());
            }
            return resultNumber;
        }
    }else {
        // Making addition and give proccessing it  to the other object (FloatNumber)
        return other.operator+(*this);
    }
}

shared_ptr<Number> IntegerNumber::operator-(const Number &other) const {
    auto negatedOther = other.negateNumber();
    return operator+(*negatedOther);
}


shared_ptr<Number> IntegerNumber::operator*(const Number &other) const {
    if (other.getFractionalDigits().empty()) {
        const vector<int> &otherDigits = other.getIntegerDigits();
        vector<int> result(digits.size() + otherDigits.size(), 0);
        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < otherDigits.size(); ++j) {
                int prod = digits[i] * otherDigits[j] + carry + result[i + j];
                result[i + j] = prod % 10;
                carry = prod / 10;
            }
            if (carry > 0) {
                result[i + otherDigits.size()] = carry;
            }
        }
        // Remove  zero
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }
        auto resultNumber = make_shared<IntegerNumber>(result);
        // Set the result sign based on the signs of the input numbers
        resultNumber->setSign(!(sign ^ other.getSign()));
        // If the result is 0, set the sign to positive
        if (resultNumber->getIntegerDigits()[0] == 0 && result.size() == 1 ) {
            resultNumber->setSign(true);
        }
        return resultNumber;
    } else {
        return other.operator*(*this);
    }
}

shared_ptr<Number> IntegerNumber::operator!() const {
    if (!sign) {
        throw runtime_error("Number must be positive.");
    }

    if (digits.empty() || (digits.size() == 1 && digits[0] == 0)) {
        return make_shared<IntegerNumber>("1");
    }
    vector<int> result = {1};
    for (int i = 1; i <= stoi(toString()); i++) {
        int carry = 0;
        for (size_t j = 0; j < result.size(); j++) {
            int product = result[j] * i + carry;
            result[j] = product % 10;
            carry = product / 10;
        }

        while (carry > 0) {
            result.push_back(carry % 10);
            carry /= 10;
        }
    }
    auto resultNumber = make_shared<IntegerNumber>(result);
    resultNumber->setSign(true);
    return resultNumber;
}

shared_ptr<Number> IntegerNumber::operator~() const { // // rounding
    return make_shared<IntegerNumber>(*this);
}

shared_ptr<Number> IntegerNumber::operator%(const Number &other) const {
    if (other.getFractionalDigits().empty()) {
        if (other.toString() == "0") {
            throw runtime_error("Division by zero is not defined.");
        }

        vector<int> dividend = digits;
        vector<int> divisor = other.getIntegerDigits();
        vector<int> resultDigits;

        if (dividend.size() < 19) { // 19 is the max number of digits in ULLONG_MAX
            unsigned long long numDivd = vectorToUnsignedLongLong(dividend);
            unsigned long long numDivs = vectorToUnsignedLongLong(divisor);

            unsigned long long tmp = numDivd % numDivs;
            resultDigits = unsignedLongLongToVector(tmp);
        } else {
            while (isGreaterOrEqual(dividend, divisor)) {
                dividend = subtractIntegerDigits(dividend, divisor);
            }
            resultDigits = dividend;
        }

        auto result = make_shared<IntegerNumber>(resultDigits);
        result->setSign(true);
        return result;
    } else {
        throw runtime_error("Modulo operation is not defined for floating-point numbers.");
    }
}




shared_ptr<Number> IntegerNumber::operator/(const Number &other) const  {
    if (other.getFractionalDigits().empty()) {
        const vector<int> &otherDigits = other.getIntegerDigits();

        if (otherDigits.size() == 1 && otherDigits[0] == 0) {
            throw runtime_error("Division by zero");
        }

// If the divisor is larger than the dividend the division result is 0.
        if (isGreaterOrEqual(otherDigits, digits)) {
            auto resultNumber = make_shared<IntegerNumber>(vector<int>{0});
            resultNumber->setSign(true);
            return resultNumber;
        }

        vector<int> result(digits.size(), 0);
        vector<int> temp(digits.size(), 0);

// Iterate from the most significant digit to the least
        for (std::size_t i = digits.size(); i-- > 0; ) {
// Bring down the next digit of the dividend
            temp.insert(temp.begin(), digits[i]);
// Remove  zero in temp
            while (!temp.empty() && temp.back() == 0) {
                temp.pop_back();
            }
// Determine how many times the divisor can go into the current value of temp
            while (isGreaterOrEqual(temp, otherDigits)) {
// Increase the result digit
                ++result[i];
// Subtract the divisor from temp
                temp = subtractIntegerDigits(temp, otherDigits);
            }
        }
// Remove  zeros in the result
        while (!result.empty() && result.back() == 0) {
            result.pop_back();
        }

        auto resultNumber = make_shared<IntegerNumber>(result);
// Set the result sign based on the signs of the input numbers
        resultNumber->setSign(!(sign ^ other.getSign()));
// If the result is 0, set the sign to positive
        if (resultNumber->getIntegerDigits()[0] == 0 && result.size() == 1 ) {
            resultNumber->setSign(true);
        }

        return resultNumber;
    } else {
        throw runtime_error("Cannot divide integer by float");

    }
}


shared_ptr<Number> IntegerNumber::operator^(const Number &other) const {
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






std::shared_ptr<Number> IntegerNumber::toExponent() const
{
    auto it = digits.rbegin();
    while (it != digits.rend() && *it == 0)
    {
        ++it; // Skip trailing zeros

    }

    auto withExponent = std::make_shared<IntegerNumber>(digits);
    // Calculate the count of trailing zeros
    unsigned long long zeroCount = digits.size() - (unsigned long long)std::distance(digits.rbegin(), it);

    // Resize the digits vector to remove the trailing zeros
    withExponent->digits.resize(digits.size() - zeroCount);

    // Create a new vector to store the count of zeros
    withExponent->tenExponent = zeroCount;

    // Create and return a shared pointer to the new Number object
    return withExponent;
}



std::shared_ptr<Number> IntegerNumber::fromExponent() const
{
    auto withoutExponent = std::make_shared<IntegerNumber>(digits);

    // withoutExponent trailing zeros to the digits vector based on the tenExponent value
    withoutExponent->digits.resize(digits.size() + tenExponent, 0);

    // Reset the tenExponent to 0
    withoutExponent->tenExponent = 0;

    // Create and return a shared pointer to the new Number object
    return withoutExponent;
}

