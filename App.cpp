#include "App.h"
#include "MainMenuFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    MainMenuFrame* mainMenuFrame = new MainMenuFrame("Main Menu");
    mainMenuFrame->SetClientSize(450, 600);
    mainMenuFrame->Center();
    mainMenuFrame->Show();
    return true;
}
