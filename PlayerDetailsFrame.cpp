#include "PlayerDetailsFrame.h"

PlayerDetailsFrame::PlayerDetailsFrame(wxWindow* parent, Player* player)
	: wxFrame(parent, wxID_ANY, "Player Informations", wxDefaultPosition, wxSize(500, 400)), player(player)
{
	// wxFrame için panel oluþtur
	wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
	mainPanel->SetBackgroundColour(backgroundColour);

	// Ana düzenleyici (Sizer)
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	// Font ayarlarý
	wxFont boldFont(14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	// Oyuncu Adý ve Karakter Adý
	wxStaticText* Name = new wxStaticText(mainPanel, wxID_ANY, "Name: " + player->getName(), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* CharName = new wxStaticText(mainPanel, wxID_ANY, "Character: " + player->getCharacterName(), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	Name->SetFont(boldFont);
	CharName->SetFont(boldFont);

	// Saðlýk ve Saldýrý Gücü
	wxStaticText* health = new wxStaticText(mainPanel, wxID_ANY, "Health: " + std::to_string(player->getHealth()), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxStaticText* baseAttack = new wxStaticText(mainPanel, wxID_ANY, "Base Attack: " + std::to_string(player->getBaseAttack()), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);

	// Hikaye (Salt okunur ve sabit boyutlu)
	wxTextCtrl* storyBox = new wxTextCtrl(mainPanel, wxID_ANY, player->getStory(),
		wxDefaultPosition, wxSize(450, 120), wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
	storyBox->SetBackgroundColour(wxColour(230, 230, 230)); // Hafif gri arka plan

	// Bileþenleri `mainSizer` içerisine ekleyelim
	mainSizer->Add(Name, 0, wxLEFT | wxTOP, 10);
	mainSizer->Add(CharName, 0, wxLEFT | wxTOP, 5);
	mainSizer->Add(health, 0, wxLEFT | wxTOP, 5);
	mainSizer->Add(baseAttack, 0, wxLEFT | wxTOP, 5);
	mainSizer->Add(storyBox, 0, wxEXPAND | wxALL, 10); // Expand olmadan sabit boyut

	// Panelin sizer'ýný ayarlayalým
	mainPanel->SetSizer(mainSizer);


	// Ana Frame'e paneli ekleyelim
	this->SetClientSize(mainPanel->GetSize());

	// Frame’in boyutunu ayarla ve sizer'ý kullan
	this->Fit();
}
