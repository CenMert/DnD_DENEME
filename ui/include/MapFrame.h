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
    // Üye deðiþkenler:
    wxString m_imagePath;
    wxImage m_originalImage;         // Orijinal görüntü
    wxStaticBitmap* m_staticBitmap;  // Görüntüyü gösteren kontrol

    // Event handler
    void OnResize(wxSizeEvent& event);

    wxDECLARE_EVENT_TABLE();
};
