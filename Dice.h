/*
This Dice class will be used as seperate objects.
You can use it for multiple dice options and different classes.

I aimed to create a flexible Dice class to roll anything I want.
*/
#pragma once

#include "BaseDice.h"
#include "player.h"
#include "session.h"
#include "game.h"

#include <vector>
#include <string>
#include <random>

template <typename T>
class Dice : public BaseDice
{
public:
    Dice(T min = 1, T max = 6); // Default to D6 for numeric types
    ~Dice();
    Dice(const Dice& p);
    Dice& operator=(const Dice& p);

    void setDiceRange(T min, T max);
    T roll();

private:
    std::random_device rd;
    std::mt19937 gen;
    T min;
    T max;
};

// Specialization for Dice<std::string>
template <>
class Dice<std::string>
{
public:
    Dice();
    ~Dice();
    Dice(const Dice& p);
    Dice& operator=(const Dice& p);

    void setOptions(const std::vector<std::string>& options);
    std::string roll();

private:
    std::random_device rd;
    std::mt19937 gen;
    std::vector<std::string> options;
};
