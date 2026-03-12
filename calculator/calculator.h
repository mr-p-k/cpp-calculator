#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <cmath>
#include <cstdint>
#include <optional>
#include <string>

#include "pow.h"
#include "rational.h"

using Error = std::string;

// Реализация шаблонного калькулятора.
template <class Number>
class Calculator {
public:
    // Заменяет текущее число (результат) на число n.
    void Set(Number n);

    // Возвращает текущий результат вычислений калькулятора. В только что
    // сконструированном калькуляторе этот метод возвращает 0.
    Number GetNumber() const;

    // Прибавляет число n к текущему результату внутри калькулятора.
    std::optional<Error> Add(Number n);

    // Вычитает число n из текущего результата.
    std::optional<Error> Sub(Number n);

    // Делит текущий результат на n.
    std::optional<Error> Div(Number n);

    // Умножает текущий результат на n
    std::optional<Error> Mul(Number n);

    // Возводит текущий результат в степень n.
    std::optional<Error> Pow(Number n);

    // Сохраняет текущий результат в ячейку памяти калькулятора.
    void Save();

    // Загружает число из памяти калькулятора в текущий результат.
    void Load();

    // Возвращает true, если ячейка памяти непустая.
    bool GetHasMem() const;

    // Возвращает текущее число, преобразуя его в std::string функцией
    // std::to_string.
    std::string GetNumberRepr() const;

private:
    Number result_;
    std::optional<Number> memory_;
};

template <class T>
inline void Calculator<T>::Set(T n) {
    result_ = n;
}

template <class T>
inline T Calculator<T>::GetNumber() const {
    return result_;
}

template <class T>
inline std::optional<Error> Calculator<T>::Add(T n) {
    result_ += n;

    return std::nullopt;
}

template <class T>
inline std::optional<Error> Calculator<T>::Sub(T n) {
    result_ -= n;

    return std::nullopt;
}

template <class T>
inline std::optional<Error> Calculator<T>::Div(T n) {
    if constexpr (std::is_integral_v<T> || std::is_same_v<T, Rational>) {
        if (n == 0) {
            return Error{"Division by zero"};
        }
    }

    result_ /= n;

    return std::nullopt;
}

template <class T>
inline std::optional<Error> Calculator<T>::Mul(T n) {
    result_ *= n;

    return std::nullopt;
}

template <typename T>
inline std::optional<Error> Calculator<T>::Pow(T n) {
    if (0 == n) {
        return Error{"Zero power to zero"};
    }

    if constexpr (std::is_same_v<T, int> || std::is_same_v<T, uint8_t> ||
                  std::is_same_v<T, size_t> || std::is_same_v<T, int64_t>) {
        if (0 > n) {
            return Error{"Integer negative power"};
        }

        result_ = IntegerPow<T>(result_, n);
    } else {
        result_ = std::pow(result_, n);
    }

    return std::nullopt;
}

template <>
inline std::optional<Error> Calculator<Rational>::Pow(Rational n) {
    if (0 == n) {
        return Error{"Zero power to zero"};
    }

    if (1 != n.GetDenominator()) {
        return Error{"Fractional power is not supported"};
    }

    result_ = ::Pow(result_, n);

    return std::nullopt;
}

template <class T>
inline void Calculator<T>::Save() {
    memory_ = result_;
}

template <class T>
inline void Calculator<T>::Load() {
    if (GetHasMem()) {
        result_ = memory_.value();
    }
}

template <class T>
inline bool Calculator<T>::GetHasMem() const {
    return std::nullopt != memory_;
}

#endif  // CALCULATOR_H
