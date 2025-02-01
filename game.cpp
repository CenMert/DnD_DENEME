#include "game.h"
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

// Helper function to sanitize filenames
std::string sanitizeFilename(const std::string& input) {
    std::string output;
    // Only allow alphanumeric characters, dashes, underscores and periods.
    for (char c : input) {
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_' || c == '.') {
            output.push_back(c);
        }
        else {
            // Replace any other character with an underscore
            output.push_back('_');
        }
    }
    return output;
}

void Game::saveGame(std::string PlayersDir, std::string SessionsDir) {
    // Ensure the directories exist
    std::filesystem::create_directories(PlayersDir);
    std::filesystem::create_directories(SessionsDir);

    // Iterate over each player in the players vector
    for (const auto& player : *players) {
        // Create a JSON object for the player
        json playerJson;
        playerJson["name"] = player.getName();
        playerJson["characterName"] = player.getCharacterName();
        playerJson["health"] = player.getHealth();
        playerJson["baseAttack"] = player.getBaseAttack();
        playerJson["story"] = player.getStory();

        // Sanitize the player's name to create a safe filename
        std::string safePlayerName = sanitizeFilename(player.getName());
        // Use filesystem::path for safe path joining
        std::filesystem::path filePath = std::filesystem::path(PlayersDir) / (safePlayerName + ".json");

        // Write the JSON object to the file
        std::ofstream file(filePath);
        if (file.is_open()) {
            file << playerJson.dump(4); // Pretty print with 4 spaces indentation
            file.close();
        }
        else {
            std::cerr << "Failed to open file: " << filePath << std::endl;
        }
    }

    // Iterate over each session in the sessions vector
    for (const auto& session : *sessions) {
        json sessionJson;
        sessionJson["sessionID"] = session.getSessionID();
        sessionJson["sessionLastModifiedDate"] = getCurrentTimeISO8601();

        std::string content;
        // Iterate through the vector and append each string to the result
        for (const auto& str : session.getSessionText()) {
            content += str + "\n"; // Add a newline after each string
        }
        // Remove the trailing newline (if any)
        if (!content.empty() && content.back() == '\n') {
            content.pop_back();
        }

        // Sanitize the session name before using it as a filename
        std::string safeSessionName = sanitizeFilename(session.getSessionName());
        std::string sessionFilename = safeSessionName + ".txt";
        // Join the sessions directory and the sanitized filename
        std::filesystem::path sessionFilePath = std::filesystem::path(SessionsDir) / sessionFilename;

        writeStoryToFile(sessionFilePath.string(), content);
    }
}

std::string Game::getCurrentTimeISO8601() {
    // Get the current time point
    auto now = std::chrono::system_clock::now();

    // Convert the time point to a time_t (seconds since epoch)
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t to a tm structure (UTC time)
    std::tm now_tm;
#ifdef _WIN32
    // On Windows, use the secure version
    gmtime_s(&now_tm, &now_time_t);
#else
    // On non-Windows platforms, fallback to gmtime
    now_tm = *std::gmtime(&now_time_t);
#endif

    // Format the time as an ISO 8601 string
    char buffer[21]; // Buffer to hold the formatted time string
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &now_tm);

    return std::string(buffer);
}


// Function to write the story to a file
void Game::writeStoryToFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    file << content;
    file.close();
}
