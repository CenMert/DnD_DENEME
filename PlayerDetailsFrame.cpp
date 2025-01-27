#include "PlayerDetailsFrame.h"

PlayerDetailsFrame::PlayerDetailsFrame(wxWindow* parent, Player* player)
	: wxFrame(parent, wxID_ANY, "Player Informations", wxDefaultPosition, wxDefaultSize),
	player(player)
{
	wxPanel* mainPanel = new wxPanel(this);
	mainPanel->SetBackgroundColour(backgroundColour);
	
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Name & CharName
	wxStaticText* Name = new wxStaticText(mainPanel, wxID_ANY, player->getName(), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	wxStaticText* CharName = new wxStaticText(mainPanel, wxID_ANY, player->getCharacterName(), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	wxFont oldFont(18, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	Name->SetFont(oldFont);
	CharName->SetFont(oldFont);
	mainSizer->Add(Name, 0, wxLEFT | wxTOP, 10);
	mainSizer->Add(CharName, 0, wxLEFT | wxTOP, 10);

	// Other details

}
