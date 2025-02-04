#ifndef PLAYER_H
#define PLAYER_H


#include <iostream>
#include <string>
#include <vector>

#include <wx/wx.h>   // Windows/wxWidgets header that eventually pulls in rpcndr.h

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
    Player();

    ~Player() {}

    Player operator=(const Player& p);

    // getters
    string getName() const;
    string getCharacterName() const;
    double getHealth() const;
    double getBaseAttack() const;
    string getStory() const;
    string getPathToJson() const;

    // setters
    void setName(const string &name);
    void setCharacterName(const string &characterName);
    void setHealth(const double health);
    void setBaseAttack(const double baseAttack);
    void setStory(const std::string &story);
    void setPathToJson(const std::string & path);

    //JSON Functions
    bool setJsonFileDefault(const std::string& theGame);
    bool saveToJsonFile(const std::string& theGame);
    bool copyFromJson(); // this will copy the content of an json file whic hold a player

    std::string sanitizeFilename(const std::string& input);

private:

    string name;
    string characterName;
    double health = 100.0; // this can be changed depending on the player class
    double baseAttack = 10.0;
    string story;

    // maybe i can have the directory of the json file to manage easily.
    string pathToJson;
};

#endif