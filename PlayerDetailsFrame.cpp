#include "PlayerDetailsFrame.h"
#include <wx/statline.h>   // For wxStaticLine

PlayerDetailsFrame::PlayerDetailsFrame(wxWindow* parent, Player* player)
    : wxFrame(parent, wxID_ANY, "Player Information", wxDefaultPosition, wxSize(500, 400)), player(player)
{
    // Create the main panel with a light background colour
    wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
    mainPanel->SetBackgroundColour(wxColour(245, 245, 245));

    // Overall vertical sizer for the frame
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // --- Header ---
    wxStaticText* header = new wxStaticText(mainPanel, wxID_ANY, "Player Details", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont headerFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    header->SetFont(headerFont);
    mainSizer->Add(header, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 15);

    // --- Basic Information Section ---
    // Use a static box to group related information
    wxStaticBoxSizer* infoBoxSizer = new wxStaticBoxSizer(wxVERTICAL, mainPanel, "Basic Information");

    // Grid sizer for aligning labels and their values
    wxGridSizer* infoGrid = new wxGridSizer(2, 10, 10);  // 2 columns, 10px horizontal and vertical gap

    // Define fonts for labels and values
    wxFont labelFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxFont valueFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    // Name
    wxStaticText* nameLabel = new wxStaticText(mainPanel, wxID_ANY, "Name:", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    nameLabel->SetFont(labelFont);
    wxStaticText* nameValue = new wxStaticText(mainPanel, wxID_ANY, player->getName());
    nameValue->SetFont(valueFont);
    infoGrid->Add(nameLabel, 0, wxALIGN_CENTER_VERTICAL);
    infoGrid->Add(nameValue, 0, wxALIGN_CENTER_VERTICAL);

    // Character Name
    wxStaticText* charLabel = new wxStaticText(mainPanel, wxID_ANY, "Character:", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    charLabel->SetFont(labelFont);
    wxStaticText* charValue = new wxStaticText(mainPanel, wxID_ANY, player->getCharacterName());
    charValue->SetFont(valueFont);
    infoGrid->Add(charLabel, 0, wxALIGN_CENTER_VERTICAL);
    infoGrid->Add(charValue, 0, wxALIGN_CENTER_VERTICAL);

    // Health
    wxStaticText* healthLabel = new wxStaticText(mainPanel, wxID_ANY, "Health:", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    healthLabel->SetFont(labelFont);
    wxStaticText* healthValue = new wxStaticText(mainPanel, wxID_ANY, std::to_string(player->getHealth()));
    healthValue->SetFont(valueFont);
    infoGrid->Add(healthLabel, 0, wxALIGN_CENTER_VERTICAL);
    infoGrid->Add(healthValue, 0, wxALIGN_CENTER_VERTICAL);

    // Base Attack
    wxStaticText* attackLabel = new wxStaticText(mainPanel, wxID_ANY, "Base Attack:", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    attackLabel->SetFont(labelFont);
    wxStaticText* attackValue = new wxStaticText(mainPanel, wxID_ANY, std::to_string(player->getBaseAttack()));
    attackValue->SetFont(valueFont);
    infoGrid->Add(attackLabel, 0, wxALIGN_CENTER_VERTICAL);
    infoGrid->Add(attackValue, 0, wxALIGN_CENTER_VERTICAL);

    // Add the grid to the static box sizer with padding
    infoBoxSizer->Add(infoGrid, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(infoBoxSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 15);

    // --- Separator ---
    mainSizer->AddSpacer(10);
    wxStaticLine* separator = new wxStaticLine(mainPanel, wxID_ANY);
    mainSizer->Add(separator, 0, wxEXPAND | wxLEFT | wxRIGHT, 15);
    mainSizer->AddSpacer(10);

    // --- Story Section ---
    // Use a static box sizer for the story section
    wxStaticBoxSizer* storyBoxSizer = new wxStaticBoxSizer(wxVERTICAL, mainPanel, "Story");
    wxTextCtrl* storyBox = new wxTextCtrl(mainPanel, wxID_ANY, player->getStory(),
        wxDefaultPosition, wxSize(-1, 150),
        wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
    storyBox->SetBackgroundColour(wxColour(250, 250, 250));  // Slightly different white for contrast
    storyBoxSizer->Add(storyBox, 1, wxEXPAND | wxALL, 10);

    mainSizer->Add(storyBoxSizer, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 15);

    // Set the sizer for the main panel
    mainPanel->SetSizer(mainSizer);

    // Adjust the frame to fit the contents and centre on the screen
    mainSizer->SetSizeHints(this);
    this->Centre();
}
