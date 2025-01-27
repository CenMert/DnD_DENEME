#pragma once
#include <wx/wx.h>

class MapFrame : public wxFrame
{
public:
	MapFrame(wxWindow* parent, wxString MapPath);
	~MapFrame();
private:
	wxStaticBitmap* mapBitmap;
	wxString path;
};

