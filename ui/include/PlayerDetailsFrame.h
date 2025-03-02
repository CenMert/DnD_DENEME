#pragma once
#include <wx/wx.h>
#include "Player.h"
#include "QuestionDialog.h"
#include <filesystem>

namespace fs = std::filesystem;
using json = nlohmann::json;

class PlayerDetailsFrame : public wxFrame
{
public:
	PlayerDetailsFrame(wxWindow* parent, Player* player);
	~PlayerDetailsFrame() {};

private:
	wxColour buttonColour = wxColour(166, 85, 28);
	wxColour backgroundColour = wxColour(204, 147, 114);

	Player* player;

	void On_SetPlayer_ButtonClicked(wxCommandEvent& event);
	std::string getTwoDigitAfterComma(double value);
};

