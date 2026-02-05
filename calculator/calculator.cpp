#include "calculator.h"

#include <cmath>
#include <iostream>
#include <string>

bool ReadNumber(Number& result) {
  bool is_ok{true};

  if (!(std::cin >> result)) {
    is_ok = false;
    std::cerr << "Error: Numeric operand expected" << std::endl;
  }

  return is_ok;
}

bool RunCalculatorCycle() {
  Number number{0};
  Number mem{0};
  bool used_mem{false};

  if (ReadNumber(number)) {
    // Основной цикл.
    std::string u_input{""};
    bool is_operation{false};
    const std::string s_legal_operation_symbols{"+-*/:"};
    enum class Operation : char { Plus, Minus, Mult, Div, Pow, Assign };
    Operation operation{};
    for (;;) {
      std::cin >> u_input;
      if (!is_operation) {
        if (s_legal_operation_symbols.find_first_of(u_input) !=
            std::string::npos) {
          if (u_input == "+") {
            operation = Operation::Plus;
          } else if (u_input == "-") {
            operation = Operation::Minus;
          } else if (u_input == "*") {
            operation = Operation::Mult;
          } else if (u_input == "/") {
            operation = Operation::Div;
          } else if (u_input == "**") {
            operation = Operation::Pow;
          } else if (u_input == ":") {
            operation = Operation::Assign;
          }

          is_operation = true;
        } else if (u_input == "q") {
          break;
        } else if (u_input == "=") {
          std::cout << number << std::endl;
        } else if (u_input == "c") {
          number = 0;
        } else if (u_input == "s") {
          mem = number;
          used_mem = true;
        } else if (u_input == "l") {
          if (used_mem) {
            number = mem;
          } else {
            std::cerr << "Error: Memory is empty" << std::endl;
            break;
          }
        } else {
          std::cerr << "Error: Unknown token " << u_input << std::endl;
          break;
        }
      } else {
        if (u_input[0] == '-' || std::isdigit(u_input[0])) {
          Number tmp{std::stod(u_input)};
          switch (operation) {
            case Operation::Plus:
              number += tmp;
              break;
            case Operation::Minus:
              number -= tmp;
              break;
            case Operation::Mult:
              number *= tmp;
              break;
            case Operation::Div:
              number /= tmp;
              break;
            case Operation::Pow:
              number = std::pow(number, tmp);
              break;
            case Operation::Assign:
              number = tmp;
              break;
          }

          is_operation = false;
        } else {
          std::cerr << "Error: Numeric operand expected" << std::endl;
          break;
        }
      }
    }
  }

  return true;
}
