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
    Session(
        int sessionID,
        std::string sessionName,
        std::string sessionCreatedDate,
        std::string sessionLastModifiedDate,
        std::string sessionTextFile,
        std::vector < std::string > sessionText
        );
    Session();
    ~Session();

    // Operator Overloading
    Session& operator=(const Session& s);

    // Getters
    int getSessionID() const { return this->sessionID; }
    std::string getSessionName() const { return this->sessionName; }
    std::string getSessionCreatedDate() const { return this->sessionCreatedDate; }
    std::string getSessionLastModifiedDate() const { return this->sessionLastModifiedDate; }
    std::string getSessionTextFile() const { return this->sessionTextFile; }
    std::vector<std::string> getSessionText() const { return this->sessionText; }

    // Setters
    void setSessionID(const int id);
    void setCreatedDate(const std::string& date);
    void setLastModifiedDate(const std::string& date);
    void setSessionText(const std::vector<std::string>& text);

    // Other Functions
    void replaceSessionText(std::vector<std::string> newText);
    void addSessionText(std::string newText);

    void display() const;

private:
    int sessionID; // Unique session identifier
    std::string sessionName;
    std::string sessionCreatedDate;
    std::string sessionLastModifiedDate;
    std::string sessionTextFile;
    std::vector<std::string> sessionText; // Session text logs
};

#endif
