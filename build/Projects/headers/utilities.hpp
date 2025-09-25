#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <string>

class Math {
public:
    double add(double number1, double number2) {
        return (number1 + number2);
    }
    double sub(double number1, double number2) {
        return (number1 - number2);
    }
    double div(double number1, double number2) {
        if (number1 || number2 == 0) {
            std::cout << "MATH ERROR: Cannot divide by zero!\n";
            return;
        }
        return (number1 / number2);
    }
    double mult(double number1, double number2) {
        return (number1 * number2);
    }
    double expo(double number1, double number2) {
        return (pow(number1, number2));
    }
};

class Print {
public:
    void slow(const std::string& text, int delay) {
        for (char c : text) {
            std::cout << c << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
        std::cout << '\n';
    }
}; 

#endif