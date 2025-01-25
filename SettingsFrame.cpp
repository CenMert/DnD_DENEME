#include "SettingsFrame.h"

enum Settings_IDs {
	ID_sound = 300
};

wxBEGIN_EVENT_TABLE(SettingsFrame, wxFrame)
	EVT_CLOSE(SettingsFrame::OnClose)
wxEND_EVENT_TABLE()

SettingsFrame::SettingsFrame(wxWindow* parent) : 
	wxFrame(parent, wxID_ANY, "Settings")
{
	wxFont oldFont(18, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, fontStyle);

	// Sound Slider Text
	wxPanel* SettingsPanel = new wxPanel(this);
	wxStaticText* soundSliderText = new wxStaticText(
		SettingsPanel, wxID_ANY, "Sound", wxDefaultPosition, wxDefaultSize
	); soundSliderText->SetFont(oldFont);

	// Sound Slider
	wxSlider* soundSlider = new wxSlider(
		SettingsPanel, ID_sound, 50, 0, 100, wxDefaultPosition, wxDefaultSize
		); 

	// Box Sizer to adjust all in middle.
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(soundSlider, 0, wxALIGN_CENTER | wxTOP, 25);
	sizer->Add(soundSliderText, 0, wxALIGN_CENTER | wxTOP, 50);

	SettingsPanel->SetBackgroundColour(backgroundColour);
	SettingsPanel->SetSizer(sizer);


	CreateStatusBar();
}

void SettingsFrame::OnClose(wxCloseEvent& event)
{
	// Show the main menu again when closing settings
	if (GetParent()) {
		GetParent()->Show();
	}

	// Destroy this window
	this->Destroy();
}