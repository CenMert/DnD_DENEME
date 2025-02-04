#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <iostream>

#include "Player.h"
#include "Session.h"
#include "BaseDice.h"
#include "Dice.h"
#include <fstream>
#include <filesystem>
#include "json.hpp"

// For time operations
#include <iomanip>
#include <chrono>
#include <ctime>
#include <cctype>

using namespace std;
using json = nlohmann::json;

/*
A game class that will be used to hold the all information about the current game.
This class will hold all the players and sessions.

The game will be loaded this class's object and the game will be played using this object.

*/

class Game {
    //BIG3
public:
    Game() 
        : players(std::make_shared<std::vector<Player>>()),
        sessions(std::make_shared<std::vector<Session>>()),
        dices(std::make_shared<std::vector<BaseDice>>())
    {}
    Game(std::string gameName) 
        : gameName(gameName),
        players(std::make_shared<std::vector<Player>>()),
        sessions(std::make_shared<std::vector<Session>>()),
        dices(std::make_shared<std::vector<BaseDice>>())
    {}
    ~Game() {}
    Game operator=(const Game& g) {
        players = g.players;
        sessions = g.sessions;
        dices = g.dices;
        return *this;
    }
    Game(const Game& g) {
        players = g.players;
        sessions = g.sessions;
        dices = g.dices;
    }

    // getters
    std::shared_ptr < vector<Player> >&     getPlayers() { return players; }
    std::shared_ptr < vector<Session> >&    getSessions() { return sessions; }
    std::shared_ptr < vector<BaseDice> >&   getDices() { return dices; }
    std::string getGameName() { return gameName; }
    

    // setters
    void setPlayers(const std::vector<Player>& newPlayers) { *players = newPlayers; }
    void setSessions(const std::vector<Session>& newSessions) { *sessions = newSessions; }
    void setDices(const std::vector<BaseDice>& newDices) { *dices = newDices; }
    void setGameName(std::string name) { this->gameName = name; }

    // other functions
    void addPlayer(const Player& p) { players->push_back(p); }
    void addSession(const Session& s) { sessions->push_back(s); }

    //implemented in .cpp file
    void saveGame(std::string PlayersDir, std::string SessionsDir);

    // Extra
    void writeStoryToFile(const std::string& filename, const std::string& content);
    std::string getCurrentTimeISO8601();
private:
    std::string gameName;
    std::shared_ptr < vector< BaseDice  > >    dices; 
        // Lets limit that it can carry as most 10 dices.
        // 5 of them default, 5 of them custom
    std::shared_ptr < vector< Player    > >    players;
    std::shared_ptr < vector< Session   > >    sessions; // this will hold the sessions that are currently being played
    // you can find the sessions saved files in "sessions" folder


};

#endif