#include <iostream>
#include <numeric> 
using namespace std;

// 设计并实现有理数库。使用整数表示有理数的分子与分母，完成有理数的加减乘除与化简运算。
// 这里直接选择采用了面向对象技术。
class Rational 
{
private:
    int numerator;   // 分子
    int denominator; // 分母

    void simplify() {
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        if (denominator < 0){ 
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Rational(int num, int den) {
        if (den == 0) {
            throw invalid_argument("分母不能为零！");
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

    friend ostream& operator<<(ostream& os, const Rational& r) {
        os << r.numerator << "/" << r.denominator;
        return os;
    }
};


int main() {
    try {
        int num, den;
        char slash;
        
        cout << "本程序实现有理数库, 支持有理数的四则运算。" << endl;

        cout << "请输入第一个有理数 (格式为 x/y): ";
        cin >> num >> slash >> den;
        Rational r1(num, den);

        cout << "请输入第二个有理数 (格式为 x/y): ";
        cin >> num >> slash >> den;
        Rational r2(num, den);

        cout << "化简后结果为——" << endl;
        cout << "第一个有理数: " << r1 << endl;
        cout << "第二个有理数: " << r2 << endl;

        cout << "加法结果: " << (r1 + r2) << endl;
        cout << "减法结果: " << (r1 - r2) << endl;
        cout << "乘法结果: " << (r1 * r2) << endl;
        cout << "除法结果: " << (r1 / r2) << endl;

    } 
    catch (const exception& e) {
        cout << "非法输入: " << e.what() << endl;
    }
    return 0;
}