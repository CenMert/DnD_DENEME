#include "DiceFrame.h"
// Eðer wxGIFDecoder gibi bir yardýmcý kütüphane kullanýyorsanýz, aþaðýdaki satýrý aktif edebilirsiniz.
// #include <wx/gifdecod.h>

enum
{
    ID_ROLL_BUTTON = wxID_HIGHEST + 1
};

wxBEGIN_EVENT_TABLE(DiceFrame, wxFrame)
EVT_BUTTON(ID_ROLL_BUTTON, DiceFrame::OnRoll)
wxEND_EVENT_TABLE()

DiceFrame::DiceFrame(wxWindow* parent, Dice theDice)
    : wxFrame(parent, wxID_ANY, "Rolling Dice Window", wxDefaultPosition, wxSize(250, 300)),
    theDice(theDice)
{
    // Pencere içerisinde ana panel oluþturuluyor.
    wxPanel* panel = new wxPanel(this);

    // 128x128 boyutunda wxAnimationCtrl, gif animasyonlarýný göstermek için oluþturuluyor.
    mGifCtrl = new wxAnimationCtrl(panel, wxID_ANY, wxNullAnimation, wxPoint(10, 10), wxSize(128, 128));

    // "roll" butonu oluþturuluyor.
    mRollButton = new wxButton(panel, ID_ROLL_BUTTON, "roll", wxPoint(10, 150), wxSize(100, 30));

    // Yerleþim düzeni (Sizer) kullanýlarak kontroller hizalanýyor.
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(mGifCtrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    sizer->Add(mRollButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    panel->SetSizer(sizer);
}

void DiceFrame::OnRoll(wxCommandEvent& event)
{
    // Eðer animasyon oynuyorsa, butona yeniden basýldýðýnda animasyonu durdur ve son kareyi göster.
    if (mIsPlaying)
    {
        mGifCtrl->Stop();
        wxBitmap lastFrame = GetLastFrameBitmap(gif_path.string());
        if (lastFrame.IsOk())
        {
            // Eðer daha önce bir statik bitmap oluþturulmamýþsa, oluþtur.
            if (!mStaticBitmap)
            {
                mStaticBitmap = new wxStaticBitmap(mGifCtrl->GetParent(), wxID_ANY, lastFrame,
                    mGifCtrl->GetPosition(), mGifCtrl->GetSize());
            }
            else
            {
                mStaticBitmap->SetBitmap(lastFrame);
            }
            // mGifCtrl gizlenip, statik bitmap gösteriliyor.
            mGifCtrl->Hide();
            mGifCtrl->GetParent()->Layout();
        }
        mIsPlaying = false;
        return;
    }
    else
    {
        // Yeni bir zar atýþý yapmadan önce statik bitmap varsa silinip, animasyon kontrolü görünür hale getiriliyor.
        if (mStaticBitmap)
        {
            mStaticBitmap->Destroy();
            mStaticBitmap = nullptr;
            mGifCtrl->Show();
            mGifCtrl->GetParent()->Layout();
        }
    }

    // Yeni bir zar atýþý yapýlýyor.
    int number = theDice.roll();

    // Zar sonucuna göre gif dosya yolu güncelleniyor.
    switch (number)
    {
    case 1:
        gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_1_example.gif";
        break;
    case 2:
        gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_2_example.gif";
        break;
    case 3:
        gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_3_example.gif";
        break;
    case 4:
        gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_4_example.gif";
        break;
    case 5:
        gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_5_example.gif";
        break;
    case 6:
        gif_path = fs::path("animations") / "dice_animations" / "dice_rolling_6_example.gif";
        break;
    default:
        break;
    }


    wxString fullPath = gif_path.string();
    if (!wxFileName::FileExists(fullPath))
    {
        wxMessageBox("File not found: " + fullPath);
        return;
    }

    // Seçilen gif dosyasý yükleniyor ve oynatýlýyor.
    wxInitAllImageHandlers();
    if (mGifCtrl->LoadFile(gif_path.string(), wxANIMATION_TYPE_GIF))
    {
        mGifCtrl->Show();
        mGifCtrl->Play();
        mIsPlaying = true;
    }
}

wxBitmap DiceFrame::GetLastFrameBitmap(const wxString& gifPath)
{
    /*
    // wxGIFDecoder kullanýmý örneði:
    wxGIFDecoder decoder;
    if (!decoder.Load(gifPath))
        return wxNullBitmap;
    int frameCount = decoder.GetFrameCount();
    if (frameCount <= 0)
        return wxNullBitmap;
    wxImage lastFrame = decoder.GetFrame(frameCount - 1);
    return wxBitmap(lastFrame);
    */

    // Alternatif: Gif dosyasýný normal þekilde yükleyip, elde edilen bitmap'i döndürün.
    wxImage image;
    if (!image.LoadFile(gifPath, wxBITMAP_TYPE_GIF))
        return wxNullBitmap;
    return wxBitmap(image);
}