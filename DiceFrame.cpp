#include "DiceFrame.h"
// E�er wxGIFDecoder gibi bir yard�mc� k�t�phane kullan�yorsan�z, a�a��daki sat�r� aktif edebilirsiniz.
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
    // Pencere i�erisinde ana panel olu�turuluyor.
    wxPanel* panel = new wxPanel(this);

    // 128x128 boyutunda wxAnimationCtrl, gif animasyonlar�n� g�stermek i�in olu�turuluyor.
    mGifCtrl = new wxAnimationCtrl(panel, wxID_ANY, wxNullAnimation, wxPoint(10, 10), wxSize(128, 128));

    // "roll" butonu olu�turuluyor.
    mRollButton = new wxButton(panel, ID_ROLL_BUTTON, "roll", wxPoint(10, 150), wxSize(100, 30));

    // Yerle�im d�zeni (Sizer) kullan�larak kontroller hizalan�yor.
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(mGifCtrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    sizer->Add(mRollButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    panel->SetSizer(sizer);
}

void DiceFrame::OnRoll(wxCommandEvent& event)
{
    // E�er animasyon oynuyorsa, butona yeniden bas�ld���nda animasyonu durdur ve son kareyi g�ster.
    if (mIsPlaying)
    {
        mGifCtrl->Stop();
        wxBitmap lastFrame = GetLastFrameBitmap(gif_path.string());
        if (lastFrame.IsOk())
        {
            // E�er daha �nce bir statik bitmap olu�turulmam��sa, olu�tur.
            if (!mStaticBitmap)
            {
                mStaticBitmap = new wxStaticBitmap(mGifCtrl->GetParent(), wxID_ANY, lastFrame,
                    mGifCtrl->GetPosition(), mGifCtrl->GetSize());
            }
            else
            {
                mStaticBitmap->SetBitmap(lastFrame);
            }
            // mGifCtrl gizlenip, statik bitmap g�steriliyor.
            mGifCtrl->Hide();
            mGifCtrl->GetParent()->Layout();
        }
        mIsPlaying = false;
        return;
    }
    else
    {
        // Yeni bir zar at��� yapmadan �nce statik bitmap varsa silinip, animasyon kontrol� g�r�n�r hale getiriliyor.
        if (mStaticBitmap)
        {
            mStaticBitmap->Destroy();
            mStaticBitmap = nullptr;
            mGifCtrl->Show();
            mGifCtrl->GetParent()->Layout();
        }
    }

    // Yeni bir zar at��� yap�l�yor.
    int number = theDice.roll();

    // Zar sonucuna g�re gif dosya yolu g�ncelleniyor.
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

    // Se�ilen gif dosyas� y�kleniyor ve oynat�l�yor.
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
    // wxGIFDecoder kullan�m� �rne�i:
    wxGIFDecoder decoder;
    if (!decoder.Load(gifPath))
        return wxNullBitmap;
    int frameCount = decoder.GetFrameCount();
    if (frameCount <= 0)
        return wxNullBitmap;
    wxImage lastFrame = decoder.GetFrame(frameCount - 1);
    return wxBitmap(lastFrame);
    */

    // Alternatif: Gif dosyas�n� normal �ekilde y�kleyip, elde edilen bitmap'i d�nd�r�n.
    wxImage image;
    if (!image.LoadFile(gifPath, wxBITMAP_TYPE_GIF))
        return wxNullBitmap;
    return wxBitmap(image);
}