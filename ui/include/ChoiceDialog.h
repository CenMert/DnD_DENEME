#pragma once

#include <wx/wx.h>
// Custom dialog class to show a wxChoice control
class ChoiceDialog : public wxDialog
{
public:
    ChoiceDialog(wxWindow* parent, const wxArrayString& choices)
        : wxDialog(parent, wxID_ANY, "Select Session", wxDefaultPosition, wxSize(300, 150))
    {
        // Create the wxChoice control
        m_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
        if (!choices.IsEmpty())
            m_choice->SetSelection(0);
        else {
            wxMessageBox("There is no any selectable items.");
            this->Close();
        }

        // Create OK and Cancel buttons
        wxButton* okButton = new wxButton(this, wxID_OK, "OK");
        wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");

        // Layout using sizers
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->Add(m_choice, 0, wxALL | wxEXPAND, 10);

        wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
        buttonSizer->Add(okButton, 0, wxALL, 5);
        buttonSizer->Add(cancelButton, 0, wxALL, 5);

        mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);
        SetSizerAndFit(mainSizer);
    }

    // Optionally provide a method to get the selected value
    int GetSelection() const { return m_choice->GetSelection(); }
    wxString GetSelectedString() const { return m_choice->GetStringSelection(); }

private:
    wxChoice* m_choice;
};


