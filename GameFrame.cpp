#include "GameFrame.h"
#include "player.h"
#include "session.h"
#include "json.hpp"

#include <string>
#include <vector>

enum Game_IDs {
	ID_TopHeader = 2
};

wxBEGIN_EVENT_TABLE(GameFrame, wxFrame)
	EVT_CLOSE(GameFrame::OnClose)
wxEND_EVENT_TABLE()

GameFrame::GameFrame(wxWindow* parent, wxString GameFolder)
	: wxFrame(parent, wxID_ANY, "The Game"), game(std::make_shared<Game>(GameFolder.ToStdString()))
{
	// Configure all the directory elements to use later
	const std::string GameDirectory = "GameData/" + GameFolder.ToStdString();
	setGameFolder(GameFolder);
	setGameDirectory(GameDirectory);
	setPlayersDirectory();
	setSessionsDirectory();

	wxFont oldFont(18, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, fontStyle);
	wxPanel* gamePanel = new wxPanel(this);

	wxStaticText* topHeader = new wxStaticText(gamePanel, ID_TopHeader,
		("Game Panel : " +  this->GameFolder), 
		wxDefaultPosition, wxDefaultSize 
	);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(topHeader, 0, wxALIGN_LEFT | wxTOP, 50);

	topHeader->SetFont(oldFont);

	gamePanel->SetBackgroundColour(backgroundColour);
	gamePanel->SetSizer(sizer);


	/*
	Gamer object operations:
		I will create an Game object.
		Add all the players and sessions from the folders
	
	*/
	this->game->setGameName(GameFolder.ToStdString());
	extractPlayersFromFolder();
	extractSessionsFromFolder();


	
	CreateStatusBar();
}

void GameFrame::OnClose(wxCloseEvent& event)
{
	// Show the main menu again when closing settings
	if (GetParent()) {
		GetParent()->Show();
	}

	// Destroy this window
	this->Destroy();
}

// Implement this and use it for players
// This will search for the player json files and adds created player objects to the 
// this->game->players which is a vector<Player>
// HANDLE WITH SMART POINTERS
void GameFrame::extractPlayersFromFolder()
{
}

// Does the same thing as extractPlayerFromFolder
// HANDLE WITH SMART POINTERS
void GameFrame::extractSessionsFromFolder()
{
}

