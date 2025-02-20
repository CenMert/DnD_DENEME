#include "DiceFrame.h"

// Constructor
DiceFrame::DiceFrame(wxWindow* parent, Dice theDice)
    : wxFrame(parent, wxID_ANY, "Rolling Dice Window", wxDefaultPosition, wxSize(128, 128)),
    theDice(theDice)
{
    // Create the status bar
    CreateStatusBar();

    // Initialize image handlers
    wxInitAllImageHandlers();

    // Create the panel for displaying the image.
    m_gifPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(128, 128));
    m_gifPanel->SetBackgroundColour(wxColor(100, 100, 200));

    // Create the static bitmap to display the PNG.
    // Initially, we create it with a null bitmap.
    m_staticBitmap = new wxStaticBitmap(m_gifPanel, wxID_ANY, wxNullBitmap, wxPoint(0, 0), wxSize(128, 128));

    // Load and display the initial image (Dice0.png)
    fs::path initialPath = fs::path("animations") / "dice_animations" / "Dice0.png";
    wxImage initialImage;
    if (initialImage.LoadFile(initialPath.string(), wxBITMAP_TYPE_PNG))
    {
        m_staticBitmap->SetBitmap(wxBitmap(initialImage));
        m_gifPanel->Refresh();
    }
    else
    {
        wxLogError("Failed to load initial PNG image.");
    }

    // Create a panel for the roll button.
    wxPanel* button_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(50, 50));
    button_panel->SetBackgroundColour(wxColor(100, 200, 200));

    // Create the roll button and bind its event.
    wxButton* rollButton = new wxButton(button_panel, wxID_ANY, "Roll the " + theDice.getDiceType());
    rollButton->Bind(wxEVT_BUTTON, &DiceFrame::On_Roll_ButtonClicked, this);

    // Lay out the panels using a box sizer.
    wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(m_gifPanel, 1, wxEXPAND | wxALL, 10);
    main_sizer->Add(button_panel, 0, wxEXPAND | wxALL, 10);
    this->SetSizerAndFit(main_sizer);
}

// Sets the file path for the PNG based on the dice roll.
void DiceFrame::RollAndGetGIFPath() {
    int number = this->theDice.roll();
    switch (number)
    {
    case 0:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice0.png";
        break;
    case 1:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice1.png";
        break;
    case 2:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice2.png";
        break;
    case 3:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice3.png";
        break;
    case 4:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice4.png";
        break;
    case 5:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice5.png";
        break;
    case 6:
        this->gif_path = fs::path("animations") / "dice_animations" / "Dice6.png";
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

// Called when the roll button is clicked.
void DiceFrame::On_Roll_ButtonClicked(wxCommandEvent& event)
{
    // Determine the file path based on the dice roll.
    RollAndGetGIFPath();
    bool status = IsPNGReadableWithHandler(this->gif_path.string());

    // Ensure image handlers are initialized.
    wxInitAllImageHandlers();

    if (status)
    {
        // Load the PNG image.
        wxImage image;
        if (!image.LoadFile(this->gif_path.string(), wxBITMAP_TYPE_PNG))
        {
            wxLogError("Failed to load PNG file.");
            return;
        }

        // Display the PNG image in the static bitmap control.
        m_staticBitmap->SetBitmap(wxBitmap(image));
        m_gifPanel->Refresh();

        this->SetStatusText("PNG loaded: " + this->gif_path.string());
    }
    else
    {
        wxLogError("Failed to read PNG file.");
    }
}

// Checks if the PNG file can be opened and loaded.
bool DiceFrame::IsPNGReadableWithHandler(const std::string& png_path)
{
    // Open the file stream.
    wxFileInputStream fileStream(png_path);
    if (!fileStream.IsOk())
        return false;

    // Try loading the image as PNG.
    wxImage testImage;
    if (!testImage.LoadFile(png_path, wxBITMAP_TYPE_PNG))
        return false;

    return true;
}