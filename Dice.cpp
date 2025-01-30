#include "dice.h"

// =============================
// Default Template Implementation (Numeric Dice)
// =============================

template <typename T>
Dice<T>::Dice(T min, T max) : min(min), max(max), gen(rd()) {}

template <typename T>
Dice<T>::~Dice() {}

template <typename T>
Dice<T>::Dice(const Dice& p) : min(p.min), max(p.max), gen(rd()) {}

template <typename T>
Dice<T>& Dice<T>::operator=(const Dice<T>& p) {
    if (this != &p) {
        min = p.min;
        max = p.max;
    }
    return *this;
}

template <typename T>
void Dice<T>::setDiceRange(T min, T max) {
    if (min > 0 && max > min) {
        this->min = min;
        this->max = max;
    }
}

template <typename T>
T Dice<T>::roll() {
    std::uniform_real_distribution<T> dist(min, max);
    return dist(gen);
}

// Explicit Instantiations
template class Dice<int>;
template class Dice<double>;

// =============================
// Specialization for Dice<std::string>
// =============================

Dice<std::string>::Dice() : gen(rd()) {}

Dice<std::string>::~Dice() {}

Dice<std::string>::Dice(const Dice& p) : options(p.options), gen(rd()) {}

Dice<std::string>& Dice<std::string>::operator=(const Dice<std::string>& p) {
    if (this != &p) {
        options = p.options;
    }
    return *this;
}

void Dice<std::string>::setOptions(const std::vector<std::string>& options) {
    this->options = options;
}

std::string Dice<std::string>::roll() {
    if (options.empty()) {
        return "No options set!";
    }

    std::uniform_int_distribution<int> dist(0, options.size() - 1);
    return options[dist(gen)];
}

// Explicit Specialization
template class Dice<std::string>;
