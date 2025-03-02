#pragma once
#include <wx/wx.h>
#include <wx/animate.h>
#include <wx/stream.h>
#include <wx/filename.h>
#include <wx/image.h>
#include <wx/wfstream.h>
#include <wx/imaggif.h>
#include <filesystem>
#include <string>

#include "GameManager.h"
#include "Dice.h"

namespace fs = std::filesystem;

class DiceFrame : public wxFrame
{
public:
    DiceFrame(wxWindow* parent, Dice theDice);

private:
    Dice theDice;
    fs::path gif_path;  // this holds the PNG file path

    // Function to set the file path based on the dice roll.
    void RollAndGetGIFPath();
    void updateRolledDices();
    void OnRoll(wxCommandEvent& WXUNUSED(event));
    void OnTimer(wxTimerEvent& event);

    // Here is the vars and funcs that inspired from wxWidgets sample of aninate
	wxAnimationCtrlBase* m_animationCtrl;
    wxStaticText* lastRolledDices;
    wxTimer m_timer;
    int number;
	std::vector<int>* rolledDices;

    wxFont oldFont = wxFont(10, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Papyrus");

};