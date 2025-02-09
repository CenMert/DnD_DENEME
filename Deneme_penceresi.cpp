#include <wx/wx.h>

class MyFrame : public wxFrame {
public:
    MyFrame()
        : wxFrame(nullptr, wxID_ANY, "wxPanel Example", wxDefaultPosition, wxSize(400, 300))
    {
        // Create a panel that will act as a container for other controls
        wxPanel* panel = new wxPanel(this, wxID_ANY);

        // Create a button on the panel
        wxButton* button = new wxButton(panel, wxID_ANY, "Click Me", wxPoint(20, 20));

        // (Optional) Use a sizer for better layout management
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(button, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
        panel->SetSizer(sizer);
    }
};

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MyFrame* frame = new MyFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
