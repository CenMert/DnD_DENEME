#include "Player.h"


using json = nlohmann::json;
namespace fs = std::filesystem;

Player::Player(string name, string characterName) : name(name), characterName(characterName) {}

Player::Player()
{
	this->name = "-NO NAME-";
	this->characterName = "-NO NAME-";
	this->health = 100;
	this->baseAttack = 10;
	this->story = "-NO STORY-";
	this->pathToJson = "-NO PATH-";
}

Player Player::operator=(const Player& p)
{
	this->name = p.getName();
	this->characterName = p.getCharacterName();
	this->baseAttack = p.getBaseAttack();
	this->health = p.getHealth();
	this->story = p.getStory();
	this->pathToJson = p.getPathToJson();

    return *this;
}

string Player::getName() const { return this->name; }

string Player::getCharacterName() const { return this->characterName; }

double Player::getHealth() const { return this->health; }

double Player::getBaseAttack() const { return this->baseAttack; }

string Player::getStory() const { return this->story; }

string Player::getPathToJson() const { return this->pathToJson; }

void Player::setName(const string& name) { this->name = name; }

void Player::setCharacterName(const string& characterName) { this->characterName = characterName; }

void Player::setHealth(const double health) { this->health = health; }

void Player::setBaseAttack(const double baseAttack) { this->baseAttack = baseAttack; }

void Player::setStory(const std::string& story) { this->story = story; }

void Player::setPathToJson(const std::string &path) { this->pathToJson = path; }

// Function to create and set a default JSON file for the player
bool Player::setJsonFileDefault(const std::string &theGame) {
    // Ensure the directory exists
    std::string directory = "GameData/" + theGame + "/Players"; // Change this if needed
    fs::create_directories(directory);

    // Construct file path using player's name
    std::string sanitizedName = name.empty() ? "default" : name;
    std::string filePath = directory + "/" + sanitizedName + ".json";
    pathToJson = filePath; // Store path for later reference

    // Create JSON object with default values
    json playerJson;
    playerJson["name"] = "_NO NAME_";
    playerJson["characterName"] = "_NO CH NAME_";
    playerJson["health"] = 100;
    playerJson["baseAttack"] = 10;
    playerJson["story"] = "_NO STORY_";

    // Try writing to the file
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to create player JSON file at " << filePath << std::endl;
        return false;
    }

    outFile << playerJson.dump(4); // Pretty-print JSON with indentation
    outFile.close();

    std::cout << "Player JSON file created successfully: " << filePath << std::endl;
    return true;
}

// Function to ensure filenames are safe (removes invalid characters)
std::string Player::sanitizeFilename(const std::string& input) {
    std::string output;
    for (char c : input) {
        if (std::isalnum(c) || c == '-' || c == '_') {
            output.push_back(c);
        }
        else {
            output.push_back('_'); // Replace invalid characters
        }
    }
    return output;
}

// Save player data to JSON file
bool Player::saveToJsonFile(const std::string& theGame) {
    // Ensure the directory exists
    std::string directory = "GameData/" + theGame + "/Players"; // Game-specific folder
    fs::create_directories(directory);

    // Construct file path using sanitized player's name
    std::string sanitizedName = sanitizeFilename(name.empty() ? "default" : name);
    std::string filePath = directory + "/" + sanitizedName + ".json";
    pathToJson = filePath; // Store path for reference

    // Create JSON object
    json playerJson;
    playerJson["name"] = name;
    playerJson["characterName"] = characterName;
    playerJson["health"] = health;
    playerJson["baseAttack"] = baseAttack;
    playerJson["story"] = story;

    // Try writing to the file
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to create player JSON file at " << filePath << std::endl;
        return false;
    }

    outFile << playerJson.dump(4); // Pretty-print JSON with indentation
    outFile.close();

    std::cout << "Player JSON file saved: " << filePath << std::endl;
    return true;
}

bool Player::copyFromJson() 
{
    // Create a file dialog to select the JSON file
    wxFileDialog openFileDialog(
        nullptr, "Select Player JSON File", "", "",
        "JSON files (*.json)|*.json",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    // If the user cancels, return false
    if (openFileDialog.ShowModal() != wxID_OK) {
        return false;
    }

    // Get the selected file path
    std::string filePath = openFileDialog.GetPath().ToStdString();
    pathToJson = filePath;  // Store for future reference

    // Open the file for reading
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open player JSON file: " << filePath << std::endl;
        return false;
    }

    // Parse JSON data
    json playerJson;
    try {
        inFile >> playerJson;
    }
    catch (json::parse_error& e) {
        std::cerr << "Error: JSON parsing failed: " << e.what() << std::endl;
        return false;
    }
    inFile.close();

    // Assign values from JSON to Player attributes
    if (playerJson.contains("name")) name = playerJson["name"].get<std::string>();
    if (playerJson.contains("characterName")) characterName = playerJson["characterName"].get<std::string>();
    if (playerJson.contains("health")) health = playerJson["health"].get<double>();
    if (playerJson.contains("baseAttack")) baseAttack = playerJson["baseAttack"].get<double>();
    if (playerJson.contains("story")) story = playerJson["story"].get<std::string>();

    std::cout << "Player data loaded from: " << filePath << std::endl;
    return true;
}



