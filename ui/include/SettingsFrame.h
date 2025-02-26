#pragma once
#include <wx/wx.h>
#include "MainMenuFrame.h"
class SettingsFrame : public wxFrame
{
public:
	SettingsFrame(wxWindow* parent);


private:
	void OnClose(wxCloseEvent& event);

	wxDECLARE_EVENT_TABLE();

	std::string fontStyle = "Papyrus";
	wxColour buttonColour = wxColour(166, 85, 28);
	wxColour backgroundColour = wxColour(204, 147, 114);
};

