#pragma once
#define _HAS_STD_BYTE 0
#include <cstddef>
// diðer includes...

#include "GameManager.h"
#include "PlayFrame.h"

#include <string>
#include <wx/wx.h>
#include "MapFrame.h"
#include "PlayerDetailsFrame.h"
#include "ChoiceDialog.h"
#include "QuestionDialog.h"
#include "json.hpp"

#include <filesystem>
#include <fstream>
#include <vector>
#include <sstream>
#include <random>
#include <chrono>

#include <wx/filedlg.h>
#include <wx/statbmp.h>
#include <wx/image.h>


class GameFrame : public wxFrame
{
public:
	GameFrame(wxWindow* parent, wxString GameFolder);
	~GameFrame() {};
private:

	// On Close
	void OnClose(wxCloseEvent& event);

	//	Side Panel Buttons
	void saveBC(wxCommandEvent& event);

	// some constrains
	// Example Folder Hierarcy
	/*
		-GameData/
			|-Game1/
				|-Players/
					|-Berke.json
					|-Serhat.json
				|-Sessions/
					|-Session1/
						|-Session1.json
						|-Session1.txt
					|-Session2/
						|-Session2.json
						|-Session2.txt
				|-maps/
					|-DnD_Battle_Map.png
	*/

	wxTextCtrl* Content;

	// this is the varibal that selected for load session
	Session* loaded_session;

	std::shared_ptr< GameManager > GM;

	std::string fontStyle = "Papyrus";
	
	// On Button Events
	void On_Details_ButtonClicked(Player& player, wxCommandEvent& event);
	void On_Map_ButtonClicked(wxCommandEvent& event);

	void On_Load_ButtonClicked(wxCommandEvent& event);
	void On_SaveForNewSession_ButtonClicked(wxCommandEvent& event);
	void On_SaveForCurrentSession_ButtonClicked(wxCommandEvent& event);

	// additional required functions
	std::vector< std::string > GetVectorOfContent();
};

