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
        while (number_one != number_two) {
            if (number_one > number_two) {
                int64_t support = number_one;
                number_one = number_two;
                number_two = support;
            }
            number_two -= number_one;
        }
        return number_one;
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
    friend const RationalNumber operator+(const RationalNumber& our, const RationalNumber& other) {
        int64_t new_num, new_den;
        if (our.denominator != other.denominator) {
            new_num = our.numerator * other.denominator + other.numerator * our.denominator;
            new_den = our.denominator * other.denominator;
        }
        else {
            new_num = our.numerator + other.numerator;
            new_den = our.denominator;
        }
        return RationalNumber(new_num, new_den);
    }
    RationalNumber& operator+=(const RationalNumber& other) {
        *this = *this + other;
        return *this;
    }
    friend const RationalNumber operator-(const RationalNumber& our, const RationalNumber& other) {
        int64_t new_num, new_den;
        if (our.denominator != other.denominator) {
            new_num = our.numerator * other.denominator - other.numerator * our.denominator;
            new_den = our.denominator * other.denominator;
        }
        else {
            new_num = our.numerator - other.numerator;
            new_den = our.denominator;
        }
        return RationalNumber(new_num, new_den);
    }
    RationalNumber& operator-=(const RationalNumber& other) {
        *this = *this - other;
        return *this;
    }
    friend const RationalNumber operator*(const RationalNumber& our, const RationalNumber& other) {
        return RationalNumber(our.numerator * other.numerator, our.denominator * other.denominator);
    }
    RationalNumber& operator*=(const RationalNumber& other) {
        *this = *this * other;
        return *this;
    }
    friend const RationalNumber operator/(const RationalNumber& our, const RationalNumber& other) {
        return RationalNumber(our.numerator * other.denominator, our.denominator * other.numerator);
    }
    RationalNumber& operator/=(const RationalNumber& other) {
        *this = *this / other;
        return *this;
    }
    friend const bool operator==(const RationalNumber& our, const RationalNumber& other) {
        return our.numerator == other.numerator && our.denominator == other.denominator;
    }
    friend const bool operator!=(const RationalNumber& our, const RationalNumber& other) {
        return !(our == other);
    }
    RationalNumber operator-() const {
        return RationalNumber(-numerator, denominator);
    }
    friend const bool operator<(const RationalNumber& our, const RationalNumber& other) {
        return our.numerator * other.denominator < other.numerator * our.denominator;
    }
    friend const bool operator>(const RationalNumber& our, const RationalNumber& other) {
        return our.numerator * other.denominator > other.numerator* our.denominator;
    }
    friend const bool operator<=(const RationalNumber& our, const RationalNumber& other) {
        return !(our > other);
    }
    friend const bool operator>=(const RationalNumber& our, const RationalNumber& other) {
        return !(our < other);
    }
    RationalNumber Sqrt() const {
        return RationalNumber(sqrt(numerator) / sqrt(denominator));
    }
    RationalNumber Sqt() const {
        return RationalNumber(numerator * numerator, denominator * denominator);
    }
    friend ostream& operator<<(ostream& out, const RationalNumber& rational) {
        return out << rational.numerator << "/" << rational.denominator;
    }
    RationalNumber Atan() const {
        return atan(static_cast<double>(numerator) / static_cast<double>(denominator));
    }
};

