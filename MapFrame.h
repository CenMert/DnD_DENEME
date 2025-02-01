#pragma once
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dir.h>

#include <string>

class MapFrame : public wxFrame
{
public:
    MapFrame(wxWindow* parent, wxString ImageName);
    ~MapFrame();

private:
    wxString ImageName;
};