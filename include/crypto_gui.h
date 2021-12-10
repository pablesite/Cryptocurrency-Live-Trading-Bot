#ifndef CRYPTO_GUI_H_
#define CRYPTO_GUI_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <future>
#include "crypto_logic.h"

class CryptoBot: public wxApp
{
public:
    virtual bool OnInit();
};


class CryptoGui: public wxFrame
{
public:
    CryptoGui(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();

    std::unique_ptr<CryptoLogic> _cryptoLogic;
};

#endif