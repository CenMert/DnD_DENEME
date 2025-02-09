#ifndef PLAYER_H
#define PLAYER_H


#include <iostream>
#include <string>
#include <vector>

// Undefine the conflicting 'byte' from Windows headers.
#ifdef byte
#undef byte
#endif

#include "json.hpp"
#include <fstream>
#include <filesystem>

using namespace std;

class Player {
public:
    Player(string name, string characterName);
    Player(string name, string characterName, double baseAttack, double health, string story);
    Player();

    ~Player() {}

    Player& operator=(const Player& p);

    // getters
    string getName() const;
    string getCharacterName() const;
    double getHealth() const;
    double getBaseAttack() const;
    string getStory() const;

    // setters
    void setName(const string &name);
    void setCharacterName(const string &characterName);
    void setHealth(const double health);
    void setBaseAttack(const double baseAttack);
    void setStory(const std::string &story);

    void display() const ;
private:

    string name;
    string characterName;
    double health = 100.0; // this can be changed depending on the player class
    double baseAttack = 10.0;
    string story;

    // maybe i can have the directory of the json file to manage easily.
    string fileName;
};

#endif