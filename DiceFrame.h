#pragma once
#include <wx/wx.h>
#include <wx/animate.h>
#include <wx/filename.h>
#include <filesystem>

#include "GameManager.h"
#include "Dice.h"

namespace fs = std::filesystem;

class DiceFrame : public wxFrame
{
public:
    DiceFrame(wxWindow* parent, Dice theDice);

private:
    // Roll butonuna t�klan�ld���nda �al��acak event handler
    void OnRoll(wxCommandEvent& event);

    // Yard�mc� fonksiyon: Belirtilen gif dosyas�ndan son kareyi wxBitmap olarak d�nd�r�r.
    wxBitmap GetLastFrameBitmap(const wxString& gifPath);

    // Zar nesnesi ve gif dosya yolu
    Dice theDice;
    fs::path gif_path;

    // 128x128 boyutlu gif animasyonlar�n� g�stermek i�in kontrol (wxAnimationCtrl kullan�l�yor)
    wxAnimationCtrl* mGifCtrl;
    // "roll" butonu
    wxButton* mRollButton;
    // Animasyon oynuyor mu?
    bool mIsPlaying = false;
    // Animasyon durdu�unda son kareyi g�stermek i�in kullan�lacak statik bitmap
    wxStaticBitmap* mStaticBitmap = nullptr;

    wxDECLARE_EVENT_TABLE();
};