class ComplexNumber {
private:
    RationalNumber real_num;
    RationalNumber imag_part;
public:
    ComplexNumber() {}
    explicit ComplexNumber(RationalNumber real_num, RationalNumber imag_part) {
        this->real_num = real_num;
        this->imag_part = imag_part;
    }
    ComplexNumber(const ComplexNumber& other) {
        real_num = other.real_num;
        imag_part = other.imag_part;
    }
    ~ComplexNumber() {}
    ComplexNumber& operator=(const ComplexNumber& other) {
        real_num = other.real_num;
        imag_part = other.imag_part;
        return *this;
    }
    ComplexNumber& operator=(RationalNumber number) {
        real_num = number;
        imag_part = 0;
        return *this;
    }
    ComplexNumber operator+(const ComplexNumber& other) const {
        RationalNumber new_real = real_num + other.real_num;
        RationalNumber new_image = imag_part + other.imag_part;
        return ComplexNumber(new_real, new_image);
    }
    ComplexNumber operator+(RationalNumber number) const {
        RationalNumber new_real = real_num + number;
        return ComplexNumber(new_real, imag_part);
    }
    ComplexNumber& operator+=(const ComplexNumber& other) {
        *this = *this + other;
        return *this;
    }
    ComplexNumber& operator+=(RationalNumber number) {
        *this = *this + number;
        return *this;
    }
    ComplexNumber operator-(const ComplexNumber& other) const {
        RationalNumber new_real = real_num - other.real_num;
        RationalNumber new_image = imag_part - other.imag_part;
        return ComplexNumber(new_real, new_image);
    }
    ComplexNumber operator-(RationalNumber number) const {
        RationalNumber new_real = real_num - number;
        return ComplexNumber(new_real, imag_part);
    }
    ComplexNumber& operator-=(const ComplexNumber& other) {
        *this = *this - other;
        return *this;
    }
    ComplexNumber& operator-=(RationalNumber number) {
        *this = *this - number;
        return *this;
    }
    ComplexNumber operator*(const ComplexNumber& other) const {
        RationalNumber new_real = real_num * other.real_num - imag_part * other.imag_part;
        RationalNumber new_image = real_num * other.imag_part + imag_part * other.real_num;
        return ComplexNumber(new_real, new_image);
    }
    ComplexNumber operator*(RationalNumber number) const {
        return ComplexNumber(real_num * number, imag_part * number);
    }
    ComplexNumber& operator*=(const ComplexNumber& other) {
        *this = *this * other;
        return *this;
    }
    ComplexNumber& operator*=(RationalNumber number) {
        *this = *this * number;
        return *this;
    }
    ComplexNumber operator/(const ComplexNumber& other) const {
        RationalNumber div = other.real_num.Sqt() + other.imag_part.Sqt();
        RationalNumber new_real = (real_num * other.real_num + imag_part * other.imag_part) / div;
        RationalNumber new_image = (imag_part * other.real_num - real_num * other.imag_part) / div;
        return ComplexNumber(new_real, new_image);
    }
    ComplexNumber operator/(RationalNumber number) const {
        return ComplexNumber(real_num / number, imag_part / number);
    }
    ComplexNumber& operator/=(const ComplexNumber& other) {
        *this = *this / other;
        return *this;
    }
    ComplexNumber& operator/=(RationalNumber number) {
        *this = *this / number;
        return *this;
    }
    friend const bool operator==(const ComplexNumber& our, const ComplexNumber& other) {
        return our.real_num == other.real_num && our.imag_part == other.imag_part;
    }
    friend const bool operator!=(const ComplexNumber& our, const ComplexNumber& other) {
        return !(our == other);
    }
    ComplexNumber operator-() const {
        return ComplexNumber(-real_num, -imag_part);
    }
    RationalNumber Abs() const {
        return RationalNumber((real_num.Sqt() + imag_part.Sqt()).Sqrt());
    }
    RationalNumber Arg() const {
        RationalNumber PI = acos(-1.0);
        RationalNumber arg_result = RationalNumber(imag_part / real_num).Atan();
        if (real_num < 0 && imag_part >= 0) {
            arg_result += PI;
        }
        else if (real_num < 0 && imag_part < 0) {
            arg_result -= PI;
        }
        return arg_result;
    }
    ComplexNumber Pow(int power = 2) {
        ComplexNumber result(real_num, imag_part);
        ComplexNumber complex_pow(real_num, imag_part);
        for (int i = 1; i < power; i++) {
            result *= complex_pow;
        }
        return result;
    }
    friend ostream& operator<<(ostream& out, const ComplexNumber& complex) {
        return out << "ComplexNumber(" << complex.real_num << ", " << complex.imag_part << ")";
    }
    void SetReal(RationalNumber real_num) {
        this->real_num = real_num;
    }
    void SetImag(RationalNumber imag_part) {
        this->imag_part = imag_part;
    }
    RationalNumber GetReal() {
        return real_num;
    }
    RationalNumber GetImag() {
        return imag_part;
    }
};

int main()
{

}
