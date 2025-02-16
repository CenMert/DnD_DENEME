﻿#include "GameFrame.h"


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
	// initialization
	loaded_session = new Session();

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
		wxButton* SaveForCurrentSessionButton = new wxButton(SideButtonPanel, wxID_ANY, "Save For\nCurrent Session");
		wxButton* DiceButton = new wxButton(SideButtonPanel, wxID_ANY, "Dice");
		
		SBP_Sizer->Add(MapButton, 0, wxALL, vertical_space);
		SBP_Sizer->Add(SaveButton, 0, wxALL, vertical_space);
		SBP_Sizer->Add(LoadButton, 0, wxALL, vertical_space);
		SBP_Sizer->Add(SaveForNewSessionButton, 0, wxALL, vertical_space);
		SBP_Sizer->Add(SaveForCurrentSessionButton, 0, wxALL, vertical_space);
		SBP_Sizer->Add(DiceButton, 0, wxALL, vertical_space);
		
		SaveButton->Bind(wxEVT_BUTTON, &GameFrame::saveBC, this);
		MapButton->Bind(wxEVT_BUTTON, &GameFrame::On_Map_ButtonClicked, this);
		LoadButton->Bind(wxEVT_BUTTON, &GameFrame::On_Load_ButtonClicked, this);
		SaveForNewSessionButton->Bind(wxEVT_BUTTON, &GameFrame::On_SaveForNewSession_ButtonClicked, this);
		SaveForCurrentSessionButton->Bind(wxEVT_BUTTON, &GameFrame::On_SaveForCurrentSession_ButtonClicked, this);
		DiceButton->Bind(wxEVT_BUTTON, &GameFrame::On_Dice_ButtonClicked, this);

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
			// psp_sizer->AddStretchSpacer(1);
			player_specific_panel->SetSizer(psp_sizer);

			PCP_Sizer->Add(player_specific_panel, vertical_space);
		}

		PlayerCardPanel->SetSizer(PCP_Sizer);


	// player card panel ends

	// Play Voice Panel starts
		// Ill create number of buttons that I have in the audio file.
		// name all the buttons with the name of the files.
		// bind them to the button click function.
		
		

	// Play voice Panel ends
		wxPanel* AudioPanel = new wxPanel(MainPanel, wxID_ANY);
		wxBoxSizer* Audio_Sizer = new wxBoxSizer(wxVERTICAL);

		fs::path audio_path("audios");
		for (fs::path file_path : fs::directory_iterator(audio_path))
		{
			std::string audio_filename = file_path.filename().stem().string();

			wxButton* AudioButton = new wxButton(AudioPanel, wxID_ANY, audio_filename);
			AudioButton->UseBackgroundColour();
			AudioButton->Bind(wxEVT_BUTTON, [this, file_path](wxCommandEvent& event) {
				this->On_Audio_ButtonClicked(file_path, event);
			});

			Audio_Sizer->Add(AudioButton, 0, wxALIGN_CENTER | wxCENTER, 10);
			AudioPanel->SetSizer(Audio_Sizer);
		}


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

	// Colouring the Panels
		AudioPanel->SetBackgroundColour(wxColour(50, 120, 50));
		SideButtonPanel->SetBackgroundColour(wxColour(100, 120, 120));
		MainPanel->SetBackgroundColour(wxColour(120, 100, 140));
		TextCtrlPanel->SetBackgroundColour(wxColour(120, 120, 160));
		PlayerCardPanel->SetBackgroundColour(wxColour(80, 80, 180));


	MainSizer->Add(AudioPanel, 0, wxEXPAND | wxALL, horizontal_space);
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
	fs::path map_folder =
		fs::path("GameData") / this->GM->getGame()->getGameName() / "Maps";

	wxArrayString choices;
	for (const auto& file : fs::directory_iterator(map_folder))
	{
		choices.Add(file.path().stem().string());
	}

	ChoiceDialog dlg(this, choices);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString selectedMap = dlg.GetSelectedString();

		std::string selectedMapStr = std::string(selectedMap.mb_str());
		fs::path mapFilePath = map_folder / (selectedMapStr + ".png");

		this->SetStatusText("Map selected: " + selectedMapStr);

		MapFrame* mapFrame = new MapFrame(this, wxString(mapFilePath.string()));
		mapFrame->Show();
	}

}

void GameFrame::On_Load_ButtonClicked(wxCommandEvent& event)
{
	this->SetStatusText("Load Button Clicked.");

	// Get keys from sessions
	std::vector<std::string> keys;
	for (auto& [key, session] : *this->GM->getGame()->getSessions())
	{
		keys.push_back(key);
	}

	// Convert keys to wxArrayString
	wxArrayString choices;
	for (const auto& key : keys)
	{
		choices.Add(wxString(key));
	}

	// Create and show the dialog modally
	ChoiceDialog dlg(this, choices);
	if (dlg.ShowModal() == wxID_OK)
	{
		// Process selection
		int selectedIndex = dlg.GetSelection();
		wxString selectedKey = dlg.GetSelectedString();
		wxLogStatus("You selected: " + selectedKey);

		// Convert wxString to std::string
		std::string keyStr = std::string(selectedKey.mb_str());

		// Get the sessions map (assuming it's a shared_ptr)
		std::shared_ptr<std::unordered_map<std::string, Session>> sessions = this->GM->getGame()->getSessions(); // shared_ptr to unordered_map

		// Use find() to locate the session using the key
		auto it = sessions->find(keyStr);
		if (it != sessions->end())
		{
			*loaded_session = it->second;
			std::string content = loaded_session->getSessionText_asCompleteString();
			this->Content->ChangeValue(content);
			this->SetTitle("The Game - " + loaded_session->getSessionName());
		}
		else
		{
			wxMessageBox("Session not found for key: " + selectedKey);
		}
	}
}

