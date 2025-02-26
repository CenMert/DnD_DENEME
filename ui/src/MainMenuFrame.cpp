#include "MainMenuFrame.h"
#include "SettingsFrame.h"
#include "PlayFrame.h"
#include <filesystem>

namespace fs = std::filesystem;

enum IDs {
    ID_buttonPlay = 200,
    ID_buttonSettings = 201
};

wxBEGIN_EVENT_TABLE(MainMenuFrame, wxFrame)
    EVT_BUTTON(ID_buttonPlay, MainMenuFrame::OnButtonPlayClicked)
    EVT_BUTTON(ID_buttonSettings, MainMenuFrame::OnButtonSettingsClicked)
wxEND_EVENT_TABLE()

MainMenuFrame::MainMenuFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title)


{
    // the icon operation that appears at the top of the window with its header.
    wxIcon appIcon;
    if (appIcon.LoadFile((fs::path("def_images") / "icos" / "poition1.ico").string(), wxBITMAP_TYPE_ICO)) { SetIcon(appIcon); }
    else { wxLogError("Icon File couldn't added to window."); }

    wxPanel* mainPanel = new wxPanel(this);
    wxFont oldFont(18, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, fontStyle);

    // A STATIC TEXT
    wxStaticText* textHeader = new wxStaticText(
        mainPanel, wxID_ANY, "WELCOME\n DnD Session Tracker", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER
    );
    textHeader->SetFont(oldFont);

    // BUTTON FOR THE "PLAY"
    wxButton* buttonPlay = new wxButton(
        mainPanel, ID_buttonPlay, "Play", wxPoint(200, 250), wxSize(200, 40)
    );
    buttonPlay->SetFont(oldFont);

    // BUTTON FOR THE "SETTINGS"
    wxButton* buttonSettings = new wxButton(
        mainPanel, ID_buttonSettings, "Settings", wxPoint(200, 300), wxSize(200, 40)
    );
    buttonSettings->SetFont(oldFont);

    // TO CENTER ALL THE OBJECTS
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(textHeader, 0, wxALIGN_CENTER | wxTOP, 50);
    sizer->Add(buttonPlay, 0, wxALIGN_CENTER | wxTOP, 50);
    sizer->Add(buttonSettings, 0, wxALIGN_CENTER | wxTOP, 25);

    // COLOURING
    buttonPlay->SetBackgroundColour(buttonColour);
    buttonSettings->SetBackgroundColour(buttonColour);
    mainPanel->SetBackgroundColour(backgroundColour);

    mainPanel->SetSizer(sizer);

    CreateStatusBar();
}

// FIXED: Implemented the event handlers
void MainMenuFrame::OnButtonPlayClicked(wxCommandEvent& evt) {
    wxLogStatus("Play Button - Clicked");
    OpenPlay();
}

void MainMenuFrame::OnButtonSettingsClicked(wxCommandEvent& evt) {
    wxLogStatus("Settings Button - Clicked");
    OpenSettings();
}

void MainMenuFrame::OpenSettings()
{
    SettingsFrame* settingsWindow = new SettingsFrame(this); // Pass "this" as parent
    settingsWindow->Show();
    settingsWindow->Center();
    this->Hide(); // Hide the main menu while settings are open
}

void MainMenuFrame::OpenPlay()
{
    PlayFrame* playWindow = new PlayFrame(this); // Pass "this" as parent
    playWindow->Show();
    playWindow->Center();
    this->Hide(); // Hide the main menu while settings are open
}

