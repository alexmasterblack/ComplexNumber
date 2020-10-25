#include <iostream>
#include <cmath> 
#include <string>
#include <sstream>   

using namespace std;

class RationalNumber {
    int64_t numerator = 0;
    int64_t denominator = 1;
public:
    RationalNumber() {}
    RationalNumber(double number) {
        if (number == static_cast<int64_t>(number)) {
            numerator = static_cast<int64_t>(number);
            denominator = 1;
        }
        else {
            ostringstream str;
            str << number;
            string decimal = str.str();
            string after_point = decimal.substr(decimal.find('.') + 1);
            int lenght = after_point.length();

            for (; lenght > 0; lenght--) {
                number *= 10;
                denominator *= 10;
            }
            numerator = number;
            Reduction();
        }
    }
    RationalNumber(int64_t numerator, int64_t denominator) {
        if (denominator != 0) {
            this->numerator = numerator;
            this->denominator = denominator;
        }
        if (this->denominator <= 0) {
            this->denominator = -this->denominator;
            this->numerator = -this->numerator;
        }
        if (this->numerator != 0) {
            Reduction();
        }
        else {
            this->denominator = 1;
        }
    }
    int64_t GreatestCommonFactor(int64_t number_one, int64_t number_two) {
        if (number_one == number_two) {
            return number_one;
        }
        if (number_one > number_two) {
            int64_t support = number_one;
            number_one = number_two;
            number_two = support;
        }
        return GreatestCommonFactor(number_one, number_two - number_one);
    }
    void Reduction() {
        int64_t div = GreatestCommonFactor(abs(numerator), denominator);
        numerator /= div;
        denominator /= div;
    }
    RationalNumber& operator=(const RationalNumber& other) {
        numerator = other.numerator;
        denominator = other.denominator;
        return *this;
    }
    RationalNumber operator+(const RationalNumber& other) const {
        int64_t new_num, new_den;
        if (denominator != other.denominator) {
            new_num = numerator * other.denominator + other.numerator * denominator;
            new_den = denominator * other.denominator;
        }
        else {
            new_num = numerator + other.numerator;
            new_den = denominator;
        }
        return RationalNumber(new_num, new_den);
    }
    RationalNumber& operator+=(const RationalNumber& other) {
        *this = *this + other;
        return *this;
    }
    RationalNumber operator-(const RationalNumber& other) const {
        int64_t new_num, new_den;
        if (denominator != other.denominator) {
            new_num = numerator * other.denominator - other.numerator * denominator;
            new_den = denominator * other.denominator;
        }
        else {
            new_num = numerator - other.numerator;
            new_den = denominator;
        }
        return RationalNumber(new_num, new_den);
    }
    RationalNumber& operator-=(const RationalNumber& other) {
        *this = *this - other;
        return *this;
    }
    RationalNumber operator*(const RationalNumber& other) const {
        return RationalNumber(numerator * other.numerator, denominator * other.denominator);
    }
    RationalNumber& operator*=(const RationalNumber& other) {
        *this = *this * other;
        return *this;
    }
    RationalNumber operator/(const RationalNumber& other) const  {
        return RationalNumber(numerator * other.denominator, denominator * other.numerator);
    }
    RationalNumber& operator/=(const RationalNumber& other) {
        *this = *this / other;
        return *this;
    }
    bool operator==(const RationalNumber& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }
    bool operator!=(const RationalNumber& other) const {
        return !(*this == other);
    }
    RationalNumber operator-() const {
        return RationalNumber(-numerator, denominator);
    }
    int64_t GetNumerator() {
        return numerator;
    }
    int64_t GetDenominator() {
        return denominator;
    }
    string GetDecimal() {
        return to_string(numerator) + '/' + to_string(denominator);
    }
};

class ComplexNumber {
private:
    RationalNumber real_num;
    RationalNumber imag_part;
public:
    ComplexNumber() {}
    explicit ComplexNumber(double real_num, double imag_part) {
        this->real_num = RationalNumber(real_num);
        this->imag_part = RationalNumber(imag_part);
    }
    ComplexNumber(const ComplexNumber& other) {
        real_num = other.real_num;
        imag_part = other.imag_part;
    }
    ComplexNumber& operator=(const ComplexNumber& other) {
        real_num = other.real_num;
        imag_part = other.imag_part;
        return *this;
    }
    RationalNumber GetReal() {
        return real_num;
    }
    RationalNumber GetImag() {
        return imag_part;
    }
    string GetComplex() {
        return GetReal().GetDecimal() + " + i " + GetImag().GetDecimal();
    }
};

int main()
{
    RationalNumber l;
    cout << l.GetDecimal() << endl;


    ComplexNumber c;
    cout << c.GetComplex() << endl;
    ComplexNumber a(1.5, 2);
    cout << a.GetComplex() << endl;
    ComplexNumber b(1.2, 7);
    cout << b.GetComplex() << endl;
    a = b;
    cout << a.GetComplex() << endl;
}
