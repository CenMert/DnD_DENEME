#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include "json.hpp" // Include nlohmann/json

class Session {
public:
    // Constructors and Destructor
    Session(std::string sessionName, std::string sessionCreatedDate, std::vector<std::string> sessionText);
    Session();
    ~Session();

    // Operator Overloading
    Session& operator=(const Session& s);

    // Getters
    int getSessionID() const;
    std::string getSessionName() const;
    std::string getSessionDate() const;
    std::string getCreatedDate() const;
    std::string getLastModifiedDate() const;
    std::vector<std::string> getSessionText() const;

    // Setters
    void setSessionID(const int id);
    void setCreatedDate(const std::string& date);
    void setLastModifiedDate(const std::string& date);
    void setSessionText(const std::vector<std::string>& text);

    // File Handling Functions
    bool saveToJsonFile(const std::string& directory) const;
    bool loadFromJsonFile(const std::string& filePath);

    // Other Functions
    void replaceSessionText(std::vector<std::string> newText);
    void addSessionText(std::string newText);

private:
    int sessionID; // Unique session identifier
    std::string sessionName;
    std::string sessionCreatedDate;
    std::string sessionLastModifiedDate;
    std::vector<std::string> sessionText; // Session text logs
};

#endif
