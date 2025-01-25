#pragma once
#include "PlayFrame.h"
#include "game.h"
#include "player.h"
#include "session.h"

#include <string>
#include <wx/wx.h>


class GameFrame : public wxFrame
{
public:
	GameFrame(wxWindow* parent, wxString GameFolder);
private:
	wxDECLARE_EVENT_TABLE();

	void OnClose(wxCloseEvent& event);


	// setters
	void setGameFolder(const wxString GameFolder) { this->GameFolder = GameFolder; }
	void setGameDirectory(const wxString GameDirectory) { this->GameDir = GameDirectory; }
	void setPlayersDirectory() { this->PlayersDir = GameDir + "/players"; }
	void setSessionsDirectory() { this->SessionsDir = GameDir + "/sessions"; }

	// getters
	wxString getGameFolder() const { return this->GameFolder; }
	wxString getGameDirectory() const { return this->GameDir; }
	wxString getPlayersDirectory() const { return this->PlayersDir; }
	wxString getSessionsDirectory() const { return this->SessionsDir; }

	// folder functions
	void extractPlayersFromFolder();
	void extractSessionsFromFolder();

	// some constrains
	wxString GameFolder;
	wxString GameDir;
	wxString PlayersDir;
	wxString SessionsDir;

	std::shared_ptr<Game> game;

	std::string fontStyle = "Papyrus";
	wxColour buttonColour = wxColour(166, 85, 28);
	wxColour backgroundColour = wxColour(204, 147, 114);
};

