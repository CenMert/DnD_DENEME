#pragma once
#include <stdlib.h>
#include <ctime>
#include <string>

class Dice
{
public:
	Dice();
	~Dice();
	Dice& operator=(const Dice& other);

	Dice(std::string DiceType, int range_begin, int range_end);

	std::string getDiceType();

	int roll();

private:
	std::string DiceType;
	int range_begin;
	int range_end;
	int number;
};