#include "GameFrame.h"
#include "player.h"
#include "session.h"
#include "json.hpp"

#include <filesystem>  // For directory iteration
#include <fstream>     // For file reading

namespace fs = std::filesystem;
using json = nlohmann::json;

#include <string>
#include <vector>
#include <sstream>

enum Game_IDs {
	ID_TopHeader = 2,
	ID_SideButtonPanel = 3,
	ID_MapButton = 4,
	ID_AddPlayerButton = 5
};

wxBEGIN_EVENT_TABLE(GameFrame, wxFrame)
	EVT_CLOSE(GameFrame::OnClose)
	// Add clicked events
wxEND_EVENT_TABLE()

GameFrame::GameFrame(wxWindow* parent, wxString GameFolder)
	: wxFrame(parent, wxID_ANY, "The Game", wxDefaultPosition, wxSize(1280, 720)),
	game(std::make_shared<Game>(GameFolder.ToStdString()))
{
	// Configure all the directory elements to use later
	const wxString GameDirectory = "GameData/" + GameFolder.ToStdString();
	setGameFolder(GameFolder);
	setGameDirectory(GameDirectory);
	setPlayersDirectory();
	setSessionsDirectory();

	wxFont oldFont(18, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, fontStyle);
	wxPanel* gamePanel = new wxPanel(this);

	wxStaticText* topHeader = new wxStaticText(gamePanel, ID_TopHeader,
		("Game Panel : " + this->GameFolder),
		wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER
	);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(topHeader, 0, wxALIGN_CENTER | wxTOP, 10);

	topHeader->SetFont(oldFont);

	gamePanel->SetBackgroundColour(backgroundColour);
	gamePanel->SetSizer(mainSizer);
	SetGameObject(); // Configure the game object

	/*
		Updated Layout
	*/

	wxPanel* SidePanelButton = new wxPanel(gamePanel);
	wxPanel* DynamicTextPanel = new wxPanel(gamePanel);
	wxPanel* PlayerCardPanel = new wxPanel(gamePanel);
	wxPanel* PlayerCardButtonPanel = new wxPanel(PlayerCardPanel);

	// Set custom sizes for the panels
	SidePanelButton->SetMinSize(SidePanelButtonSize);
	DynamicTextPanel->SetMinSize(DynamicTextSize);
	PlayerCardPanel->SetMinSize(PlayerCardSize);
	PlayerCardButtonPanel->SetMinSize(PlayerCardButtonSize);

	// Set the colours
	SidePanelButton->SetBackgroundColour(backgroundColour);
	DynamicTextPanel->SetBackgroundColour(backgroundColour);
	PlayerCardPanel->SetBackgroundColour(backgroundColour);

	wxBoxSizer* contentSizer = new wxBoxSizer(wxHORIZONTAL);
	contentSizer->Add(SidePanelButton, 0, wxEXPAND | wxALL, 5);
	contentSizer->Add(DynamicTextPanel, 1, wxEXPAND | wxALL, 5); // Adjustable
	contentSizer->Add(PlayerCardPanel, 0, wxEXPAND | wxALL, 5);

	mainSizer->Add(contentSizer, 1, wxEXPAND | wxALL, 5);

	// Side panel için minimum genişlik belirleyelim
	SidePanelButton->SetMinSize(wxSize(75, 400)); // Genişlik 200px, yükseklik 400px olarak ayarlandı

	// SidePanelButton içine butonları ekleyelim
	wxButton* MapButton = new wxButton(
		SidePanelButton, ID_MapButton, "Map",
		wxDefaultPosition, wxDefaultSize); // Buton boyutunu varsayılan bırak (kendi içeriğine göre ayarlanır)

	wxButton* AddPlayerButton = new wxButton(
		SidePanelButton, ID_AddPlayerButton, "+Player",
		wxDefaultPosition, wxDefaultSize); // ID'yi düzelttik

	// Side panel için bir sizer oluştur ve butonları ekle
	wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
	leftSizer->Add(MapButton, 0, wxEXPAND | wxALL, 5);
	leftSizer->Add(AddPlayerButton, 0, wxEXPAND | wxALL, 5);

	// SidePanelButton’a sizer’ı ata
	SidePanelButton->SetSizer(leftSizer);
	SidePanelButton->Layout(); // UI'yı güncelle
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

				wxLogMessage("Successfully added session: %d", s.getSessionID());
			}
			catch (const std::exception& e) {
				wxLogError("Error processing session file: %s", e.what());
			}
		}
	}
}


