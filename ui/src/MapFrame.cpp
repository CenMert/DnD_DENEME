#include "MapFrame.h"
#include <algorithm> // std::min

// Event table'a resize eventi ekle
wxBEGIN_EVENT_TABLE(MapFrame, wxFrame)
EVT_SIZE(MapFrame::OnResize)
wxEND_EVENT_TABLE()

// Constructor: Ba�lang�� boyutunu 1200x900 olarak ayarlad�m.
MapFrame::MapFrame(wxWindow* parent, wxString imagePath)
    : wxFrame(parent, wxID_ANY, "Map Window", wxDefaultPosition, wxSize(1200, 900)),
    m_imagePath(imagePath)
{
    // PNG deste�ini ekle
    wxImage::AddHandler(new wxPNGHandler());

    // Panel olu�tur
    wxPanel* imagePanel = new wxPanel(this, wxID_ANY);
    imagePanel->SetBackgroundColour(wxColour(204, 147, 114));

    // Sizer ayarlamas�
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // G�r�nt�y� y�kle
    if (!m_imagePath.IsEmpty())
    {
        if (m_originalImage.LoadFile(m_imagePath, wxBITMAP_TYPE_PNG))
        {
            // Ba�lang��ta pencerenin mevcut boyutuna g�re �l�ekle
            wxSize clientSize = GetClientSize();
            double scaleWidth = (double)clientSize.GetWidth() / m_originalImage.GetWidth();
            double scaleHeight = (double)clientSize.GetHeight() / m_originalImage.GetHeight();
            double scaleFactor = std::min(scaleWidth, scaleHeight);

            int newWidth = m_originalImage.GetWidth() * scaleFactor;
            int newHeight = m_originalImage.GetHeight() * scaleFactor;
            wxImage scaledImage = m_originalImage.Copy();
            scaledImage.Rescale(newWidth, newHeight, wxIMAGE_QUALITY_HIGH);

            m_staticBitmap = new wxStaticBitmap(imagePanel, wxID_ANY, wxBitmap(scaledImage));
            sizer->Add(m_staticBitmap, 1, wxEXPAND | wxALL, 5);
        }
        else
        {
            wxMessageBox("Failed to load the map image: " + m_imagePath, "Error", wxOK | wxICON_ERROR);
        }
    }

    imagePanel->SetSizer(sizer);
    this->SetSize(400, 400);
}

MapFrame::~MapFrame()
{
    // m_staticBitmap otomatik olarak temizlenecektir
}

void MapFrame::OnResize(wxSizeEvent& event)
{
    // E�er resim y�klenmi�se, pencere yeniden boyutland���nda resmi yeniden �l�ekle
    if (m_originalImage.IsOk() && m_staticBitmap)
    {
        wxSize clientSize = GetClientSize();
        double scaleWidth = (double)clientSize.GetWidth() / m_originalImage.GetWidth();
        double scaleHeight = (double)clientSize.GetHeight() / m_originalImage.GetHeight();
        double scaleFactor = std::min(scaleWidth, scaleHeight);

        int newWidth = m_originalImage.GetWidth() * scaleFactor;
        int newHeight = m_originalImage.GetHeight() * scaleFactor;
        wxImage scaledImage = m_originalImage.Copy();
        scaledImage.Rescale(newWidth, newHeight, wxIMAGE_QUALITY_HIGH);

        m_staticBitmap->SetBitmap(wxBitmap(scaledImage));
        // Yeniden d�zenleme i�in sizer'� g�ncelle
        Layout();
    }
    event.Skip(); // Di�er event handlerlar�n da �al��mas�n� sa�lar
}
