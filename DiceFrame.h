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

    // Panel for displaying the image and a static bitmap control.
    wxPanel* m_gifPanel = nullptr;
    wxStaticBitmap* m_staticBitmap = nullptr;

    // Function to set the file path based on the dice roll.
    void RollAndGetGIFPath();

    // Event handler for the roll button.
    void On_Roll_ButtonClicked(wxCommandEvent& event);

    // Function to check if a PNG file is readable.
    bool IsPNGReadableWithHandler(const std::string& png_path);
};