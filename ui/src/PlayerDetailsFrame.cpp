#include "PlayerDetailsFrame.h"
#include <wx/statline.h>   // For wxStaticLine

PlayerDetailsFrame::PlayerDetailsFrame(wxWindow* parent, Player* player)
    : wxFrame(parent, wxID_ANY, "Player Information", wxPoint(0, 0), wxSize(500, 400)), player(player)
{
    std::string fontStyle = "Papyrus";
    wxFont oldFont(15, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, fontStyle);

    // panel for the palyers pixelated Photo
    wxPanel* topLeftPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(128, 128));
	
    // panel fot the players name and class
    wxPanel* topRightPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 128));
	
    // panel for the players detailed information and more options for feature details.
    wxPanel* bottomPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(428, 128));

    // sizer for 2 panel of top
    wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    wxSizer* bottomSizer = new wxBoxSizer(wxVERTICAL);

    topSizer->Add(topLeftPanel, 0, wxLEFT | wxRIGHT, 10);
	topSizer->Add(topRightPanel, 1, wxEXPAND | wxRIGHT, 10);
	bottomSizer->Add(bottomPanel, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    topLeftPanel->SetBackgroundColour(wxColour(238, 207, 128));
    topRightPanel->SetBackgroundColour(wxColour(233, 111, 46));
    bottomPanel->SetBackgroundColour(wxColour(233, 111, 46));
    
	mainSizer->Add(topSizer, 0, wxEXPAND | wxBOTTOM | wxTOP, 10);
    mainSizer->Add(bottomSizer, 1, wxEXPAND | wxBOTTOM, 10);

    // -------------------------------------
    // SIZER ADJUSTMENTS END
	// -------------------------------------

    // TODO this need to be changed depends on the player's image choice,
    // TODO add more images to the pp_images and configure related to the players

    wxInitAllImageHandlers();
    fs::path image_path = fs::path("def_images") / "pp_images" / "dragon.png";
    wxImage playerImage;
    if (!playerImage.LoadFile(image_path.string(), wxBITMAP_TYPE_PNG))
    {
        wxLogError("Failed to load image file.");
        // Handle error appropriately.
    }
    else if (!playerImage.IsOk())
    {
        wxLogError("Loaded image is not valid.");
        // Handle error.
    }
    wxBitmap playerBitmap(playerImage);
    wxStaticBitmap* playerBitmapPanel = new wxStaticBitmap(topLeftPanel, wxID_ANY, playerBitmap);
    wxSizer* topLeftPanel_sizer = new wxBoxSizer(wxVERTICAL);
    topLeftPanel_sizer->Add(playerBitmapPanel, 1, wxEXPAND | wxALL, 10);
    topLeftPanel->SetSizerAndFit(topLeftPanel_sizer);

    // -------------------------------------
    // IMAGE OPENING END 
    // -------------------------------------

	wxStaticText* playerName = new wxStaticText(topRightPanel, wxID_ANY, player->getName(), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	wxStaticText* playerCharacterName = new wxStaticText(topRightPanel, wxID_ANY, player->getCharacterName(), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	playerName->SetFont(oldFont);
	playerCharacterName->SetFont(oldFont);

	wxStaticText* playerBaseAttack = new wxStaticText(bottomPanel, wxID_ANY, 
        "Base Attack: " + getTwoDigitAfterComma(player->getBaseAttack()), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    playerBaseAttack->SetFont(oldFont);
	wxStaticText* playerHealth = new wxStaticText(bottomPanel, wxID_ANY, 
        "Health: " + getTwoDigitAfterComma(player->getHealth()), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	playerHealth->SetFont(oldFont);
	wxStaticText* playerStory = new wxStaticText(bottomPanel, wxID_ANY, "Story: " + player->getStory(), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    playerStory->SetFont(oldFont);
    this->SetSizerAndFit(mainSizer);

    wxSizer* topRightPanel_sizer = new wxBoxSizer(wxVERTICAL);
	topRightPanel_sizer->Add(playerName, 1, wxEXPAND | wxALL, 5);
	topRightPanel_sizer->Add(playerCharacterName, 1, wxEXPAND | wxALL, 5);

	wxSizer* bottomPanel_sizer = new wxBoxSizer(wxVERTICAL);
	bottomPanel_sizer->Add(playerBaseAttack, 1, wxEXPAND | wxALL, 10);
	bottomPanel_sizer->Add(playerHealth, 1, wxEXPAND | wxALL, 10);
	bottomPanel_sizer->Add(playerStory, 1, wxEXPAND | wxALL, 10);

	topRightPanel->SetSizerAndFit(topRightPanel_sizer);
    bottomPanel->SetSizerAndFit(bottomPanel_sizer);
}

void PlayerDetailsFrame::On_SetPlayer_ButtonClicked(wxCommandEvent& event)
{
    QuestionDialog setWhat(this, "onemsiz", 
        "What do you want to set?\n1->name\n2->character name\n3->base attack\n4->health\n5->story");
    int value = 0;
    if (setWhat.ShowModal() == wxID_OK) {
        value = std::stoi(std::string(setWhat.GetAnswer().mb_str()));
    }
    else
    {
        wxMessageBox("Operation Failed.");
        return;
    }

    switch (value)
    {
    case 1:
    {
        QuestionDialog nameD(this, "onemsiz", "Set Name");
        if (nameD.ShowModal() == wxID_OK) {
            std::string answer = nameD.GetAnswer().ToStdString();
            this->player->setName(answer);
        }
        break;
    }

    case 2:
    {
        QuestionDialog characterNameD(this, "onemsiz", "Set Character Name");
        if(characterNameD.ShowModal()==wxID_OK){
            std::string answer = characterNameD.GetAnswer().ToStdString();
            this->player->setCharacterName(answer);
        }
        break;
    }

    case 3:
    {
        QuestionDialog baseAttackD(this, "onemsiz", "Set Base Attack - only integer or double!");
        if(baseAttackD.ShowModal() == wxID_OK){
            std::string answer = baseAttackD.GetAnswer().ToStdString();
            this->player->setBaseAttack(std::stod(answer));
        }
        break;
    }

    case 4:
    {
        QuestionDialog healthD(this, "onemsiz", "Set Health - only integer or double!");
        if(healthD.ShowModal() == wxID_OK){
            std::string answer = healthD.GetAnswer().ToStdString();
            this->player->setHealth(std::stod(answer));
        }
        break;
    }

    case 5:
    {
        QuestionDialog storyD(this, "onemsiz", "Set Story");
        if(storyD.ShowModal() == wxID_OK){
            std::string answer = storyD.GetAnswer().ToStdString();
            this->player->setStory(answer);
        }
        break;
    }

    default:
        wxMessageBox("Invalid Number!");
        break;
    }

}

std::string PlayerDetailsFrame::getTwoDigitAfterComma(double value)
{
	std::string temp = std::to_string(value);
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] == '.')
		{
			if (temp.size() - i > 2)
			{
				return temp.substr(0, i + 3);
			}
			else
			{
				return temp;
			}
		}
	}
}