void GameFrame::On_SaveForNewSession_ButtonClicked(wxCommandEvent& event)
{
	// declare the name of the session
	std::string sessionFileName;
	QuestionDialog QD(this, sessionFileName, "What is the sessions name?");
	if (QD.ShowModal() == wxID_OK)
	{
		sessionFileName = QD.GetAnswer();
	}
	// end name of the session

	// random generation
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<long long> dist(10000, 99999);
	int sessionRandomID = dist(gen);
	// random generation end

	// get the current time
	std::time_t t = std::time(0);   // Şu anki zamanı al
	std::tm* now = std::localtime(&t);

	std::string today =
		std::to_string(now->tm_mday) + "-" +
		std::to_string(now->tm_mon + 1) + "-" + 
		std::to_string(now->tm_year + 1900);
	// end current time

	// session text
	std::vector< std::string > vecTXT = GetVectorOfContent();
	//end session text

	Session newSessionObject(
		sessionRandomID,
		sessionFileName,
		today,
		today,
		sessionFileName + ".txt",
		vecTXT
	);

	// create the folder path for new session
	std::string gameName = this->GM->getGame()->getGameName();

	fs::path session_path = 
		fs::path("GameData") / this->GM->getGame()->getGameName() / "Sessions" / sessionFileName;
	fs::create_directory(session_path);
	// end path operation

	// create the json and txt files
	fs::path session_txt_path = session_path / (sessionFileName + ".txt");
	fs::path session_json_path = session_path / (sessionFileName + ".json");

	std::ofstream(session_txt_path).close();
	std::ofstream(session_json_path).close();
	// end file op

	this->GM->getGame()->addSession(sessionFileName, newSessionObject);
	this->GM->saveSessionToJson_txt(newSessionObject, session_json_path, session_txt_path);

	this->loaded_session = &newSessionObject;

	wxMessageBox("New Session is created and added to the game folder.");
}

void GameFrame::On_SaveForCurrentSession_ButtonClicked(wxCommandEvent& event)
{
	loaded_session->setSessionText(GetVectorOfContent());

	auto it = this->GM->getGame()->getSessions()->find(this->loaded_session->getSessionName());
	if (it != this->GM->getGame()->getSessions()->end()) {
		it->second = *loaded_session; // change it directly
	}
	else {
		std::cerr << "Session not found!\n";
	}

	

	std::string sessionFileName = loaded_session->getSessionName();

	fs::path session_path =
		fs::path("GameData") / this->GM->getGame()->getGameName() / "Sessions" / sessionFileName;

	fs::path session_txt_path = session_path / (sessionFileName + ".txt");
	fs::path session_json_path = session_path / (sessionFileName + ".json");

	this->GM->saveSessionToJson_txt(*loaded_session, session_json_path, session_txt_path);

	this->SetStatusText("Save For Current Button Clicked.");
}

void GameFrame::On_Dice_ButtonClicked(wxCommandEvent& event)
{
	wxArrayString choices;
	auto& vec = this->GM->getGame()->getDices();
	for (auto& dice : *vec)
	{
		choices.Add(dice.getDiceType());
	}
	
	
	ChoiceDialog dlg(this, choices);
	if (dlg.ShowModal() == wxID_OK)
	{
		auto& theDice( vec->at(dlg.GetSelection()) );
		DiceFrame* diceFrame = new DiceFrame(this, theDice);

		diceFrame->Show();
	}
}

void GameFrame::On_Audio_ButtonClicked(fs::path file_path, wxCommandEvent& event)
{
	// Convert fs::path to wxString (ensure proper encoding)
	wxString wxFilePath = wxString::FromUTF8(file_path.string().c_str());

	// Check if the file exists
	if (!wxFileExists(wxFilePath)) {
		wxMessageBox("File does not exist: " + wxFilePath,
			"Error", wxOK | wxICON_ERROR);
		return;
	}

	// Create a wxSound object (using async playback by default)
	wxSound sound(wxFilePath, wxSOUND_ASYNC);

	if (sound.IsOk())
	{
		// Try playing the sound using the default flag (or explicitly wxSOUND_ASYNC)
		bool status = sound.Play();
		this->SetStatusText(wxFilePath + " " + (status ? "played" : "failed to play"));
	}
	else
	{
		wxMessageBox("Could not load the audio file: " + wxFilePath,
			"Error", wxOK | wxICON_ERROR);
	}
}

std::vector<std::string> GameFrame::GetVectorOfContent()
{
	// wxTextCtrl içeriğini al
	std::string ContentSTR = this->Content->GetValue().ToStdString();

	std::vector<std::string> vecTXT;
	std::stringstream ss(ContentSTR);
	std::string line;

	// Satır satır oku ve vektöre ekle
	while (std::getline(ss, line, '\n')) {
		vecTXT.push_back(line);
	}

	return vecTXT;
}
