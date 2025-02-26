#include "PlayFrame.h"
#include "GameFrame.h"
#include "QuestionDialog.h"
#include <filesystem> // to get names of the folders
#include <string>
namespace fs = std::filesystem;

enum IDs {
	ID_chooseGameChoices = 400,
	ID_chooseGameButton = 401
};

wxBEGIN_EVENT_TABLE(PlayFrame, wxFrame)
	EVT_BUTTON(ID_chooseGameButton, PlayFrame::OnButtonChooseGameClicked)
	EVT_CLOSE(PlayFrame::OnClose)
wxEND_EVENT_TABLE()

PlayFrame::PlayFrame(wxWindow* parent)
	: wxFrame(parent, wxID_ANY, "Play Window", wxDefaultPosition, wxSize(500, 400))
{


	// the icon operation that appears at the top of the window with its header.
	wxIcon appIcon;
	if (appIcon.LoadFile((fs::path("def_images") / "icos" / "poition2.ico").string(), wxBITMAP_TYPE_ICO)) { SetIcon(appIcon); }
	else { wxLogError("Icon File couldn't added to window."); }

	wxPanel* playPanel = new wxPanel(this);
	wxFont oldFont(
		18, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL,
		wxFONTWEIGHT_BOLD, false, fontStyle);

	wxArrayString choices = FindGameFolder();

	wxChoice* choiceWindow = new wxChoice(
		playPanel, ID_chooseGameChoices, 
		wxDefaultPosition, wxDefaultSize, choices
	); choiceWindow->SetFont(oldFont);

	choiceWindow->SetSelection(0);
	setChoiceWindow(choiceWindow);

	// To choose the selected Game Folder.
	// I will create a button and that button will trigger an event
	// event will run the function "OnButtonChooseGameClicked"
	wxButton* buttonChooseSelectedGame = new wxButton(
		playPanel, ID_chooseGameButton, "Open Selected Game", wxPoint(200, 300), wxSize(350, 50)
	); buttonChooseSelectedGame->SetFont(oldFont);

	wxButton* newGame = new wxButton(playPanel, wxID_ANY, "New Game");
	newGame->SetFont(oldFont);
	newGame->Bind(wxEVT_BUTTON, &PlayFrame::On_NewGame_ButtonClicked, this);

	// adjust them all in middle
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(buttonChooseSelectedGame, 0, wxALIGN_CENTER | wxTOP, 25);
	sizer->Add(choiceWindow, 0, wxALIGN_CENTER | wxTOP, 50);
	sizer->Add(newGame, 0, wxALIGN_CENTER | wxTOP, 50);

	// COLOURING
	buttonChooseSelectedGame->SetBackgroundColour(buttonColour);
	choiceWindow->SetBackgroundColour(buttonColour);
	playPanel->SetBackgroundColour(backgroundColour);

	playPanel->SetSizer(sizer);
	
	CreateStatusBar();
}

void PlayFrame::OnButtonChooseGameClicked(wxCommandEvent& evt)
{
	setSelectedGame(choiceWindow->GetStringSelection());

	if (selectedGame.IsEmpty()) {
		wxMessageBox("Please select a game folder before continuing!", "Error", wxICON_ERROR | wxOK);
		return;
	}

	OpenGame();
}

void PlayFrame::On_NewGame_ButtonClicked(wxCommandEvent& event)
{
	QuestionDialog QD(this, "onemsiz", "SO, GAME NAME?");
	std::string gameName;

	if (QD.ShowModal() == wxID_OK)
	{
		gameName = QD.GetAnswer();
	}

	fs::path newGamePath = fs::path("GameData") / gameName;

	fs::create_directory(newGamePath);
}

void PlayFrame::OnClose(wxCloseEvent& event)
{
	// Show the main menu again when closing settings
	if (GetParent()) {
		GetParent()->Show();
	}

	// Destroy this window
	this->Destroy();
}

wxArrayString PlayFrame::FindGameFolder()
{
	// Find Game Folders
	std::string path = "GameData";

	// Ensure the path exists and is a directory
	if (!fs::exists(path) || !fs::is_directory(path)) {
		wxLogError("GameData directory not found!");
		wxMessageBox("No Game Folder Found!");
	}
	wxArrayString choices;
	// Iterate through the directory contents
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.is_directory()) { // Check if it's a folder
			choices.Add(entry.path().filename().string());
		}
	}
	// END Find Game Folders
	return choices;
}

void PlayFrame::OpenGame()
{
	setSelectedGame(getChoiceWindow()->GetStringSelection());

	if (selectedGame.IsEmpty()) {
		wxMessageBox("No game selected!", "Error", wxICON_ERROR | wxOK);
		return;
	}

	// Otherwise, open the game window
	GameFrame* gameWindow = new GameFrame(this, getSelectedGame());
	gameWindow->Show();
	gameWindow->Center();

	// this->Hide(); // Hide PlayFrame while game is open
}