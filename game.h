#ifndef GAME_H
#define GAME_H

#include <string>
#include <unordered_map>
#include <memory>
#include "Player.h"
#include "Session.h"
#include "BaseDice.h"
#include "Dice.h"
#include <fstream>
#include <filesystem>
#include "json.hpp"

class Game {
public:
    Game()
        : players(std::make_shared<std::unordered_map<std::string, Player>>()),
        sessions(std::make_shared<std::unordered_map<std::string, Session>>()),
        dices(std::make_shared<std::vector<BaseDice>>()) {}

    Game(std::string gameName)
        : gameName(gameName),
        players(std::make_shared<std::unordered_map<std::string, Player>>()),
        sessions(std::make_shared<std::unordered_map<std::string, Session>>()),
        dices(std::make_shared<std::vector<BaseDice>>()) {}

    ~Game() {}

    // Getters
    std::shared_ptr<std::unordered_map<std::string, Player>>& getPlayers() { return this->players; }
    std::shared_ptr<std::unordered_map<std::string, Session>>& getSessions() { return this->sessions; }
    std::shared_ptr<std::vector<BaseDice>>& getDices() { return this->dices; }
    std::string getGameName() const { return gameName; }

    // Setters
    void setGameName(const std::string& name) { this->gameName = name; }

    // Player Management
    bool addPlayer(const std::string& fileName, const Player& p);
    Player* getPlayer(const std::string& name);
    void removePlayer(const std::string& name);

    // Session Management
    bool addSession(const std::string& fileName, const Session& s);
    // Session* getSession(const std::string& name);
    void removeSession(const std::string& name);

private:
    std::string gameName;
    std::shared_ptr<std::unordered_map<std::string, Player>> players;
    std::shared_ptr<std::unordered_map<std::string, Session>> sessions;
    std::shared_ptr<std::vector<BaseDice>> dices;
};

#endif
