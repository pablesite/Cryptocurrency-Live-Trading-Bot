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
    SetStatusText("Welcome to Crypto Gui!");
  
    // Create a new Panel //
    wxPanel *panel = new wxPanel(this, -1);
    bool isFromUser = false;
    CryptoGuiPanel *item = new CryptoGuiPanel(panel, isFromUser);

}

CryptoGuiPanel::CryptoGuiPanel(wxPanel *parent, bool isFromUser)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(800, 450), wxBORDER_NONE) {
    
    // Define Panels
    wxPanel *leftPanel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(250, 450), wxBORDER_NONE);
    wxPanel *rightPanel = new wxPanel(this, -1, wxPoint(250, 0), wxSize(550, 450), wxBORDER_NONE);
    
    // Define Box Sizers
    wxBoxSizer *leftvbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *rightvbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *hleftbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hleftbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hleftbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hleftbox4 = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *hrightbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hrightbox2 = new wxBoxSizer(wxHORIZONTAL);

    // Define elements
    wxButton *createData = new wxButton(leftPanel, -1, wxT("Create Data"));
    wxButton *simulateStrategy = new wxButton(leftPanel, -1, wxT("Simulate strategy"));
    wxButton *cryptoBot = new wxButton(leftPanel, -1, wxT("Crypto Bot"));
    wxButton *stop = new wxButton(leftPanel, -1, wxT("Stop"));

    wxStaticText * staticData = new wxStaticText(rightPanel, -1, "Static Data", wxPoint(-1, -1), wxSize(90, 30), wxALIGN_CENTRE | wxBORDER_NONE);
    wxStaticText * statisticsData = new wxStaticText(rightPanel, wxID_ANY, "Statistics Data", wxPoint(-1, -1), wxSize(90, 30), wxALIGN_CENTRE | wxBORDER_NONE);

    // wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    // wxCheckBox *cb1 = new wxCheckBox(panel, wxID_ANY, wxT("BitCoint"));
    // wxChoice *ch1 = new wxChoice(panel, wxID_ANY, wxPoint(10,10), wxSize(100,40), 3, &str1, wxCB_SORT | wxCB_DROPDOWN);
    
    // const wxString str1 = wxT("Linux");
    // wxString str2 = wxT("Operating");
    // wxString str3 = wxT("System");
    
    // Add elements to Box Sizers
    
    // vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
    leftvbox->Add(hleftbox1, 2, wxEXPAND);
    leftvbox->Add(hleftbox2, 2, wxEXPAND);
    leftvbox->Add(hleftbox3, 2, wxEXPAND);
    leftvbox->Add(hleftbox4, 1, wxEXPAND);

    rightvbox->Add(hrightbox1, 1, wxEXPAND);
    rightvbox->Add(hrightbox2, 2, wxEXPAND);

    hleftbox1->Add(createData,1);
    hleftbox2->Add(simulateStrategy,1);
    hleftbox3->Add(cryptoBot,1);
    hleftbox4->Add(stop,1);

    hrightbox1->Add(staticData, 1);
    hrightbox2->Add(statisticsData, 1);
    
    // Stablish size from Panels
    leftPanel->SetSizer(leftvbox);
    rightPanel->SetSizer(rightvbox);

    // Stablish Background Color to Panels.
    leftPanel->SetBackgroundColour(wxT("YELLOW"));
    rightPanel->SetBackgroundColour(wxT("RED"));

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


