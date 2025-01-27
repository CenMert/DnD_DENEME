#define _CRT_SECURE_NO_WARNINGS
#include "MapFrame.h"

MapFrame::MapFrame(wxWindow* parent, wxString MapPath)
    : wxFrame(parent, wxID_ANY, "Map Window", wxDefaultPosition, wxSize(800, 600))
{
    this->path = MapPath;

    wxPanel* mapPanel = new wxPanel(this);
    mapPanel->SetBackgroundColour(wxColour(204, 147, 114));

    wxImage image;
    if (!image.LoadFile(this->path, wxBITMAP_TYPE_PNG)) {
        wxMessageBox("Failed to load map image: " + this->path, "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxBitmap mapBitmap(image);
    this->mapBitmap = new wxStaticBitmap(mapPanel, wxID_ANY, mapBitmap, wxPoint(0, 0), image.GetSize());

    // Optional: Add sizer
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(this->mapBitmap, 1, wxEXPAND | wxALL, 5);
    mapPanel->SetSizer(sizer);

    this->Show();
}


MapFrame::~MapFrame()
{
}
