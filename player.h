#pragma once
#include <iostream>
#include <string>
#include <vector>


using namespace std;


/*
Pure virtual player class for he player that will take their spcific classes whivh it will be derived from.
This file is implemented inline because it is a pure virtual class and it will not be used as a standalone class.

*/
class Player {
public:
    Player(string name, string characterName) : name(name), characterName(characterName) {}

    ~Player() {}

    Player operator=(const Player& p) {
        name = p.name;
        characterName = p.characterName;
        health = p.health;
        baseAttack = p.baseAttack;
        return *this;
    }

    // getters
    string getName() const { return name; }
    string getCharacterName() const { return characterName; }
    double getHealth() const { return health; }
    double getBaseAttack() const { return baseAttack; }

    // setters
    void setName(const string name) { this->name = name; }
    void setCharacterName(const string characterName) { this->characterName = characterName; }
    void setHealth(const double health) { this->health = health; }
    void setBaseAttack(const double baseAttack) { this->baseAttack = baseAttack; }

private:

    string name;
    string characterName;
    double health = 100.0; // this can be cahnged depending on the player class
    double baseAttack = 10.0;
    string story;
};
