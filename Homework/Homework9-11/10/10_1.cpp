#include <iostream>
#include <numeric>
#include <stdexcept>
using namespace std;

//使用面向对象技术完成习题7.1，并为有理数类重载必要的操作符。

class Rational 
{
private:
    int numerator;   // Numerator
    int denominator; // Denominator

    void simplify() {
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Rational(int num = 0, int den = 1) {
        if (den == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        numerator = num;
        denominator = den;
        simplify();
    }

    int getNumerator() const {
        return numerator;
    }

    int getDenominator() const {
        return denominator;
    }

    Rational operator+(const Rational& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int den = denominator * other.denominator;
        return Rational(num, den);
    }

    Rational operator-(const Rational& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int den = denominator * other.denominator;
        return Rational(num, den);
    }

    Rational operator*(const Rational& other) const {
        int num = numerator * other.numerator;
        int den = denominator * other.denominator;
        return Rational(num, den);
    }

    Rational operator/(const Rational& other) const {
        if (other.numerator == 0) {
            throw invalid_argument("Division by zero.");
        }
        int num = numerator * other.denominator;
        int den = denominator * other.numerator;
        return Rational(num, den);
    }

    bool operator==(const Rational& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const Rational& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const Rational& r) {
        os << r.numerator << "/" << r.denominator;
        return os;
    }

    friend istream& operator>>(istream& is, Rational& r) {
        char slash;
        is >> r.numerator >> slash >> r.denominator;
        if (r.denominator == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        r.simplify();
        return is;
    }
};


int main() 
{
    try {
        Rational r1, r2;

        cout << "This program implements a rational number library with basic arithmetic operations." << endl;

        cout << "Enter the first rational number (format: x/y): ";
        cin >> r1;

        cout << "Enter the second rational number (format: x/y): ";
        cin >> r2;

        cout << "Simplified results:" << endl;
        cout << "First rational number: " << r1 << endl;
        cout << "Second rational number: " << r2 << endl;

        cout << "Addition result: " << (r1 + r2) << endl;
        cout << "Subtraction result: " << (r1 - r2) << endl;
        cout << "Multiplication result: " << (r1 * r2) << endl;
        cout << "Division result: " << (r1 / r2) << endl;

        cout << "Equality check: " << (r1 == r2 ? "Equal" : "Not equal") << endl;

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}