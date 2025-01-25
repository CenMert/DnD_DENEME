#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "player.h"

using namespace std;

class Session {
public:
    //BIG3
    Session(string sessionName, string sessionCreatedDate, string sessionText) : sessionName(sessionName), sessionCreatedDate(sessionCreatedDate), sessionText(sessionText) {}
    ~Session() {}
    Session operator=(const Session& s) {
        sessionName = s.sessionName;
        sessionCreatedDate = s.sessionCreatedDate;
        sessionText = s.sessionText;
        return *this;
    }

    // getters
    string getSessionName() { return sessionName; }
    string getSessionDate() { return sessionCreatedDate; }
    string getSessionText() { return sessionText; }

    // setters
    void setSessionName(string sessionName) { this->sessionName = sessionName; }
    void setSessionDate(string sessionDate) { this->sessionCreatedDate = sessionDate; }
    void setSessionText(string sessionText) { this->sessionText = sessionText; }

    // other functions
    void recplaceSessionText(string newText) { sessionText = newText; }
    void addSessionText(string newText) { sessionText += newText; }

private:
    static int sessionID; // this will be used to identify the session
    string sessionName = { "Session " + to_string(sessionID++) };
    string sessionCreatedDate;
    string sessionLastEditedDate;
    string sessionText; // this is the text what had happended in the session
};