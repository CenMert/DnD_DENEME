#pragma once
#include <wx/wx.h>
#include "MainMenuFrame.h"

#include <string>

class PlayFrame : public wxFrame
{
public:
	PlayFrame(wxWindow* parent);

private:
	void OnButtonChooseGameClicked(wxCommandEvent& evt);
	void On_NewGame_ButtonClicked(wxCommandEvent& event);

	void OnClose(wxCloseEvent& event);
	wxArrayString FindGameFolder();
	void OpenGame();


	// setter
	void setChoiceWindow(wxChoice* choiceWindow) { this->choiceWindow = choiceWindow; }
	void setSelectedGame(wxString selectedGame) { this->selectedGame = selectedGame; }

	// getter
	wxString getSelectedGame() { return this->selectedGame; }
	wxChoice* getChoiceWindow() { return this->choiceWindow; }

	wxDECLARE_EVENT_TABLE();

	wxChoice* choiceWindow; // Added seperately to use it on button clicked event
	wxString selectedGame;

	std::string fontStyle = "Papyrus";
	wxColour buttonColour = wxColour(166, 85, 28);
	wxColour backgroundColour = wxColour(204, 147, 114);


};

