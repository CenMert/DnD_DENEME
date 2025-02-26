#include "Dice.h"

// Default constructor: delegates to the parameterized constructor with default values.
Dice::Dice()
    : Dice("default", 1, 6) // default dice type with range [1,6]
{
}

// Parameterized constructor: sets dice type and range.
// Seeds the random generator only once.
Dice::Dice(std::string DiceType, int range_begin, int range_end)
    : DiceType(DiceType), range_begin(range_begin), range_end(range_end), number(0)
{
    static bool seeded = false;
    if (!seeded)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }
}

std::string Dice::getDiceType()
{
    return this->DiceType;
}

// Destructor
Dice::~Dice()
{
    // No dynamic allocation to free
}

// Assignment operator
Dice& Dice::operator=(const Dice& other)
{
    if (this != &other)
    {
        this->DiceType = other.DiceType;
        this->range_begin = other.range_begin;
        this->range_end = other.range_end;
        this->number = other.number;
    }
    return *this;
}

// roll() method: Rolls the dice within the provided range and returns the result.
int Dice::roll()
{

    // Compute range size and generate random number.
    int rangeSize = this->range_end - this->range_begin + 1;
    number = std::rand() % rangeSize + this->range_begin;
    return number;
}