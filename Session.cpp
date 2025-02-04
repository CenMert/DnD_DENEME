#include "Session.h"
#include "json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

// Constructor Definitions
Session::Session(std::string sessionName, std::string sessionCreatedDate, std::vector<std::string> sessionText)
    : sessionName(sessionName), sessionCreatedDate(sessionCreatedDate), sessionText(sessionText) {}

Session::Session() {}

Session::~Session() {}

// Operator Overloading
Session& Session::operator=(const Session& s) {
    if (this == &s) return *this; // Prevent self-assignment
    sessionID = s.sessionID;
    sessionName = s.sessionName;
    sessionCreatedDate = s.sessionCreatedDate;
    sessionLastModifiedDate = s.sessionLastModifiedDate;
    sessionText = s.sessionText;
    return *this;
}

// Getters
int Session::getSessionID() const { return this->sessionID; }
std::string Session::getSessionName() const { return this->sessionName; }
std::string Session::getSessionDate() const { return this->sessionCreatedDate; }
std::string Session::getCreatedDate() const { return this->sessionCreatedDate; }
std::string Session::getLastModifiedDate() const { return this->sessionLastModifiedDate; }
std::vector<std::string> Session::getSessionText() const { return this->sessionText; }

// Setters
void Session::setSessionID(const int id) { sessionID = id; }
void Session::setCreatedDate(const std::string& date) { sessionCreatedDate = date; }
void Session::setLastModifiedDate(const std::string& date) { sessionLastModifiedDate = date; }
void Session::setSessionText(const std::vector<std::string>& text) { sessionText = text; }

// Save session to a JSON file
bool Session::saveToJsonFile(const std::string& directory) const {
    // Ensure the directory exists
    fs::create_directories(directory);

    // Construct file path
    std::string filePath = directory + "/" + sessionName + ".json";

    // Create JSON object
    json sessionJson;
    sessionJson["sessionID"] = sessionID;
    sessionJson["sessionName"] = sessionName;
    sessionJson["sessionCreatedDate"] = sessionCreatedDate;
    sessionJson["sessionLastModifiedDate"] = sessionLastModifiedDate;
    sessionJson["sessionText"] = sessionText;

    // Try writing to the file
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to create session JSON file at " << filePath << std::endl;
        return false;
    }

    outFile << sessionJson.dump(4); // Pretty-print JSON with indentation
    outFile.close();

    std::cout << "Session JSON file saved: " << filePath << std::endl;
    return true;
}

// Load session from a JSON file
bool Session::loadFromJsonFile(const std::string& filePath) {
    // Check if the file exists
    if (!fs::exists(filePath)) {
        std::cerr << "Error: File does not exist - " << filePath << std::endl;
        return false;
    }

    // Open the file for reading
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open session JSON file: " << filePath << std::endl;
        return false;
    }

    // Parse JSON data
    json sessionJson;
    try {
        inFile >> sessionJson;
    }
    catch (json::parse_error& e) {
        std::cerr << "Error: JSON parsing failed: " << e.what() << std::endl;
        return false;
    }
    inFile.close();

    // Assign values from JSON to Session attributes
    if (sessionJson.contains("sessionID")) sessionID = sessionJson["sessionID"].get<int>();
    if (sessionJson.contains("sessionName")) sessionName = sessionJson["sessionName"].get<std::string>();
    if (sessionJson.contains("sessionCreatedDate")) sessionCreatedDate = sessionJson["sessionCreatedDate"].get<std::string>();
    if (sessionJson.contains("sessionLastModifiedDate")) sessionLastModifiedDate = sessionJson["sessionLastModifiedDate"].get<std::string>();
    if (sessionJson.contains("sessionText")) sessionText = sessionJson["sessionText"].get<std::vector<std::string>>();

    std::cout << "Session loaded from: " << filePath << std::endl;
    return true;
}

// Other Functions
void Session::replaceSessionText(std::vector<std::string> newText) { this->sessionText = newText; }
void Session::addSessionText(std::string newText) { this->sessionText.push_back(newText); }
