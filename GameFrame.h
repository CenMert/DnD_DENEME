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

	// On Close
	void OnClose(wxCloseEvent& event);

	// Main Panel
	void SetGameObject();

	// Button Clicks
	void OnAddPlayerButtonClicked(wxCommandEvent& evt);
	void OnMapButtonClicked(wxCommandEvent& evt);
		// Im not sure whether this will work for all player details button
	void OnPlayerDetailsButtonClicked(wxCommandEvent& evt);

	// setters
	void setGameFolder(const wxString GameFolder) { this->GameFolder = GameFolder; }
	void setGameDirectory(const wxString GameDirectory) { this->GameDir = GameDirectory; }
	void setPlayersDirectory() { this->PlayersDir = this->GameDir + "/" + "players"; }
	void setSessionsDirectory() { this->SessionsDir = this->GameDir + "/" + "sessions"; }

	// getters
	wxString getGameFolder() const { return this->GameFolder; }
	wxString getGameDirectory() const { return this->GameDir; }
	wxString getPlayersDirectory() const { return this->PlayersDir; }
	wxString getSessionsDirectory() const { return this->SessionsDir; }

	// folder functions
	void extractPlayersFromFolder();
	void extractSessionsFromFolder();

	// some constrains
	wxString GameFolder;	// Game1
	wxString GameDir;		// GameData/Game1
	wxString PlayersDir;	// GameData/Game1/players
	wxString SessionsDir;	// GameData/Game1/sessions

	std::shared_ptr<Game> game;

	std::string fontStyle = "Papyrus";
	wxColour buttonColour = wxColour(166, 85, 28);
	wxColour backgroundColour = wxColour(204, 147, 114);
	wxStaticText* dynamicText; // WTF??
		
		// These sizes are just experimental
	wxSize SidePanelButtonSize = wxSize(10, 10);
	wxSize DynamicTextSize = wxSize(300, 400);
	wxSize PlayerCardSize = wxSize(100, 50);
	wxSize PlayerCardButtonSize = wxSize(25, 10);

};

