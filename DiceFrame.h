#pragma once
#include <wx/wx.h>
#include <wx/animate.h>
#include <wx/stream.h>
#include <wx/filename.h>
#include <wx/image.h>
#include <wx/wfstream.h>
#include <wx/imaggif.h>
#include <filesystem>

#include "GameManager.h"
#include "Dice.h"
#include <string>

namespace fs = std::filesystem;

class DiceFrame : public wxFrame
{
public:
    DiceFrame(wxWindow* parent, Dice theDice);

private:
    Dice theDice;
    fs::path gif_path;

    void RollAndGetGIFPath();

    void On_Roll_ButtonClicked(wxCommandEvent& event);

    bool IsGIFReadableWithHandler(const std::string& gif_path);
};
