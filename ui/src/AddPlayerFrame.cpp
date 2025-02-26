#include "AddPlayerFrame.h"
#include <wx/msgdlg.h>
#include <stdexcept>

AddPlayerFrame::AddPlayerFrame(wxWindow* parent, std::shared_ptr<GameManager> GM)
    : wxFrame(parent, wxID_ANY, "Who is that new adventurer?", wxDefaultPosition, wxSize(500, 700)),
    GM(GM)
{
    // Main panel and sizer
    wxPanel* MainPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    MainPanel->SetSizer(mainSizer);

    // Name Panel
    wxPanel* NamePanel = new wxPanel(MainPanel, wxID_ANY);
    wxBoxSizer* nameSizer = new wxBoxSizer(wxHORIZONTAL);
    NamePanel->SetSizer(nameSizer);
    wxStaticText* nameLabel = new wxStaticText(NamePanel, wxID_ANY, "Name:");
    nameCtrl = new wxTextCtrl(NamePanel, wxID_ANY, wxEmptyString);
    nameSizer->Add(nameLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    nameSizer->Add(nameCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(NamePanel, 0, wxEXPAND | wxALL, 5);

    // Character Name Panel
    wxPanel* CNamePanel = new wxPanel(MainPanel, wxID_ANY);
    wxBoxSizer* cnameSizer = new wxBoxSizer(wxHORIZONTAL);
    CNamePanel->SetSizer(cnameSizer);
    wxStaticText* cnameLabel = new wxStaticText(CNamePanel, wxID_ANY, "Character Name:");
    cnameCtrl = new wxTextCtrl(CNamePanel, wxID_ANY, wxEmptyString);
    cnameSizer->Add(cnameLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    cnameSizer->Add(cnameCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(CNamePanel, 0, wxEXPAND | wxALL, 5);

    // Health Panel
    wxPanel* HealthPanel = new wxPanel(MainPanel, wxID_ANY);
    wxBoxSizer* healthSizer = new wxBoxSizer(wxHORIZONTAL);
    HealthPanel->SetSizer(healthSizer);
    wxStaticText* healthLabel = new wxStaticText(HealthPanel, wxID_ANY, "Health:");
    healthCtrl = new wxTextCtrl(HealthPanel, wxID_ANY, wxEmptyString);
    healthSizer->Add(healthLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    healthSizer->Add(healthCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(HealthPanel, 0, wxEXPAND | wxALL, 5);

    // Base Attack Panel
    wxPanel* BAttackPanel = new wxPanel(MainPanel, wxID_ANY);
    wxBoxSizer* battackSizer = new wxBoxSizer(wxHORIZONTAL);
    BAttackPanel->SetSizer(battackSizer);
    wxStaticText* battackLabel = new wxStaticText(BAttackPanel, wxID_ANY, "Base Attack:");
    battackCtrl = new wxTextCtrl(BAttackPanel, wxID_ANY, wxEmptyString);
    battackSizer->Add(battackLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    battackSizer->Add(battackCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(BAttackPanel, 0, wxEXPAND | wxALL, 5);

    // Story Panel (multiline text)
    wxPanel* StoryPanel = new wxPanel(MainPanel, wxID_ANY);
    wxBoxSizer* storySizer = new wxBoxSizer(wxHORIZONTAL);
    StoryPanel->SetSizer(storySizer);
    wxStaticText* storyLabel = new wxStaticText(StoryPanel, wxID_ANY, "Story:");
    storyCtrl = new wxTextCtrl(StoryPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    storySizer->Add(storyLabel, 0, wxALIGN_TOP | wxALL, 5);
    storySizer->Add(storyCtrl, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(StoryPanel, 1, wxEXPAND | wxALL, 5);

    // Create button at the bottom
    wxButton* createButton = new wxButton(MainPanel, wxID_ANY, "Create");
    createButton->Bind(wxEVT_BUTTON, &AddPlayerFrame::On_Create_ButtonClicked, this);
    mainSizer->Add(createButton, 0, wxALIGN_CENTER | wxALL, 10);

    MainPanel->Layout();
}

void AddPlayerFrame::On_Create_ButtonClicked(wxCommandEvent& event)
{
    // Retrieve the current values from the text controls when the button is clicked.
    this->name = nameCtrl->GetValue().ToStdString();
    this->cname = cnameCtrl->GetValue().ToStdString();
    this->story = storyCtrl->GetValue().ToStdString();

    try {
        this->health = std::stod(healthCtrl->GetValue().ToStdString());
        this->battack = std::stod(battackCtrl->GetValue().ToStdString());
    }
    catch (const std::exception& e) {
        wxMessageBox("Invalid number format in Health or Base Attack", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // Create a new player and save it
    this->player = new Player(this->name, this->cname, this->battack, this->health, this->story);
    this->GM->getGame()->addPlayer(this->name, *this->player);
    this->GM->savePlayerToJson(
        *this->player,
        fs::path("GameData") / this->GM->getGame()->getGameName() / "Players" / (this->name + ".json")
    );
}
