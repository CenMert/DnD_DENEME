#pragma once
#include "wx/wx.h"
#include <string>

/*
TODO:
    This function always returns a value either the cancel button pressed.
    You have used this function a few but important places such as Save For new session button in GameFrame.
    You need to add a feature for cancel. adn maybe you can retun a success type to sure about there is a value?
*/

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

