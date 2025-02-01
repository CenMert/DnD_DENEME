#define _CRT_SECURE_NO_WARNINGS
#include "MapFrame.h"

// Constructor for MapFrame
MapFrame::MapFrame(wxWindow* parent, wxString ImageName)
    : wxFrame(parent, wxID_ANY, "Map Window", wxDefaultPosition, wxSize(800, 600)), // Set fixed size (800x600)
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
            // Scale the image to fit the frame size while maintaining aspect ratio
            int frameWidth = 800;  // Width of the MapFrame
            int frameHeight = 600; // Height of the MapFrame

            // Calculate scaling factor
            double scaleWidth = (double)frameWidth / image.GetWidth();
            double scaleHeight = (double)frameHeight / image.GetHeight();
            double scaleFactor = std::min(scaleWidth, scaleHeight);

            // Resize the image
            int newWidth = image.GetWidth() * scaleFactor;
            int newHeight = image.GetHeight() * scaleFactor;
            image.Rescale(newWidth, newHeight, wxIMAGE_QUALITY_HIGH);

            // Convert the resized image to a bitmap
            wxBitmap bitmap(image);

            // Create a static bitmap to display the image
            wxStaticBitmap* staticBitmap = new wxStaticBitmap(ImagePanel, wxID_ANY, bitmap);

            // Add to sizer with expansion
            ImageSizer->Add(staticBitmap, 1, wxEXPAND | wxALL, 5);
        }
        else
        {
            wxMessageBox("Failed to load the map image: " + ImageName, "Error", wxOK | wxICON_ERROR);
        }
    }

    // Set sizer for panel
    ImagePanel->SetSizer(ImageSizer);

    // Fit the frame to the contents
    this->Fit();
}

MapFrame::~MapFrame() { ; }