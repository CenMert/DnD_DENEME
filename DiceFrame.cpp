#include "DiceFrame.h"
// Eðer wxGIFDecoder gibi bir yardýmcý kütüphane kullanýyorsanýz, aþaðýdaki satýrý aktif edebilirsiniz.
// #include <wx/gifdecod.h>

DiceFrame::DiceFrame(wxWindow* parent, Dice theDice)
    : wxFrame(parent, wxID_ANY, "Rolling Dice Window", wxDefaultPosition, wxSize(250, 300)),
    theDice(theDice)
{
    CreateStatusBar();

    wxPanel* gif_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
    wxPanel* button_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(50, 50));

    gif_panel->SetBackgroundColour(wxColor(100, 100, 200));
    button_panel->SetBackgroundColour(wxColor(100, 200, 200));

    wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);

    // Creating the button
    wxButton* rollButton = new wxButton(button_panel, wxID_ANY, "Roll the " + theDice.getDiceType());

    rollButton->Bind(wxEVT_BUTTON, &DiceFrame::On_Roll_ButtonClicked, this);

    main_sizer->Add(gif_panel, 1, wxEXPAND | wxALL, 10);
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
    this->SetStatusText(to_string(status));
    // I get true from the code above, which means I can open and read the gif file.
    // So i can show it too right????


}

bool DiceFrame::IsGIFReadableWithHandler(const std::string& gif_path)
{
    wxGIFHandler gifHandler;
    wxFileInputStream input(gif_path);

    if (!input.IsOk()) return false;
    else return gifHandler.CanRead(input);

}
