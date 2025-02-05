// BigUnsigned.h
#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class BigUnsigned {
private:
    std::vector<unsigned char> digits;
    void removeLeadingZeros();
    

public:
    BigUnsigned(unsigned n = 0);
    BigUnsigned(const std::string&);
    BigUnsigned(const BigUnsigned&);
    BigUnsigned& operator=(const BigUnsigned&);
    bool operator==(const BigUnsigned&) const;
    friend bool operator<(const BigUnsigned&, const BigUnsigned&);
    friend BigUnsigned operator+(const BigUnsigned&, const BigUnsigned&);
    BigUnsigned operator-(const BigUnsigned&) const;
    BigUnsigned operator*(const BigUnsigned&) const;
    friend std::ostream& operator<<(std::ostream&, const BigUnsigned&);
};

#endif // BIGUNSIGNED_H

// BigUnsigned.cpp
#include "BigUnsigned.h"

void BigUnsigned::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

BigUnsigned::BigUnsigned(unsigned n) {
    do {
        digits.push_back(n % 10);
        n /= 10;
    } while (n > 0);
}

BigUnsigned::BigUnsigned(const std::string& str) {
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        digits.push_back(*it - '0');
    }
}

BigUnsigned::BigUnsigned(const BigUnsigned& other) : digits(other.digits) {}

BigUnsigned& BigUnsigned::operator=(const BigUnsigned& other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

bool BigUnsigned::operator==(const BigUnsigned& other) const {
    return digits == other.digits;
}

std::ostream& operator<<(std::ostream& os, const BigUnsigned& num) {
    for (auto it = num.digits.rbegin(); it != num.digits.rend(); ++it) {
        os << (char)(*it + '0');
    }
    return os;
}

// BigInteger.h
#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include "BigUnsigned.h"

class BigInteger {
private:
    BigUnsigned value;
    bool isNegative;

public:
    BigInteger(int n = 0);
    BigInteger(const BigUnsigned&);
    BigInteger(const BigInteger&);
    static BigInteger gcd(BigInteger, BigInteger);
    friend std::istream& operator>>(std::istream&, BigInteger&);
    friend std::ostream& operator<<(std::ostream&, const BigInteger&);
};

#endif // BIGINTEGER_H

// BigInteger.cpp
#include "BigInteger.h"

BigInteger::BigInteger(int n) : value(std::abs(n)), isNegative(n < 0) {}
BigInteger::BigInteger(const BigUnsigned& v) : value(v), isNegative(false) {}
BigInteger::BigInteger(const BigInteger& other) : value(other.value), isNegative(other.isNegative) {}

BigInteger BigInteger::gcd(BigInteger a, BigInteger b) {
    while (!(b.value == BigUnsigned(0))) {
        a = BigInteger(a.value % b.value);
        std::swap(a, b);
    }
    return a;
}

std::istream& operator>>(std::istream& is, BigInteger& num) {
    std::string str;
    is >> str;
    num.isNegative = (str[0] == '-');
    num.value = BigUnsigned(num.isNegative ? str.substr(1) : str);
    return is;
}

std::ostream& operator<<(std::ostream& os, const BigInteger& num) {
    if (num.isNegative) os << '-';
    os << num.value;
    return os;
}

// main.cpp
#include "BigInteger.h"

int main() {
    BigInteger a, b;
    std::cout << "Introduce dos números grandes: ";
    std::cin >> a >> b;
    std::cout << "El MCD de " << a << " y " << b << " es " << BigInteger::gcd(a, b) << std::endl;
    return 0;
}
