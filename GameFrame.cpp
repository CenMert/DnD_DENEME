#include "GameFrame.h"


namespace fs = std::filesystem;
using json = nlohmann::json;

// Define custom event IDs
enum Game_IDs {
	ID_TopHeader = 2,
	ID_SideButtonPanel = 3,
	ID_MapButton = 4,
	ID_AddPlayerButton = 5,
	ID_SaveButton = 6,
	ID_LoadButton = 7,
	ID_TextEditor = 8,

	ID_SaveForNewSessionButton = 9,
	ID_SaveForCurrentSessionButton = 10
};

// Color and size settings
wxColour buttonColour(wxT("#A6551C"));
wxColour backgroundColour(wxT("#CC9372"));
wxColour playerCardBGColour(wxT("#E3D83D"));
wxSize SidePanelButtonSize = wxSize(100, 25);
wxSize DynamicTextSize = wxSize(600, 400);
wxSize PlayerCardSize = wxSize(200, 100);
wxSize PlayerCardButtonSize = wxSize(80, 25);

// Button spaces
enum buttons_constants {
	vertical_space = 5,
	horizontal_space = 5
};

GameFrame::GameFrame(wxWindow* parent, wxString GameFolder)
	: wxFrame(parent, wxID_ANY, "The Game", wxDefaultPosition, wxSize(1280, 720)),
	GM(std::make_shared<GameManager>(GameFolder.ToStdString()))
{

	wxFont oldFont = wxFont(wxString(fontStyle));
	// the icon operation that appears at the top of the window with its header.
	wxIcon appIcon;
	if (appIcon.LoadFile("game_icon.ico", wxBITMAP_TYPE_ICO)) { SetIcon(appIcon); }
	else { wxLogError("Icon File couldn't added to window."); }

	// we have set the game.
	GM->setGame(GameFolder.ToStdString());
	
	// initialize the datas
	GM->loadGame();
	wxMessageBox("Game: " + GameFolder + " is loaded.");

	wxPanel* MainPanel = new wxPanel(this, wxID_ANY);
	wxBoxSizer * MainSizer = new wxBoxSizer(wxHORIZONTAL);

	/** Here is the button consturction area. */
	// initializing side buttons
		wxPanel* SideButtonPanel = new wxPanel(MainPanel, wxID_ANY);
		wxBoxSizer* SBP_Sizer = new wxBoxSizer(wxVERTICAL); // to adjust vertical

		wxButton* MapButton = new wxButton(SideButtonPanel, wxID_ANY, "Map");
		wxButton* SaveButton = new wxButton(SideButtonPanel, wxID_ANY, "Save");
		wxButton* LoadButton = new wxButton(SideButtonPanel, wxID_ANY, "Load");
		wxButton* SaveForNewSessionButton = new wxButton(SideButtonPanel, wxID_ANY, "Save For\nNew Session");

		SBP_Sizer->Add(MapButton, 0, wxALL, vertical_space);
		SBP_Sizer->Add(SaveButton, 0, wxALL, vertical_space);
		SBP_Sizer->Add(LoadButton, 0, wxALL, vertical_space);
		SBP_Sizer->Add(SaveForNewSessionButton, 0, wxALL, vertical_space);

		
		SaveButton->Bind(wxEVT_BUTTON, &GameFrame::saveBC, this);
		MapButton->Bind(wxEVT_BUTTON, &GameFrame::On_Map_ButtonClicked, this);
		LoadButton->Bind(wxEVT_BUTTON, &GameFrame::On_Load_ButtonClicked, this);
		SaveForNewSessionButton->Bind(wxEVT_BUTTON, &GameFrame::On_SaveForNewSession_ButtonClicked, this);
		


		SideButtonPanel->SetSizer(SBP_Sizer);
	// side button adjustmen end.

	// Left Player cards panel

		wxPanel* PlayerCardPanel = new wxPanel(MainPanel, wxID_ANY);
		wxBoxSizer* PCP_Sizer = new wxBoxSizer(wxVERTICAL);

		/*
		get all the players 
		create a panel for each of them
		adjust that panel with the information from player
		then add it to the PlayerCardPanel
		*/
		for (auto& [name, player] : *this->GM->getGame()->getPlayers()) {
			wxPanel* player_specific_panel = new wxPanel(
				PlayerCardPanel, wxID_ANY, wxDefaultPosition, wxSize(200, 100), wxBORDER_SIMPLE);
			wxBoxSizer* psp_sizer = new wxBoxSizer(wxVERTICAL);

			// adjustment
			player_specific_panel->SetBackgroundColour(backgroundColour);
			// end adjustment

			wxStaticText* player_static_txt = new wxStaticText(player_specific_panel, wxID_ANY,
				player.getName());
			wxButton* player_detail_button = new wxButton(player_specific_panel, wxID_ANY, "Details");
			player_detail_button->Bind(wxEVT_BUTTON, [this, &player](wxCommandEvent& event) {
				// 'player' artık ilgili oyuncu nesnesini temsil ediyor.
				this->On_Details_ButtonClicked(player, event);
			});

			psp_sizer->Add(player_static_txt, 0, wxALIGN_CENTER | wxALL, vertical_space);
			psp_sizer->Add(player_detail_button, 0, wxALIGN_CENTER | wxALL, vertical_space);
			psp_sizer->AddStretchSpacer(1);
			player_specific_panel->SetSizer(psp_sizer);

			PCP_Sizer->Add(player_specific_panel, vertical_space);
		}

		PlayerCardPanel->SetSizer(PCP_Sizer);


	// player card panel ends

	// middle text control panel

		wxPanel* TextCtrlPanel = new wxPanel(MainPanel, wxID_ANY);
		wxBoxSizer* TCP_Sizer = new wxBoxSizer(wxVERTICAL);
		
		this->Content = new wxTextCtrl(TextCtrlPanel, wxID_ANY,
			wxT("Type Something."),
			wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH2
		);

		TCP_Sizer->Add(Content, 1, wxEXPAND | wxALL, 10);

		TextCtrlPanel->SetSizer(TCP_Sizer);

	// middle Text Ctrl Adjustment end

	MainSizer->Add(SideButtonPanel, 0, wxEXPAND | wxALL, horizontal_space);
	MainSizer->Add(TextCtrlPanel, 1, wxEXPAND | wxALL, horizontal_space);
	MainSizer->Add(PlayerCardPanel, 0, wxEXPAND | wxALL, horizontal_space);

	MainPanel->SetSizer(MainSizer);

	CreateStatusBar();
}


