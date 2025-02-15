#pragma once
#include "wx/wx.h"
#include <string>

class QuestionDialog : public wxDialog
{
public:
	QuestionDialog(wxWindow* parent, std::string answer, std::string question)
		: wxDialog(parent, wxID_ANY, "Answer The Question", wxDefaultPosition, wxSize(300, 150))
	{
		this->theAnswer = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
        this->Question = new wxStaticText(this, wxID_ANY, question, wxDefaultPosition, wxDefaultSize);
        // Create OK and Cancel buttons
        wxButton* okButton = new wxButton(this, wxID_OK, "OK");
        wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");

        // Layout using sizers
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->Add(this->theAnswer, 0, wxALL | wxEXPAND, 10);
        mainSizer->Add(this->Question, 0, wxALL | wxEXPAND, 10);

        wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
        buttonSizer->Add(okButton, 0, wxALL, 5);
        buttonSizer->Add(cancelButton, 0, wxALL, 5);

        mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);
        SetSizerAndFit(mainSizer);
	}

    // getters
    wxString GetAnswer() { return this->theAnswer->GetLineText(0); }


private:
	wxTextCtrl* theAnswer;
    wxStaticText* Question;
};

