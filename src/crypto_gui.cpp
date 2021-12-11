#include <string>

#include "crypto_gui.h"

std::string dataPath = "../";
std::string imgBasePath = dataPath + "images/";

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
    //With header and footer, 88 pixels height extra are needed.
    CryptoGui *frame = new CryptoGui("Crypyoconcurrency Live Trading Bot", wxPoint(50, 50), wxSize(800, 538));
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

    
    // wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    // wxCheckBox *cb1 = new wxCheckBox(panel, wxID_ANY,
    //                                  wxT("BitCoint"));

    // const wxString str1 = wxT("Linux");
    // wxString str2 = wxT("Operating");
    // wxString str3 = wxT("System");
    // //wxString str[] = [str1, str2, str3];

    // wxChoice *ch1 = new wxChoice(panel, wxID_ANY, wxPoint(10,10), wxSize(100,40), 3, &str1, wxCB_SORT | wxCB_DROPDOWN);
    // SetStatusText("Welcome to Crypto Gui!");

    wxPanel *panel = new wxPanel(this, -1);
    bool isFromUser = false;
    CryptoGuiPanel *item = new CryptoGuiPanel(panel, isFromUser);

}

CryptoGuiPanel::CryptoGuiPanel(wxPanel *parent, bool isFromUser)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(800, 450), wxBORDER_NONE) {
  // retrieve image from chatbot
  //wxBitmap *bitmap = isFromUser == true ? nullptr: nullptr;

    
//     std::string text = "text of proof";
//   // create image and text
//   //_chatBotImg = new wxStaticBitmap(this, wxID_ANY, (isFromUser ? wxBitmap(imgBasePath + "user.png", wxBITMAP_TYPE_PNG) : *bitmap), wxPoint(-1, -1), wxSize(-1, -1));
//   _cryptoTxt = new wxStaticText(this, wxID_ANY, text, wxPoint(-1, -1), wxSize(90, 30), wxALIGN_CENTRE | wxBORDER_NONE);
//   _cryptoTxt->SetForegroundColour(isFromUser == true ? wxColor(*wxBLACK): wxColor(*wxWHITE));

  // create sizer and add elements
//   wxBoxSizer *horzBoxSizer = new wxBoxSizer(wxHORIZONTAL);
//   horzBoxSizer->Add(_cryptoTxt, 8, wxEXPAND | wxALL, 1);
//   //horzBoxSizer->Add(_cryptoTxt, 2, wxEXPAND | wxALL, 1);
//   //horzBoxSizer->Add(_chatBotImg, 2, wxEXPAND | wxALL, 1);
//   this->SetSizer(horzBoxSizer);

  // wrap text after 150 pixels
//   _cryptoTxt->Wrap(150);

//   _cryptoTxt->SetBackgroundColour((isFromUser == true ? wxT("YELLOW") : wxT("RED")));

    wxPanel *leftPanel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(250, 450), wxBORDER_NONE);
    wxBoxSizer *leftvbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    // wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);

    wxButton *ok = new wxButton(this, -1, wxT("Ok"));
    wxButton *cancel = new wxButton(this, -1, wxT("Cancel"));

    // hbox1->Add(new wxPanel(leftPanel, -1));
    // vbox->Add(hbox1, 1, wxEXPAND);
    // vbox->Add(new wxPanel(leftPanel, -1));
    leftvbox->Add(ok,1);
    leftvbox->Add(cancel,3);

    // hbox2->Add(ok);
    // hbox2->Add(cancel);

    // vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
    leftPanel->SetSizer(leftvbox);
    leftPanel->SetBackgroundColour(wxT("YELLOW"));
    // Centre();


  // set background color
  this->SetBackgroundColour((isFromUser == true ? wxT("YELLOW") : wxT("BLUE")));
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


