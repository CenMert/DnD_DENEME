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
	~GameFrame() {};
private:

	// On Close
	void OnClose(wxCloseEvent& event);

	// Main Panel
	void SetGameObject();

	// Button Clicks
	void OnAddPlayerButtonClicked(wxCommandEvent& evt);
	void OnMapButtonClicked(wxCommandEvent& evt);
		// Im not sure whether this will work for all player details button
	void OnPlayerDetailsButtonClicked(wxCommandEvent& evt);
	void OnLoadButtonClicked(wxCommandEvent& evt);
	void OnSaveButtonClicked(wxCommandEvent& evt);

	void OnNewSessionSaveButtonClicked(wxCommandEvent& evt);

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
	// Example Folder Hierarcy
	/*
		-GameData/
			|-Game1/
				|-players/
					|-Berke.json
					|-Serhat.json
				|-sessions/
					|-session1.json
					|-session1.txt
					|-session2.json
					|-session2.txt
				|-maps/
					|-DnD_Battle_Map.png
	*/

	wxString GameFolder;	// Game1
	wxString GameDir;		// GameData/Game1
	wxString PlayersDir;	// GameData/Game1/players
	wxString SessionsDir;	// GameData/Game1/sessions

	std::shared_ptr<Game> game;
	std::shared_ptr< vector<Player> > Players;
	std::shared_ptr< vector<Session> > Sessions;

	std::string fontStyle = "Papyrus";
	wxColour buttonColour = wxColour(166, 85, 28);
	wxColour backgroundColour = wxColour(204, 147, 114);
	
	// Text Editor to handle it on load and save functions
	wxTextCtrl* textEditor;
	Player* selectedPlayer;

};

