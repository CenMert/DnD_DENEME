#pragma once
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/image.h>

#include <string>

class MapFrame : public wxFrame
{
public:
    MapFrame(wxWindow* parent, wxString imagePath);
    ~MapFrame();

private:
    // �ye de�i�kenler:
    wxString m_imagePath;
    wxImage m_originalImage;         // Orijinal g�r�nt�
    wxStaticBitmap* m_staticBitmap;  // G�r�nt�y� g�steren kontrol

    // Event handler
    void OnResize(wxSizeEvent& event);

    wxDECLARE_EVENT_TABLE();
};
