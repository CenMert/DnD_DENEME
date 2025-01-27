#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "player.h"
#include "session.h"

using namespace std;
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
        sessions(std::make_shared<std::vector<Session>>())
    {}
    Game(std::string gameName) 
        : gameName(gameName),
        players(std::make_shared<std::vector<Player>>()),
        sessions(std::make_shared<std::vector<Session>>())
    {}
    ~Game() {}
    Game operator=(const Game& g) {
        players = g.players;
        sessions = g.sessions;
        return *this;
    }
    Game(const Game& g) {
        players = g.players;
        sessions = g.sessions;
    }

    // getters
    std::shared_ptr < vector<Player> >& getPlayers() { return players; }
    std::shared_ptr < vector<Session> >& getSessions() { return sessions; }
    std::string getGameName() { return gameName; }

    // setters
    void setPlayers(const std::vector<Player>& newPlayers) { *players = newPlayers; }
    void setSessions(const std::vector<Session>& newSessions) { *sessions = newSessions; }
    void setGameName(std::string name) { this->gameName = name; }

    // other functions
    void addPlayer(const Player& p) { players->push_back(p); }
    void addSession(const Session& s) { sessions->push_back(s); }

    //implemented in .cpp file
    void saveGame();
    void loadGame();

private:
    std::string gameName;
    std::shared_ptr < vector<Player> > players;
    std::shared_ptr < vector<Session> > sessions; // this will hold the sessions that are currently being played
    // you can find the sessions saved files in "sessions" folder


};

