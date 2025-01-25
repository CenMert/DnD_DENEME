#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "player.h"

using namespace std;

class Session {
public:
    //BIG3
    Session(string sessionName, string sessionCreatedDate, vector<string> sessionText) : sessionName(sessionName), sessionCreatedDate(sessionCreatedDate), sessionText(sessionText) {}
    Session() {};
    ~Session() {}
    Session operator=(const Session& s) {
        sessionName = s.sessionName;
        sessionCreatedDate = s.sessionCreatedDate;
        sessionText = s.sessionText;
        return *this;
    }

    // getters
    int getSessionID() { return sessionID; }
    string getSessionName() { return sessionName; }
    string getSessionDate() { return sessionCreatedDate; }
    vector<string> getSessionText() { return sessionText; }

    // setters
    void setSessionID(const int id) { sessionID = id; }
    void setCreatedDate(const std::string& date) { sessionCreatedDate = date; }
    void setLastModifiedDate(const std::string& date) { sessionLastModifiedDate = date; }
    void setSessionText(const std::vector<std::string>& text) { sessionText = text; }


    // other functions
    void recplaceSessionText(vector<string> newText) { this->sessionText = newText; }
    void addSessionText(string newText) { this->sessionText.push_back(newText) ; }

private:
    int sessionID; // this will be used to identify the session
    string sessionName;
    string sessionCreatedDate;
    string sessionLastModifiedDate;
    std::vector<std::string> sessionText; // this is the text what had happended in the session
};