#include "DiceFrame.h"

enum
{
    ID_ROLL = 1

};


// Constructor
DiceFrame::DiceFrame(wxWindow* parent, Dice theDice)
    : wxFrame(parent, wxID_ANY, "Rolling Dice Window", wxDefaultPosition, wxSize(300, 500)),
    theDice(theDice)
{
    wxMenu* file_menu = new wxMenu;

#if wxUSE_FILEDLG
    file_menu->Append(wxID_OPEN, "&Open Animation...\tCtrl+O", "Loads an animation");
#endif // wxUSE_FILEDLG
    file_menu->Append(wxID_EXIT);

    wxMenu* play_menu = new wxMenu;
    play_menu->Append(ID_ROLL, "Roll\tCtrl+P", "Roll the dice");

#ifdef wxHAS_NATIVE_ANIMATIONCTRL
    play_menu->AppendSeparator();
    play_menu->AppendCheckItem(ID_USE_GENERIC, "Use &generic animation\tCtrl+G",
        "Selects whether native or generic version is used");
#endif // wxHAS_NATIVE_ANIMATIONCTRL

    wxMenu* help_menu = new wxMenu;
    help_menu->Append(wxID_ABOUT);

    wxMenuBar* menu_bar = new wxMenuBar;

    menu_bar->Append(file_menu, "&File");
    menu_bar->Append(play_menu, "&Animation");
    menu_bar->Append(help_menu, "&Help");
    menu_bar->Append(new wxMenu, "&Edit");

    // Associate the menu bar with this frame
    SetMenuBar(menu_bar);

#if wxUSE_STATUSBAR
    CreateStatusBar();
#endif // wxUSE_STATUSBAR

    // use a wxBoxSizer otherwise wxFrame will automatically
    // resize the m_animationCtrl to fill its client area on
    // user resizes
    wxSizer* sz = new wxBoxSizer(wxVERTICAL);
    this->rolledDices = new std::vector<int>(3, 0);


    m_animationCtrl = new wxAnimationCtrl(this, wxID_ANY, wxNullAnimation, wxDefaultPosition, wxSize(256, 256));
    fs::path default_path = fs::path("animations") / "dice_animations" / "Dice0.png";
    if (m_animationCtrl->LoadFile(default_path.string()))
        m_animationCtrl->Show();

	wxButton* rollButton = new wxButton(this, ID_ROLL, "Roll");
	rollButton->Bind(wxEVT_BUTTON, &DiceFrame::OnRoll, this);
    this->m_timer.Bind(wxEVT_TIMER, &DiceFrame::OnTimer, this);

	this->lastRolledDices = new wxStaticText(this, wxID_ANY, "Last Rolled Dices: 0, 0, 0", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxStaticText* topHeaderText = new wxStaticText(this, wxID_ANY, "Dice is Rolling:");
    topHeaderText->SetFont(oldFont);
	this->lastRolledDices->SetFont(oldFont);
    
    this->SetBackgroundColour(wxColour(251, 238, 194));
    sz->Add(topHeaderText, wxSizerFlags().Centre().Border());
    sz->Add(m_animationCtrl, wxSizerFlags().Centre().Border());
	sz->Add(rollButton, wxSizerFlags().Centre().Border());
	sz->Add(this->lastRolledDices, wxSizerFlags().Centre().Border());
    SetSizer(sz);
}

// Sets the file path for the PNG based on the dice roll.
void DiceFrame::RollAndGetGIFPath() {
    this->number = this->theDice.roll();
    switch (number)
    {
    case 0:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice0.png";
        break;
    case 1:
        this->gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_1_upscaled_enhanced.gif";
        break;
    case 2:
        this->gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_2_upscaled_enhanced.gif";
        break;
    case 3:
        this->gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_3_upscaled_enhanced.gif";
        break;
    case 4:
        this->gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_4_upscaled_enhanced.gif";
        break;
    case 5:
        this->gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_5_upscaled_enhanced.gif";
        break;
    case 6:
        this->gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_6_upscaled_enhanced.gif";
        break;
    case 7:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice7.png";
        break;
    case 8:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice8.png";
        break;
    case 9:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice9.png";
        break;
    case 10:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice10.png";
        break;
    case 11:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice11.png";
        break;
    case 12:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice12.png";
        break;
    case 13:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice13.png";
        break;
    case 14:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice14.png";
        break;
    case 15:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice15.png";
        break;
    case 16:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice16.png";
        break;
    case 17:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice17.png";
        break;
    case 18:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice18.png";
        break;
    case 19:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice19.png";
        break;
    case 20:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice20.png";
        break;
    default:
        break;
    }
}

void DiceFrame::updateRolledDices()
{
    this->rolledDices->pop_back();
    int first = this->rolledDices->at(0);
	int second = this->rolledDices->at(1);

    std::vector<int>* newVec = new std::vector<int>{ this->number, first, second };

    this->rolledDices->swap(*newVec);
    delete newVec;
}

void DiceFrame::OnRoll(wxCommandEvent& WXUNUSED(event))
{
    RollAndGetGIFPath();
    updateRolledDices(); // update and display at the and
    if (m_animationCtrl->LoadFile(gif_path.string()))
    { 
        m_animationCtrl->Play();
        this->m_timer.StartOnce(2200);
        // our animations are 1500 miliseconds long
        // so wait that long then call the timer, it will stop the animation.
    }

}

void DiceFrame::OnTimer(wxTimerEvent& event)
{
    // Stop the animation control when the timer fires
    if (m_animationCtrl) m_animationCtrl->Stop();
    std::string text = "Last Rolled Dices: " +
        std::to_string(this->rolledDices->at(0)) + ", " + std::to_string(this->rolledDices->at(1)) + ", " + std::to_string(this->rolledDices->at(2));

    lastRolledDices->SetLabelText(text);
}

