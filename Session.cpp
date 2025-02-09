#include "Session.h"
#include "json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

// Constructor Definitions
Session::Session(
    int sessionID,
    std::string sessionName,
    std::string sessionCreatedDate,
    std::string sessionLastModifiedDate,
    std::string sessionTextFile,
    std::vector < std::string > sessionText
) 
:
    sessionID(sessionID),
    sessionName(sessionName),
    sessionCreatedDate(sessionCreatedDate),
    sessionLastModifiedDate(sessionLastModifiedDate),
    sessionTextFile(sessionTextFile),
    sessionText(sessionText)
    {}


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

// Setters
void Session::setSessionID(const int id) { sessionID = id; }
void Session::setCreatedDate(const std::string& date) { sessionCreatedDate = date; }
void Session::setLastModifiedDate(const std::string& date) { sessionLastModifiedDate = date; }
void Session::setSessionText(const std::vector<std::string>& text) { sessionText = text; }

// Other Functions
void Session::replaceSessionText(std::vector<std::string> newText) { this->sessionText = newText; }
void Session::addSessionText(std::string newText) { this->sessionText.push_back(newText); }

void Session::display() const
{
    std::cout << "DISPLAYING A SESSION" << "\n\n";
    std::cout <<
        "Session ID: " << this->sessionID << "\n" <<
        "Created Date: " << this->sessionCreatedDate << "\n" <<
        "Last Modified Date: " << this->sessionLastModifiedDate << "\n" <<
        "Text File: " << this->sessionTextFile << "\n";
    std::string line;
    for (std::string l : this->sessionText) { line += l + "\n"; }
        std::cout << "The Text: " << line << "\n";
}
