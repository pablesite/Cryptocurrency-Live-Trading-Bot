#include <string>

#include "crypto_gui.h"

enum
{
    ID_Hello = 1
};

wxBEGIN_EVENT_TABLE(CryptoGui, wxFrame)
    EVT_MENU(ID_Hello, CryptoGui::OnHello)
        EVT_MENU(wxID_EXIT, CryptoGui::OnExit)
            EVT_MENU(wxID_ABOUT, CryptoGui::OnAbout)
                wxEND_EVENT_TABLE()

                    wxIMPLEMENT_APP(CryptoBot);

bool CryptoBot::OnInit()
{
    CryptoGui *frame = new CryptoGui("Crypyoconcurrency Live Trading Bot", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);

    return true;
}

CryptoGui::CryptoGui(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    CreateStatusBar();

    wxPanel *panel = new wxPanel(this, -1);
    // wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    // wxCheckBox *cb1 = new wxCheckBox(panel, wxID_ANY,
    //                                  wxT("BitCoint"));

    const wxString str1 = wxT("Linux");
    wxString str2 = wxT("Operating");
    wxString str3 = wxT("System");
    //wxString str[] = [str1, str2, str3];

    wxChoice *ch1 = new wxChoice(panel, wxID_ANY, wxPoint(10,10), wxSize(100,40), 3, &str1, wxCB_SORT | wxCB_DROPDOWN);
    SetStatusText("Welcome to Crypto Gui!");
}

void CryptoGui::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void CryptoGui::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets' Hello world sample",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void CryptoGui::OnHello(wxCommandEvent &event)
{

    wxLogMessage("Hello world from wxWidgets!");

    // wxString newName = wxGetTextFromUser(_("New Diagram Name"), _("Diagram Name"), _("unnamed"), this);
    // wxLogMessage( wxT("The user entered the value %ls"), newName );

    // wxString str1 = wxT("Linux");
    // wxString str2 = wxT("Operating");
    // wxString str3 = wxT("System");
    // wxString str = str1 + wxT(" ") + str2 + wxT(" ") + str3;
    // wxPuts(str);


   

    _cryptoLogic = std::make_unique<CryptoLogic>();
    _cryptoLogic->startSimulation();
}
