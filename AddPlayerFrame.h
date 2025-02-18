#include <wx/wx.h>
#include <string>
#include "GameManager.h"

class AddPlayerFrame : public wxFrame {
public:
    AddPlayerFrame(wxWindow* parent, std::shared_ptr<GameManager> GM);

private:
    void On_Create_ButtonClicked(wxCommandEvent& event);

    std::shared_ptr<GameManager> GM;
    // Player data members (and player pointer, etc.)
    std::string name;
    std::string cname;
    double health;
    double battack;
    std::string story;
    Player* player;

    // Text controls as member variables:
    wxTextCtrl* nameCtrl;
    wxTextCtrl* cnameCtrl;
    wxTextCtrl* healthCtrl;
    wxTextCtrl* battackCtrl;
    wxTextCtrl* storyCtrl;
};
