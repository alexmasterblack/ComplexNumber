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
        while (number_one != 0) {
            auto support = number_two % number_one;
            number_two = number_one;
            number_one = support;
        }
        return number_two;
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
    bool operator<(const RationalNumber& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }
    bool operator>(const RationalNumber& other) const {
        return numerator * other.denominator > other.numerator* denominator;
    }
    bool operator<=(const RationalNumber& other) const {
        return !(*this > other);
    }
    bool operator>=(const RationalNumber& other) const {
        return !(*this < other);
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
    int64_t GetNumerator() {
        return numerator;
    }
    int64_t GetDenominator() {
        return denominator;
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
    ComplexNumber& operator=(const ComplexNumber& other) {
        real_num = other.real_num;
        imag_part = other.imag_part;
        return *this;
    }
    ComplexNumber operator+(const ComplexNumber& other) const {
        RationalNumber new_real = real_num + other.real_num;
        RationalNumber new_image = imag_part + other.imag_part;
        return ComplexNumber(new_real, new_image);
    }
    ComplexNumber& operator+=(const ComplexNumber& other) {
        *this = *this + other;
        return *this;
    }
    ComplexNumber operator-(const ComplexNumber& other) const {
        RationalNumber new_real = real_num - other.real_num;
        RationalNumber new_image = imag_part - other.imag_part;
        return ComplexNumber(new_real, new_image);
    }
    ComplexNumber& operator-=(const ComplexNumber& other) {
        *this = *this - other;
        return *this;
    }
    ComplexNumber operator*(const ComplexNumber& other) const {
        RationalNumber new_real = real_num * other.real_num - imag_part * other.imag_part;
        RationalNumber new_image = real_num * other.imag_part + imag_part * other.real_num;
        return ComplexNumber(new_real, new_image);
    }
    ComplexNumber& operator*=(const ComplexNumber& other) {
        *this = *this * other;
        return *this;
    }
    ComplexNumber operator/(const ComplexNumber& other) const {
        RationalNumber new_real = (real_num * other.real_num + imag_part * other.imag_part) / (other.real_num.Sqt() + other.imag_part.Sqt());
        RationalNumber new_image = (imag_part * other.real_num - real_num * other.imag_part) / (other.real_num.Sqt() + other.imag_part.Sqt());
        return ComplexNumber(new_real, new_image);
    }
    ComplexNumber& operator/=(const ComplexNumber& other) {
        *this = *this / other;
        return *this;
    }
    bool operator==(const ComplexNumber& other) const {
        return real_num == other.real_num && imag_part == other.imag_part;
    }
    bool operator!=(const ComplexNumber& other) const {
        return !(*this == other);
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
    void SetReal(double real_num) {
        this->real_num = real_num;
    }
    void SerImag(double imag_part) {
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
    ComplexNumber c;
    //cout << c << endl;
    //cout << sqrt(80) << endl;
    ComplexNumber a(44.0912, 98.012);
    cout << a << endl;
    cout << endl;
    //c = a.Pow(2);
    //cout << c << endl;
    //cout << a.Abs() << endl;
    //cout << a.Pow(5) << endl;
    cout << a.Arg() << endl;
    cout << a.Abs() << endl;
    
    //ComplexNumber b(-1.5, -2);
    //cout << b << endl;

    //cout << endl;
    //c.SetReal(81.169);
    //c.SerImag(1.2);
    //cout << a.GetComplex() << endl;
    //cout << -c << endl;
}
