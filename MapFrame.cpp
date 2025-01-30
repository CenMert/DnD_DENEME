#define _CRT_SECURE_NO_WARNINGS
#include "MapFrame.h"

// Constructor for MapFrame
MapFrame::MapFrame(wxWindow* parent, wxString ImageName)
    : wxFrame(parent, wxID_ANY, "Map Window", wxDefaultPosition, wxSize(800, 600)),
    ImageName(ImageName)
{
    // Ensure PNG support is initialized
    wxImage::AddHandler(new wxPNGHandler());

    // Create a panel for the image
    wxPanel* ImagePanel = new wxPanel(this, wxID_ANY);
    ImagePanel->SetBackgroundColour(wxColour(204, 147, 114));

    // Sizer for layout
    wxBoxSizer* ImageSizer = new wxBoxSizer(wxVERTICAL);

    // Load and display the image if the filename is valid
    if (!ImageName.IsEmpty())
    {
        wxImage image;
        if (image.LoadFile(ImageName, wxBITMAP_TYPE_PNG))
        {
            wxBitmap bitmap(image);

            // Create a static bitmap to display the image
            wxStaticBitmap* staticBitmap = new wxStaticBitmap(ImagePanel, wxID_ANY, bitmap);

            // Adjust size to fit the panel
            staticBitmap->SetSize(ImagePanel->GetClientSize());

            // Add to sizer
            ImageSizer->Add(staticBitmap, 1, wxEXPAND | wxALL, 5);
        }
        else
        {
            wxMessageBox("Failed to load the map image: " + ImageName, "Error", wxOK | wxICON_ERROR);
        }
    }

    // Set sizer for panel
    ImagePanel->SetSizer(ImageSizer);

    // Set sizer for the frame
    this->SetSizerAndFit(ImageSizer);
}

MapFrame::~MapFrame() { ; }
