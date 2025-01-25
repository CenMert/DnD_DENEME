#pragma once
#include <wx/wx.h>
#include <string>
/*
	SETTINGS: SettingsFrame
		this opens settings window classic.

	PLAY: PlayFrame
		this opens play window
		we can choose game, session, player etc.
		Im planning that after choosing the Game sesion;
			I will Open the main window to operate everything
			Players etc.
			Editable Text for the session.

*/

class MainMenuFrame : public wxFrame
{
public:
	MainMenuFrame(const wxString& title);
private:
	void OnButtonPlayClicked(wxCommandEvent& evt);
	void OnButtonSettingsClicked(wxCommandEvent& evt);

	// Settings
	void OpenSettings();
	void OpenPlay();

	wxDECLARE_EVENT_TABLE();

	std::string fontStyle = "Papyrus";
	wxColour buttonColour = wxColour(166, 85, 28);
	wxColour backgroundColour = wxColour(204, 147, 114);
};

