#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <numeric>

class Rational {
public:
    Rational();
    Rational(int numerator, int denominator = 1);
    Rational(const Rational& r);

    Rational Inv() const;
    int GetNumerator() const;
    int GetDenominator() const;

    // binary arithmetic
    Rational operator+(const Rational& r) const;
    Rational operator-(const Rational& r) const;
    Rational operator*(const Rational& r) const;
    Rational operator/(const Rational& r) const;
    // end binary arithmetic

    // assigment arithmentic
    Rational& operator+=(const Rational& r);
    Rational& operator-=(const Rational& r);
    Rational& operator*=(const Rational& r);
    Rational& operator/=(const Rational& r);
    // end assigment arithmetic

    // assigment
    Rational& operator=(const Rational& r);
    // end assigment

    // unary
    Rational operator+() const;
    Rational operator-() const;
    // end unary

    // i/o
    friend std::ostream& operator<<(std::ostream& os, const Rational& rational);
    friend std::istream& operator>>(std::istream& is, Rational& rational);
    // end i/o

    // equals
    friend auto operator<=>(const Rational& lhs, const Rational& rhs);
    friend auto operator==(const Rational& lhs, const Rational& rhs);
    // end equals

private:
    int numerator_;
    int denominator_{1};

    void Reduction();
};

inline Rational::Rational() : numerator_(0) {
}

inline Rational::Rational(int numerator, int denominator)
    : numerator_(numerator), denominator_(denominator) {
    Reduction();
}

inline Rational::Rational(const Rational& r)
    : numerator_(r.numerator_), denominator_(r.denominator_) {
}

inline Rational Rational::Inv() const {
    return {denominator_, numerator_};
}

inline int Rational::GetNumerator() const {
    return numerator_;
}

inline int Rational::GetDenominator() const {
    return denominator_;
}

inline Rational Rational::operator+(const Rational& r) const {
    auto n = numerator_ * r.GetDenominator() + r.GetNumerator() * denominator_;
    auto d = denominator_ * r.GetDenominator();

    return {n, d};
}

inline Rational Rational::operator-(const Rational& r) const {
    auto n = numerator_ * r.GetDenominator() - r.GetNumerator() * denominator_;
    auto d = denominator_ * r.GetDenominator();

    return {n, d};
}

inline auto operator<=>(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator_ * rhs.denominator_ <=>
           rhs.numerator_ * lhs.denominator_;
}

inline auto operator==(const Rational& lhs, const Rational& rhs) {
    auto l_num{lhs.numerator_ * rhs.denominator_};
    auto r_num{rhs.numerator_ * lhs.denominator_};

    return !(l_num < r_num) && !(l_num > r_num);
}

inline Rational Rational::operator*(const Rational& r) const {
    auto n = numerator_ * r.GetNumerator();
    auto d = denominator_ * r.GetDenominator();

    return {n, d};
}

inline Rational Rational::operator/(const Rational& r) const {
    auto n = numerator_ * r.GetDenominator();
    auto d = denominator_ * r.GetNumerator();

    return {n, d};
}

inline Rational& Rational::operator+=(const Rational& r) {
    numerator_ =
        numerator_ * r.GetDenominator() + r.GetNumerator() * denominator_;

    denominator_ *= r.GetDenominator();

    Reduction();

    return *this;
}

inline Rational& Rational::operator-=(const Rational& r) {
    numerator_ =
        numerator_ * r.GetDenominator() - r.GetNumerator() * denominator_;

    denominator_ *= r.GetDenominator();

    Reduction();

    return *this;
}

inline Rational& Rational::operator*=(const Rational& r) {
    numerator_ *= r.GetNumerator();
    denominator_ *= r.GetDenominator();

    Reduction();

    return *this;
}

inline Rational& Rational::operator/=(const Rational& r) {
    numerator_ *= r.GetDenominator();
    denominator_ *= r.GetNumerator();

    Reduction();

    return *this;
}

inline Rational& Rational::operator=(const Rational& r) {
    numerator_ = r.numerator_;
    denominator_ = r.denominator_;

    return *this;
}

inline Rational Rational::operator+() const {
    return *this;
}

inline Rational Rational::operator-() const {
    return {-numerator_, denominator_};
}

inline void Rational::Reduction() {
    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
    const int divisor = std::gcd(numerator_, denominator_);
    numerator_ /= divisor;
    denominator_ /= divisor;
}

inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    if (r.denominator_ == 1) {
        os << r.numerator_;
    } else {
        os << r.numerator_ << " / " << r.denominator_;
    }

    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {
    int n = 0;
    is >> n;
    if (is.fail()) {
        return is;
    }

    r.numerator_ = n;

    char tmp = 0;
    is.get(tmp);
    if (tmp == ' ') {
        is.get(tmp);
        if (is.fail()) {
            is.clear();

            return is;
        } else if (tmp != '/') {
            is.unget();

            return is;
        }
    }

    int d = 1;
    is >> d;
    if (is.fail() || 0 == d) {
        is.setstate(std::ios_base::failbit);
        return is;
    }

    r.denominator_ = d;

    r.Reduction();

    return is;
}

#endif  // RATIONAL_H
