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
    // Roll butonuna týklanýldýðýnda çalýþacak event handler
    void OnRoll(wxCommandEvent& event);

    // Yardýmcý fonksiyon: Belirtilen gif dosyasýndan son kareyi wxBitmap olarak döndürür.
    wxBitmap GetLastFrameBitmap(const wxString& gifPath);

    // Zar nesnesi ve gif dosya yolu
    Dice theDice;
    fs::path gif_path;

    // 128x128 boyutlu gif animasyonlarýný göstermek için kontrol (wxAnimationCtrl kullanýlýyor)
    wxAnimationCtrl* mGifCtrl;
    // "roll" butonu
    wxButton* mRollButton;
    // Animasyon oynuyor mu?
    bool mIsPlaying = false;
    // Animasyon durduðunda son kareyi göstermek için kullanýlacak statik bitmap
    wxStaticBitmap* mStaticBitmap = nullptr;

    wxDECLARE_EVENT_TABLE();
};
