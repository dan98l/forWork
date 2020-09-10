#ifndef LAB1_FRACTION_HPP
#define LAB1_FRACTION_HPP

#include <exception>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <string>

template<typename T>
class Fraction {
public:
    Fraction() : numerator(0), denominator(1) {}

    Fraction(T a, T b);

    Fraction(const std::string &str);

    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const Fraction<U> &fraction);

    Fraction<T> operator+(Fraction<T> a);

    Fraction<T> operator-(Fraction<T> a);

    Fraction<T> operator-();

    Fraction<T> operator*(Fraction<T> a);

    Fraction<T> operator/(Fraction<T> a);

    bool operator<(Fraction<T> a);

    bool operator==(Fraction<T> a);

    bool operator>(Fraction<T> a);

    Fraction<T> sqr();

    Fraction<T> inverse();

    T getNumerator();

    T getDenominator();

    std::string getNumeratorString();

    std::string getDenominatorString();

    std::string getFractionString();

private:
    T numerator, denominator;

    void checkForMinus();

    T gcd(T a, T b);
};

template<typename T>
Fraction<T>::Fraction(T a, T b) {
    numerator = a;
    denominator = b;
    if (denominator == 0) {
        throw std::runtime_error("Denominator must not be zero");
    } else {
        checkForMinus();
        T divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;
    }
}

template<typename T>
T Fraction<T>::gcd(T a, T b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

template<typename T>
Fraction<T>::Fraction(const std::string &str) {
    if (std::count(str.begin(), str.end(), '/') > 1) {
        throw std::runtime_error("Illegal characters detected");
    } else if (std::count(str.begin(), str.end(), '/') == 1){
        auto slash_positon_iterator = std::find(str.begin(), str.end(), '/');
        numerator = std::stoi(str.substr(0, std::distance(str.begin(), slash_positon_iterator)));
        denominator = std::stoi(str.substr(std::distance(str.begin(), slash_positon_iterator) + 1, std::distance(slash_positon_iterator, str.end())));
    } else {
        numerator = std::stoi(str.substr(0, std::distance(str.begin(), str.end())));
        denominator = 1;
    }

    checkForMinus();
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Fraction<T> &fraction) {
    os << fraction.numerator << "/" << fraction.denominator;
    return os;
}

template<typename T>
Fraction<T> Fraction<T>::operator+(Fraction<T> a) {
    checkForMinus();

    if (this->denominator == a.denominator) {
        this->numerator += a.numerator;
        return *this;
    }

    T divisor = Fraction<T>::gcd(this->denominator, a.denominator);

    if (divisor == 1) {
        this->numerator = this->numerator * a.denominator + a.numerator * this->denominator;
        this->denominator *= a.denominator;
    } else {
        if (this->denominator < a.denominator) {
            this->denominator *= divisor;
            this->numerator *= divisor + a.numerator;
        } else {
            a.denominator *= divisor;
            this->numerator += (a.numerator * divisor);
        }
    }

    return *this;
}

template<typename T>
Fraction<T> Fraction<T>::operator-(Fraction<T> a) {
    checkForMinus();
    a.numerator *= -1;
    *this = *this + a;
    return *this;
}

template<typename T>
Fraction<T> Fraction<T>::operator*(Fraction<T> a) {
    checkForMinus();
    this->numerator *= a.numerator;
    this->denominator *= a.denominator;

    T divisor = Fraction<T>::gcd(this->numerator, this->denominator);
    numerator /= divisor;
    denominator /= divisor;

    return *this;
}

template<typename T>
Fraction<T> Fraction<T>::operator/(Fraction<T> a) {
    std::swap(a.numerator, a.denominator);
    checkForMinus();

    *this *= a;
    return *this;
}

template<typename T>
Fraction<T> Fraction<T>::sqr() {
    checkForMinus();
    return *this * *this;
}

template<typename T>
Fraction<T> Fraction<T>::inverse() {
    std::swap(this->numerator, this->denominator);
    checkForMinus();
    return *this;
}

template<typename T>
void Fraction<T>::checkForMinus() {
    if (numerator < 0 && denominator < 0) {
        denominator = -denominator;
    } else if (denominator < 0 && numerator > 0) {
        denominator = -denominator;
        numerator = -numerator;
    }
}

template<typename T>
Fraction<T> Fraction<T>::operator-() {
    checkForMinus();
    numerator *= -1;
    return *this;
}

template<typename T>
bool Fraction<T>::operator<(Fraction<T> a) {
    auto copy = *this;
    if (this->denominator == a.denominator) {
        return this->numerator < a.numerator;
    } else {
        checkForMinus();
        copy.numerator *= a.denominator;
        a.numerator *= copy.denominator;
        return copy.numerator < a.numerator;
    }
    return false;
}

template<typename T>
bool Fraction<T>::operator==(Fraction<T> a) {
    auto copy = *this;
    if (this->denominator == a.denominator) {
        return this->numerator < a.numerator;
    } else {
        checkForMinus();
        copy.numerator *= a.denominator;
        a.numerator *= copy.denominator;
        return copy.numerator == a.numerator;
    }
    return false;
}

template<typename T>
bool Fraction<T>::operator>(Fraction<T> a) {
    auto copy = *this;
    if (this->denominator == a.denominator) {
        return this->numerator < a.numerator;
    } else {
        checkForMinus();
        copy.numerator *= a.denominator;
        a.numerator *= copy.denominator;
        return copy.numerator > a.numerator;
    }
    return false;
}

template<typename T>
T Fraction<T>::getNumerator() {
    return numerator;
}

template<typename T>
T Fraction<T>::getDenominator() {
    return denominator;
}

template<typename T>
std::string Fraction<T>::getNumeratorString() {
    std::stringstream stringstream;
    stringstream << numerator;
    return stringstream.str();
}

template<typename T>
std::string Fraction<T>::getDenominatorString() {
    std::stringstream stringstream;
    stringstream << denominator;
    return stringstream.str();
}

template<typename T>
std::string Fraction<T>::getFractionString() {
    std::stringstream stringstream;
    stringstream << numerator << "/" << denominator;
    return stringstream.str();
}


#endif //LAB1_FRACTION_HPP
