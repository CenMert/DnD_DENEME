#include "GameFrame.h"
#include "MapFrame.h"
#include "PlayerDetailsFrame.h"
#include "player.h"
#include "session.h"
#include "json.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

// Define custom event IDs
enum Game_IDs {
	ID_TopHeader = 2,
	ID_SideButtonPanel = 3,
	ID_MapButton = 4,
	ID_AddPlayerButton = 5,
	ID_SaveButton = 6,
	ID_LoadButton = 7,
	ID_TextEditor = 8,

	ID_SaveForNewSessionButton = 9
};

// Color and size settings
wxColour buttonColour = wxColour(166, 85, 28);
wxColour backgroundColour = wxColour(204, 147, 114);
wxColour playerCardBGColour = wxColour(227, 208, 61);
wxSize SidePanelButtonSize = wxSize(100, 25);
wxSize DynamicTextSize = wxSize(600, 400);
wxSize PlayerCardSize = wxSize(200, 100);
wxSize PlayerCardButtonSize = wxSize(80, 25);

GameFrame::GameFrame(wxWindow* parent, wxString GameFolder)
	: wxFrame(parent, wxID_ANY, "The Game", wxDefaultPosition, wxSize(1280, 720)),
	game(std::make_shared<Game>(GameFolder.ToStdString()))
{
	setGameFolder(GameFolder);
	setGameDirectory("GameData/" + GameFolder.ToStdString());
	setPlayersDirectory();
	setSessionsDirectory();

	wxPanel* gamePanel = new wxPanel(this);
	gamePanel->SetBackgroundColour(backgroundColour);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Header
	wxStaticText* topHeader = new wxStaticText(gamePanel, ID_TopHeader, "Game Panel: " + GameFolder, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	wxFont oldFont(18, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	topHeader->SetFont(oldFont);
	mainSizer->Add(topHeader, 0, wxALIGN_CENTER | wxTOP, 10);

	wxBoxSizer* contentSizer = new wxBoxSizer(wxHORIZONTAL);

	// Left Panel (Buttons)
	wxPanel* SidePanelButton = new wxPanel(gamePanel);
	SidePanelButton->SetMinSize(wxSize(100, 400));
	SidePanelButton->SetBackgroundColour(backgroundColour);

	wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
	wxButton* MapButton = new wxButton(SidePanelButton, ID_MapButton, "Map", wxDefaultPosition, SidePanelButtonSize);
	wxButton* AddPlayerButton = new wxButton(SidePanelButton, ID_AddPlayerButton, "+Player", wxDefaultPosition, SidePanelButtonSize);
	wxButton* SaveButton = new wxButton(SidePanelButton, ID_SaveButton, "Save", wxDefaultPosition, SidePanelButtonSize);
	wxButton* LoadButton = new wxButton(SidePanelButton, ID_LoadButton, "Load", wxDefaultPosition, SidePanelButtonSize);
	wxButton* SaveForNewSessionButton = new wxButton(SidePanelButton, ID_SaveForNewSessionButton, "Save for\nnew Session", wxDefaultPosition, wxSize(100, 35));

	leftSizer->Add(MapButton, 0, wxEXPAND | wxALL, 5);
	leftSizer->Add(AddPlayerButton, 0, wxEXPAND | wxALL, 5);
	leftSizer->Add(SaveButton, 0, wxEXPAND | wxALL, 5);
	leftSizer->Add(LoadButton, 0, wxEXPAND | wxALL, 5);
	leftSizer->Add(SaveForNewSessionButton, 0, wxEXPAND | wxALL, 5);

	MapButton->SetBackgroundColour(buttonColour);
	AddPlayerButton->SetBackgroundColour(buttonColour);
	SaveButton->SetBackgroundColour(buttonColour);
	LoadButton->SetBackgroundColour(buttonColour);
	SaveForNewSessionButton->SetBackgroundColour(buttonColour);

	SidePanelButton->SetSizer(leftSizer);
	contentSizer->Add(SidePanelButton, 0, wxEXPAND | wxALL, 5);

	// Center Panel (Text Editor)
	wxPanel* DynamicTextPanel = new wxPanel(gamePanel);
	DynamicTextPanel->SetMinSize(DynamicTextSize);
	DynamicTextPanel->SetBackgroundColour(backgroundColour);

	wxBoxSizer* CenterSizer = new wxBoxSizer(wxVERTICAL);
	this->textEditor = new wxTextCtrl(DynamicTextPanel, ID_TextEditor, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	this->textEditor->SetBackgroundColour(*wxBLACK);
	this->textEditor->SetForegroundColour(*wxWHITE);

	CenterSizer->Add(this->textEditor, 1, wxEXPAND | wxALL, 5);
	DynamicTextPanel->SetSizer(CenterSizer);
	contentSizer->Add(DynamicTextPanel, 1, wxEXPAND | wxALL, 5);

	// Right Panel (Player Cards with Scroll)
	wxScrolledWindow* PlayerCardPanel = new wxScrolledWindow(gamePanel, wxID_ANY, wxDefaultPosition, wxSize(200, 400), wxVSCROLL);
	PlayerCardPanel->SetScrollRate(5, 5);
	wxBoxSizer* playerSizer = new wxBoxSizer(wxVERTICAL);

	extractPlayersFromFolder();
	extractSessionsFromFolder();

	this->Players = game->getPlayers();
	this->Sessions = game->getSessions();

	size_t playersLen = Players->size();

	// Sample players (Replace with dynamic loading)
	for (size_t i = 0; i < playersLen; i++) {
		wxPanel* playerCard = new wxPanel(PlayerCardPanel);
		playerCard->SetMinSize(PlayerCardSize);
		playerCard->SetBackgroundColour(playerCardBGColour);

		wxBoxSizer* cardSizer = new wxBoxSizer(wxVERTICAL);
		wxStaticText* playerName = new wxStaticText(
			playerCard, wxID_ANY, Players->at(i).getName(), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
		wxButton* PlayerDetailsButton = new wxButton(
			playerCard, wxID_ANY, "Details", wxDefaultPosition, PlayerCardButtonSize);

		PlayerDetailsButton->Bind(wxEVT_BUTTON, &GameFrame::OnPlayerDetailsButtonClicked, this);

		cardSizer->Add(playerName, 0, wxALIGN_CENTER | wxTOP, 5);
		cardSizer->Add(PlayerDetailsButton, 0, wxALIGN_CENTER | wxBOTTOM, 5);
		playerCard->SetSizer(cardSizer);
		playerSizer->Add(playerCard, 0, wxEXPAND | wxALL, 5);
	}

	// Button binding for left side panel.
	LoadButton->Bind(wxEVT_BUTTON, &GameFrame::OnLoadButtonClicked, this);
	SaveButton->Bind(wxEVT_BUTTON, &GameFrame::OnSaveButtonClicked, this);
	MapButton->Bind(wxEVT_BUTTON, &GameFrame::OnMapButtonClicked, this);

	PlayerCardPanel->SetSizer(playerSizer);
	contentSizer->Add(PlayerCardPanel, 0, wxEXPAND | wxALL, 5);

	mainSizer->Add(contentSizer, 1, wxEXPAND | wxALL, 5);
	gamePanel->SetSizer(mainSizer);

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

void GameFrame::SetGameObject()
{
	/*
Gamer object operations:
	I will create an Game object.
	Add all the players and sessions from the folders

*/
	this->game->setGameName(this->GameFolder.ToStdString());
	extractPlayersFromFolder();
	extractSessionsFromFolder();
	// We have all the required the data for the creating deeper windows?
}

// Button Click Area Start

void GameFrame::OnPlayerDetailsButtonClicked(wxCommandEvent& evt)
{
	/*	Lets assume we catch the player we want to see its details.
		We will create a new window and show the details of the player.
		I want to show a png Profile Picture of the player. Just near of it, with the big puntos
			name of the player
			character name
			and the race.

		Under the big photos, There will be the additional informations like health zart zurt.
		And the story of the player. if possible we can make it italic or bold.
	*/
	wxMessageBox("Opening details for: " + this->selectedPlayer->getName(), "Player Details", wxOK | wxICON_INFORMATION);

	// Open the details window
	PlayerDetailsFrame* detailsFrame = new PlayerDetailsFrame(this, this->selectedPlayer);
	detailsFrame->Show();
	
}

void GameFrame::OnLoadButtonClicked(wxCommandEvent& evt)
{
	wxLogStatus("Load Button Clicked");

	if (this->Sessions->empty()) {
		wxLogError("No sessions available to load.");
		return;
	}

	// Create a list of available sessions
	wxArrayString sessionChoices;
	std::vector<int> sessionIDs;
	for ( auto& session : *this->Sessions) {
		sessionChoices.Add(wxString::Format("Session %d", session.getSessionID()));
		sessionIDs.push_back(session.getSessionID());
	}

	// Show a session selection dialog
	int selection = wxGetSingleChoiceIndex("Select a session to load", "Load Session", sessionChoices);
	if (selection == wxNOT_FOUND) {
		wxLogStatus("Session load canceled.");
		return;
	}

	int selectedSessionID = sessionIDs[selection];

	// Find the selected session
	auto it = std::find_if(this->Sessions->begin(), this->Sessions->end(),
		[selectedSessionID](const Session& s) { return s.getSessionID() == selectedSessionID; });

	if (it == this->Sessions->end()) {
		wxLogError("Failed to find the selected session.");
		return;
	}

	// Get session text
	std::vector<std::string> sessionText = it->getSessionText();
	std::string fullText = "";
	for (const auto& line : sessionText) {
		fullText += line + "\n";
	}

	// Set the content to the text editor
	this->textEditor = dynamic_cast<wxTextCtrl*>(FindWindowById(ID_TextEditor, this));
	if (this->textEditor) {
		this->textEditor->SetValue(fullText);
	}
	else {
		wxLogError("Failed to find the text editor.");
	}
}

// there can be a 2 option to save which one is saving the current editing session or creating a difeerent session object
// then add it to the sessions folder.
void GameFrame::OnSaveButtonClicked(wxCommandEvent& evt)
{

}

void GameFrame::OnNewSessionSaveButtonClicked(wxCommandEvent& evt)
{
	wxLogStatus("Save Button Clicked");

	wxString theTextInTheTextCtrl = this->textEditor->GetValue();
	std::vector<std::string> sessionText;
	std::istringstream textStream(theTextInTheTextCtrl.ToStdString());
	std::string line;
	while (std::getline(textStream, line)) {
		sessionText.push_back(line);
	}

	// Create a new session object
	Session newSession;
	newSession.setSessionID(this->Sessions->size() + 1);

	// get the time and date
	time_t now = time(0);
	tm* ltm = localtime(&now);

	// create session object to fill the session object
	newSession.setCreatedDate(std::to_string(1900 + ltm->tm_year) + "/" + std::to_string(1 + ltm->tm_mon) + "/" + std::to_string(ltm->tm_mday));
	newSession.setLastModifiedDate(std::to_string(1900 + ltm->tm_year) + "/" + std::to_string(1 + ltm->tm_mon) + "/" + std::to_string(ltm->tm_mday));
	newSession.setSessionText(sessionText);

	// Add the session to the game object
	this->game->addSession(newSession);


}

void GameFrame::OnAddPlayerButtonClicked(wxCommandEvent& evt)
{
}

void GameFrame::OnMapButtonClicked(wxCommandEvent& evt) {
	// reach the directroy of the game files. Find map.png file and show it on a different page
	// that will not close the Game page.

	/*
	*The image is in the GameData/<GameFolder>/maps/<name_of_the_map>
	*For now there are just one map called DnD_Battel_Map.png
	*/

	// Find the map file
	std::string mapPath = this->GameDir.ToStdString() + "/maps/DnD_Battle_Map.png";
	if (!fs::exists(mapPath)) {
		wxLogError("Map file not found: %s", mapPath);
		return;
	}

	// Create a new map frame
	MapFrame* mapFrame = new MapFrame(this, mapPath);
	mapFrame->Show();

	// wxLogMessage("Implement this, a problem about byte zart zurt!");
}

// Button Click Area End

// Implement this and use it for players
// This will search for the player json files and adds created player objects to the 
// this->game->players which is a vector<Player>
// HANDLE WITH SMART POINTERS
void GameFrame::extractPlayersFromFolder() {
	if (!fs::exists(this->PlayersDir.ToStdString()) || !fs::is_directory(this->PlayersDir.ToStdString())) {
		wxLogError("Players directory does not exist: %s", this->PlayersDir);
		return;
	}

	for (const auto& entry : fs::directory_iterator(this->PlayersDir.ToStdString())) {
		if (entry.path().extension() == ".json") {
			std::ifstream file(entry.path());
			if (!file.is_open()) {
				wxLogError("Failed to open player file: %s", entry.path().string());
				continue;
			}

			json playerJson;
			file >> playerJson;
			file.close();

			try {
				Player p;
				p.setName(playerJson["name"].get<std::string>());
				p.setCharacterName(playerJson["characterName"].get<std::string>());
				p.setHealth(playerJson["health"].get<double>());
				p.setBaseAttack(playerJson["baseAttack"].get<double>());
				p.setStory(playerJson["story"].get<std::string>());

				game->addPlayer(p);
			}
			catch (const std::exception& e) {
				wxLogError("Error parsing player JSON file: %s", e.what());
			}
		}
	}
}

// Does the same thing as extractPlayerFromFolder
// HANDLE WITH SMART POINTERS
void GameFrame::extractSessionsFromFolder() {
	if (!fs::exists(this->SessionsDir.ToStdString()) || !fs::is_directory(this->SessionsDir.ToStdString())) {
		wxLogError("Sessions directory does not exist: %s", this->SessionsDir);
		return;
	}

	for (const auto& entry : fs::directory_iterator(this->SessionsDir.ToStdString())) {
		if (entry.path().extension() == ".json") {
			std::ifstream file(entry.path());
			if (!file.is_open()) {
				wxLogError("Failed to open session JSON file: %s", entry.path().string());
				continue;
			}

			json sessionJson;
			try {
				file >> sessionJson;
			}
			catch (const json::parse_error& e) {
				wxLogError("JSON parsing error in file %s: %s", entry.path().string(), e.what());
				continue;
			}
			file.close();

			try {
				if (!sessionJson.contains("sessionID") ||
					!sessionJson.contains("sessionCreatedDate") ||
					!sessionJson.contains("sessionLastModifiedDate") ||
					!sessionJson.contains("sessionTextFile")) {

					wxLogError("Missing fields in session JSON file: %s", entry.path().string());
					continue;
				}

				// Creating a session object
				Session s;
				s.setSessionID(sessionJson["sessionID"].get<int>());
				s.setCreatedDate(sessionJson["sessionCreatedDate"].get<std::string>());
				s.setLastModifiedDate(sessionJson["sessionLastModifiedDate"].get<std::string>());

				// Read session text from the specified file
				std::string textFilePath = this->SessionsDir.ToStdString() + "/" + sessionJson["sessionTextFile"].get<std::string>();
				std::ifstream textFile(textFilePath);

				if (!textFile.is_open()) {
					wxLogError("Failed to open session text file: %s", textFilePath);
					continue;
				}

				std::vector<std::string> sessionText;
				std::string line;
				while (std::getline(textFile, line)) {
					sessionText.push_back(line);
				}
				textFile.close();

				s.setSessionText(sessionText);
				this->game->addSession(s);

				// wxLogMessage("Successfully added session: %d", s.getSessionID());
			}
			catch (const std::exception& e) {
				wxLogError("Error processing session file: %s", e.what());
			}
		}
	}
}