void GameFrame::OnClose(wxCloseEvent& event)
{	
	wxMessageBox("Data is lost if you didn't save!");

	// Show the main menu again when closing settings
	if (GetParent()) {
		GetParent()->Show();
	}

	// Destroy this window
	this->Destroy();
}

void GameFrame::saveBC(wxCommandEvent& event)
{
	GM->saveGame();
	wxMessageBox("Game is saved!");
}

void GameFrame::On_Details_ButtonClicked(Player& player, wxCommandEvent& event)
{
	PlayerDetailsFrame* frame = new PlayerDetailsFrame(this, &player);
	wxMessageBox("You have clicked the button of details a player"+ player.getName() + ", congrat.");

	frame->Show();
}

void GameFrame::On_Map_ButtonClicked(wxCommandEvent& event)
{
	wxMessageBox("Map Button Clicked!");
}

void GameFrame::On_Load_ButtonClicked(wxCommandEvent& event)
{

	wxMessageBox("Load Button.");

	// Mevcut oturumlardan key’leri alıyoruz
	std::vector<std::string> keys;
	for (auto& [key, session] : *this->GM->getGame()->getSessions())
	{
		keys.push_back(key);
	}

	// wxArrayString oluşturup, std::string verileri wxString'e çevirerek ekliyoruz.
	wxArrayString choices;
	for (const auto& key : keys)
	{
		// Eğer uygulamanız Unicode destekliyorsa direk wxString(key) kullanılabilir.
		choices.Add(wxString(key));
	}

	// wxChoice (seçilebilir liste) kontrolü oluşturuyoruz.
	// 'this' burada GameFrame (ana pencere) nesnesidir.
	wxChoice* choiceControl = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);

	// Varsayılan olarak ilk elemanı seçili yapalım (isteğe bağlı)
	if (!choices.IsEmpty())
		choiceControl->SetSelection(0);

	choiceControl->Show();

}

void GameFrame::On_SaveForNewSession_ButtonClicked(wxCommandEvent& event)
{
	wxMessageBox("Save For New Session.");
}
