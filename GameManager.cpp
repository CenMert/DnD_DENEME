#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include "json.hpp"  // Assuming you are using nlohmann/json

// color definitions for the errors.

namespace fs = std::filesystem;
using json = nlohmann::json;

GameManager::GameManager(const std::string& gameName)
    : game(std::make_shared<Game>()), gameName(gameName)
{
}

void GameManager::loadGame()
{
    fs::path player_path = fs::path("GameData") / this->gameName / "Players";
    fs::path session_path = fs::path("GameData") / this->gameName / "Sessions";

    // load the Player objects
    if (
        fs::exists(player_path) && fs::exists(session_path)
        )
    {
        
        for (const auto& file : fs::directory_iterator(player_path))
        {

            // key for the unordered_map items that holds the [key, Player] -> [playerKey, PlayerObject]
            std::string playerKey = file.path().stem().string();

            std::ifstream player_file(file.path());

            if (!player_file)
            {
                std::cerr << "Couldn't open file: " << playerKey << std::endl;
                continue;
            }

            json player_json_file;
            player_file >> player_json_file;

            // used private function
            Player PlayerObject = loadPlayerFromJson(player_json_file);

            if (this->game->addPlayer(playerKey, PlayerObject)) { 
                
                std::cout << playerKey << " is added to map." << std::endl;
            
            }

        } // player JSON load for loop end.

        /* Session operations

        unordered_map -> [session_key

        */
        // First pass: Process JSON files.
        for (auto& sessionDir : fs::directory_iterator(session_path)) {

            for (const auto& file : fs::directory_iterator(sessionDir)) {

                if (file.path().extension() == ".json") {

                    std::string sessionKey = file.path().stem().string();
                    std::ifstream session_file(file.path());
                    json session_json_file;
                    session_file >> session_json_file;

                    // Create the session
                    std::vector<std::string> vec;
                    Session SessionObject(
                        session_json_file["sessionID"].get<int>(),
                        session_json_file["sessionName"].get<std::string>(),
                        session_json_file["sessionCreatedDate"].get<std::string>(),
                        session_json_file["sessionLastModifiedDate"].get<std::string>(),
                        session_json_file["sessionTextFile"].get<std::string>(),
                        vec
                    );

                    this->game->addSession(sessionKey, SessionObject);
                }
            }
        }


        // Second pass: Process TXT files.
        for (auto& sessionDir : fs::directory_iterator(session_path)) {

            for (const auto& file : fs::directory_iterator(sessionDir)) {

                if (file.path().extension() == ".txt") {

                    std::string sessionKey = file.path().stem().string();
                    std::ifstream session_file(file.path());
                    std::vector<std::string> vec;
                    std::string line;

                    while (std::getline(session_file, line)) {
                        vec.push_back(line);
                    }

                    // Safely check if the session exists before updating.
                    auto sessions = this->game->getSessions();
                    if (sessions->find(sessionKey) != sessions->end()) {
                        sessions->at(sessionKey).setSessionText(vec);
                    }
                    else {
                        std::cerr << "Session key not found for TXT update: " << sessionKey << "\n";
                    }
                }
            }
        }


    }

}

void GameManager::saveGame() 
{
    // declare the paths
    fs::path player_path = fs::path("GameData") / this->gameName / "Players";
    fs::path session_path = fs::path("GameData") / this->gameName / "Sessions";

    try
    {

        if (
            fs::exists(player_path) && fs::exists(session_path)
            )
        {

            for (const auto& [name, player] : *this->getGame()->getPlayers())
            {
                std::string file = name + ".json";
                fs::path player_json_path = player_path / file;
                std::cout << "Saving the player " << name << "for the file in the path: " << player_json_path << std::endl;

                savePlayerToJson(player, player_json_path);
            }

            std::cout << "All players saved!" << std::endl;


            for (const auto& [name, session] : *this->getGame()->getSessions())
            {
                
                std::string file_json = name + ".json";
                std::string file_txt = name + ".txt";

                fs::path session_json_path = session_path / name / file_json;
                fs::path session_txt_path = session_path / name / file_txt;

                std::cout << "\n--Session JSON Path Is: " << session_json_path << "\n";
                std::cout << "\n--Session TXT Path Is: " << session_txt_path << "\n";

                saveSessionToJson_txt(session, session_json_path, session_txt_path);

            }

            std::cout << "All sessions saved!" << std::endl;

            std::cout << "Save operation is finished." << std::endl;

        }

    }
    catch (const std::exception&)
    {
        std::cout << "Problem has occured while saving the game" << std::endl;
    }

}

void GameManager::setGame(const std::string& Game)
{
    this->game->setGameName(Game);
}

std::shared_ptr<Game> GameManager::getGame()
{
    return this->game;
}


// Additional functions

void GameManager::savePlayerToJson(const Player& player, fs::path player_path) {

    json player_json_object;
    player_json_object["name"] = player.getName();
    player_json_object["characterName"] = player.getCharacterName();
    player_json_object["health"] = player.getHealth();
    player_json_object["baseAttack"] = player.getBaseAttack();
    player_json_object["story"] = player.getStory();

    std::ofstream exist_file(player_path);
    if (!exist_file.is_open())
    {
        std::cerr << "Error: Unable to create player JSON file at " << player_path << std::endl;
        return;
    }

    exist_file << player_json_object;
    exist_file.close();

    std::cout << "Player JSON file saved: " << player_path << std::endl;

}

void GameManager::saveSessionToJson_txt(const Session& session, fs::path json_path, fs::path txt_path) {

    json session_json_object;
    session_json_object["sessionID"] = session.getSessionID();
    session_json_object["sessionName"] = session.getSessionName();
    session_json_object["sessionCreatedDate"] = session.getSessionCreatedDate();
    session_json_object["sessionLastModifiedDate"] = session.getSessionLastModifiedDate();
    session_json_object["sessionTextFile"] = session.getSessionTextFile();

    std::ofstream json_file(json_path);
    std::ofstream txt_file(txt_path);

    if (!json_file.is_open() || !txt_file.is_open()) {  // FIXED: || instead of &&
        std::cerr << "Error: Unable to create session JSON or TXT file(s) at "
            << json_path << ", " << txt_path << std::endl;
        return;
    }

    json_file << session_json_object.dump(4);  // FIXED: Pretty-print JSON
    json_file.close();

    std::cout << "JSON Session file is saved successfully." << std::endl;

    for (const auto& line : session.getSessionText()) {
        txt_file << line << "\n";
    }

    txt_file.close();  // FIXED: Close txt_file

    std::cout << "TXT Session file is saved successfully." << std::endl;
}


Player GameManager::loadPlayerFromJson(nlohmann::json player_json_file)
{
    Player PlayerObject
    (
        player_json_file["name"         ].get<std::string>(),
        player_json_file["characterName"].get<std::string>(),
        player_json_file["baseAttack"   ].get<double>(),
        player_json_file["health"       ].get<double>(),
        player_json_file["story"        ].get<std::string>()
    );

    return PlayerObject;
}