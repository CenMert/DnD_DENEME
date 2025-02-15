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
    // Roll butonuna tıklanıldığında çalışacak event handler
    void OnRoll(wxCommandEvent& event);

    // Yardımcı fonksiyon: Belirtilen gif dosyasından son kareyi wxBitmap olarak döndürür.
    wxBitmap GetLastFrameBitmap(const wxString& gifPath);

    // Zar nesnesi ve gif dosya yolu
    Dice theDice;
    fs::path gif_path;

    // 128x128 boyutlu gif animasyonlarını göstermek için kontrol (wxAnimationCtrl kullanılıyor)
    wxAnimationCtrl* mGifCtrl;
    // "roll" butonu
    wxButton* mRollButton;
    // Animasyon oynuyor mu?
    bool mIsPlaying = false;
    // Animasyon durduğunda son kareyi göstermek için kullanılacak statik bitmap
    wxStaticBitmap* mStaticBitmap = nullptr;

    wxDECLARE_EVENT_TABLE();
};
