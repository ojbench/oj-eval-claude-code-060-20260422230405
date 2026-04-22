#pragma once
#include <vector>

// Template struct for the validator chain
template <typename T>
struct Validator {
    const T& value;
    bool negate_next = false;
    bool result = true;

    Validator(const T& val) : value(val) {}

    // Convert to bool - called when used in if statements
    operator bool() const {
        return result;
    }

    // Chainable methods for comparisons
    Validator& toBe(const T& other) {
        bool condition = (value == other);
        if (negate_next) condition = !condition;
        result = result && condition;
        return *this;
    }

    Validator& toBeOneOf(const std::vector<T>& container) {
        bool found = false;
        for (const auto& item : container) {
            if (value == item) {
                found = true;
                break;
            }
        }
        bool condition = found;
        if (negate_next) condition = !condition;
        result = result && condition;
        return *this;
    }

    Validator& le(const T& other) {
        bool condition = (value <= other);
        if (negate_next) condition = !condition;
        result = result && condition;
        return *this;
    }

    Validator& ge(const T& other) {
        bool condition = (value >= other);
        if (negate_next) condition = !condition;
        result = result && condition;
        return *this;
    }

    Validator& lt(const T& other) {
        bool condition = (value < other);
        if (negate_next) condition = !condition;
        result = result && condition;
        return *this;
    }

    Validator& gt(const T& other) {
        bool condition = (value > other);
        if (negate_next) condition = !condition;
        result = result && condition;
        return *this;
    }

    // Method to negate subsequent conditions
    Validator& Not() {
        negate_next = !negate_next;
        return *this;
    }
};

// Factory function to start the chain
template <typename T>
Validator<T> expect(const T& value) {
    return Validator<T>(value);
