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
    Game() {}
    Game(std::string gameName) : gameName(gameName) {};
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
    vector<Player> getPlayers() { return players; }
    vector<Session> getSessions() { return sessions; }
    std::string getGameName() { return gameName; }

    // setters
    void setPlayers(vector<Player> players) { this->players = players; }
    void setSessions(vector<Session> sessions) { this->sessions = sessions; }
    void setGameName(std::string name) { this->gameName = name; }

    // other functions
    void addPlayer(Player p) { players.push_back(p); }
    void addSession(Session s) { sessions.push_back(s); }

    //implemented in .cpp file
    void saveGame();
    void loadGame();

private:
    std::string gameName;
    vector<Player> players;
    vector<Session> sessions; // this will hold the sessions that are currently being played
    // you can find the sessions saved files in "sessions" folder


};

