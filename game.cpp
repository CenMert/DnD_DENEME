#include "Game.h"

// Add a player only if they don�t already exist
bool Game::addPlayer(const std::string& fileName, const Player& p) {
    // If the players map is not initialized, allocate it.
    if (!players) {
        this->players = std::make_shared<std::unordered_map<std::string, Player>>();
    }

    // Attempt to insert the player.
    // The insert() method returns a pair: 
    // - first: an iterator to the inserted element (or the element that prevented the insertion)
    // - second: a bool that is true if insertion took place, false otherwise.
    auto [iter, inserted] = players->insert({fileName, p});

    // inserted is true if the element was added (i.e., fileName did not already exist in the map)
    return inserted;
}

// Retrieve a player
Player* Game::getPlayer(const std::string& name) {
    auto it = players->find(name);
    if (it != players->end()) {
        return &(it->second);
    }
    return nullptr;
}

// Remove a player
void Game::removePlayer(const std::string& name) {
    players->erase(name);
}

// Add a session only if it doesn�t already exist
bool Game::addSession(const std::string& fileName, const Session& s) {
        // If the players map is not initialized, allocate it.
    if (!this->sessions) {
        this->sessions = std::make_shared<std::unordered_map<std::string, Session>>();
    }

    // Attempt to insert the session.
    // The insert() method returns a pair: 
    // - first: an iterator to the inserted element (or the element that prevented the insertion)
    // - second: a bool that is true if insertion took place, false otherwise.
    auto [iter, inserted] = sessions->insert({fileName, s});

    // inserted is true if the element was added (i.e., fileName did not already exist in the map)
    return inserted;
}
// Remove a session
void Game::removeSession(const std::string& name) {
    sessions->erase(name);
}
