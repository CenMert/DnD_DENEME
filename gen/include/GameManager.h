#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Game.h"
#include <memory>
#include <fstream>
#include <filesystem>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

class GameManager {
public:
    GameManager( const std::string& gameName );

    // Game Lifecycle
    void loadGame();
    void saveGame();

    void setGame(const std::string& Game);

    // Additional functions for the save operation
    void savePlayerToJson(const Player& player, fs::path player_path);
    void saveSessionToJson_txt(const Session& session, fs::path json_path, fs::path txt_path);

    std::shared_ptr<Game> getGame();

private:
    std::shared_ptr<Game> game;
    std::string gameName;




    Player loadPlayerFromJson(nlohmann::json player_json_file);
};

#endif
