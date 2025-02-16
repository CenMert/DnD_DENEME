// DiceFrame.cpp
#include "DiceFrame.h"

// If you're using a helper library like wxGIFDecoder, you can uncomment the following line:
// #include <wx/gifdecod.h>

DiceFrame::DiceFrame(wxWindow* parent, Dice theDice)
    : wxFrame(parent, wxID_ANY, "Rolling Dice Window", wxDefaultPosition, wxSize(250, 300)),
    theDice(theDice)
{
    CreateStatusBar();

    // Store the gif panel in a member variable so it can be used later.
    m_gifPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
    wxPanel* button_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(50, 50));

    m_gifPanel->SetBackgroundColour(wxColor(100, 100, 200));
    button_panel->SetBackgroundColour(wxColor(100, 200, 200));

    wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);

    // Create the roll button
    wxButton* rollButton = new wxButton(button_panel, wxID_ANY, "Roll the " + theDice.getDiceType());
    rollButton->Bind(wxEVT_BUTTON, &DiceFrame::On_Roll_ButtonClicked, this);

    main_sizer->Add(m_gifPanel, 1, wxEXPAND | wxALL, 10);
    main_sizer->Add(button_panel, 0, wxEXPAND | wxALL, 10);
    this->SetSizerAndFit(main_sizer);
}

void DiceFrame::RollAndGetGIFPath() {
    int number = this->theDice.roll();
    switch (number)
    {
    case 1:
        this->gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_1_example.gif";
        break;
    case 2:
        this->gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_2_example.gif";
        break;
    case 3:
        this->gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_3_example.gif";
        break;
    case 4:
        this->gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_4_example.gif";
        break;
    case 5:
        this->gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_5_example.gif";
        break;
    case 6:
        this->gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_6_example.gif";
        break;
    default:
        break;
    }
}

void DiceFrame::On_Roll_ButtonClicked(wxCommandEvent& event)
{
    RollAndGetGIFPath();
    bool status = IsGIFReadableWithHandler(this->gif_path.string());
    this->SetStatusText(std::to_string(status));

    if (status)
    {
        m_animation = new wxAnimation();
        m_animation->LoadFile(this->gif_path.string(), wxANIMATION_TYPE_GIF);

        m_animCtrl = new wxAnimationCtrl(m_gifPanel,
                                        wxID_ANY,
                                        *m_animation, // dereference the pointer here
                                        wxDefaultPosition,
                                        wxSize(128, 128),
                                        0,
                                        "Dice GIF");

        m_animCtrl->SetAnimation(*m_animation);
        
        m_gifPanel->Refresh();
        m_animCtrl->Play(false);
        


    }
    else
    {
        wxLogError("Failed to run GIF file.");
    }
}



bool DiceFrame::IsGIFReadableWithHandler(const std::string& gif_path)
{
    wxGIFHandler gifHandler;
    this->input = new wxFileInputStream(gif_path);

    if (!input->IsOk())
        return false;
    else
        return gifHandler.CanRead(*input);
}
