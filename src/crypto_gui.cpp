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
    CryptoGui *frame = new CryptoGui("Crypyoconcurrency Live Trading Bot", wxPoint(50, 50), wxSize(965, 538));
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

// CryptoGuiPanel::CryptoGuiPanel(wxPanel *parent, bool isFromUser)
//     : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(800, 450), wxBORDER_NONE) {

CryptoGuiPanel::CryptoGuiPanel(wxPanel *parent, bool isFromUser)
{
    // Create Box Sizers
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vbox1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *vbox2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hleftbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hleftbox2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hleftbox3 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hleftbox4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hrighttbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hrighttbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vrighttbox1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *vrighttbox2 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *create_box = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *simulate_select_box = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *simulate_buttons_box = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *select_crypto_box = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *buttons_crypto_box = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *strategy_box = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *exchange_box = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *commission_box = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *cryptocurrency_box = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *position_box = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *last_order_cc_box = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *last_order_$_box = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *benefits_box = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *benefits_acc_box = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *interest_box = new wxBoxSizer(wxHORIZONTAL);


    //// Define elements ////
    
    // Inside create_box
    wxStaticText *text_create = new wxStaticText(parent, -1, wxT("Create historic data: "));
    wxButton *createData = new wxButton(parent, -1, wxT("Create Data"));

    wxStaticLine *line_hor_1 = new wxStaticLine(parent, -1);

    // Inside simulate boxes
    wxStaticText *simulate_label = new wxStaticText(parent, -1, wxT("Simulate your strategy here: "));
    
    const wxString choices = wxT("Simple one");
    wxChoice *simulate_choice = new wxChoice(parent, -1, wxDefaultPosition, wxDefaultSize, 1, &choices, wxCB_SORT | wxCB_DROPDOWN, wxDefaultValidator);
    
    wxButton *simulate_btn = new wxButton(parent, -1, wxT("Simulate"));
    wxButton *historic_btn = new wxButton(parent, -1, wxT("Historic Data"));
    wxButton *realdata_btn = new wxButton(parent, -1, wxT("Real Data"));

    wxStaticLine *line_hor_2 = new wxStaticLine(parent, -1);

    // Inside crypto_box (TODO)
    wxStaticText *text_crypto = new wxStaticText(parent, -1, wxT("Start Crypto Bot "));
    wxStaticText *text_select_crypto = new wxStaticText(parent, -1, wxT("Select cryptoconcurrency: "));
    wxButton *cryptoBot = new wxButton(parent, -1, wxT("Start Crypto Bot"));

    wxStaticLine *line_hor_3 = new wxStaticLine(parent, -1);

    // Inside stop_box (TODO)
    wxButton *stop = new wxButton(parent, -1, wxT("Stop"));

    // Separator vertical line
    wxStaticLine *line_ver_1 = new wxStaticLine(parent, -1);

    // Inside vrighttbox1
    wxStaticText *strategy = new wxStaticText(parent, -1, wxT("Strategy: "));
    wxStaticText *data_from = new wxStaticText(parent, -1, wxT("Data from: "));
    wxStaticText *commission = new wxStaticText(parent, -1, wxT("Commission: "));
    wxStaticText *cryptocurrency = new wxStaticText(parent, -1, wxT("Cryptocurrency: "));

            // Set text variables (TO DO) //
    strategy_type = new wxStaticText(parent, -1, wxT("Simple"));
    exchange = new wxStaticText(parent, -1, wxT("Binance"));
    commission_value = new wxStaticText(parent, -1, wxT("0.000075"));
    cryptocurrency_type = new wxStaticText(parent, -1, wxT("Bitcoint"));

    wxStaticLine *line_ver_2 = new wxStaticLine(parent, -1);

    // Inside vrighttbox2
    wxStaticText *position = new wxStaticText(parent, -1, wxT("Position: "));
    wxStaticText *last_order_cc = new wxStaticText(parent, -1, wxT("Last order (cc): "));
    wxStaticText *last_order_$ = new wxStaticText(parent, -1, wxT("Last order ($): "));
    wxStaticText *benefits = new wxStaticText(parent, -1, wxT("Benefits in last order ($): "));
    wxStaticText *benefits_acc = new wxStaticText(parent, -1, wxT("Benefits accumulated ($): "));
    wxStaticText *interest = new wxStaticText(parent, -1, wxT("Interest (%): "));
            
            // Set text variables (TO DO) //
    position_bool = new wxStaticText(parent, -1, wxT("Open"));
    last_order_cc_value = new wxStaticText(parent, -1, wxT("0.004"));
    last_order_$_value = new wxStaticText(parent, -1, wxT("192.48"));
    benefits_value = new wxStaticText(parent, -1, wxT("0.35"));
    benefits_acc_value = new wxStaticText(parent, -1, wxT("7.17"));
    interest_value = new wxStaticText(parent, -1, wxT("2.47"));

    // Separator horizontal line
    wxStaticLine *line_hor_4 = new wxStaticLine(parent, -1);

    // Inside graphics box (TODO)
    wxStaticText *graphics = new wxStaticText(parent, -1, wxT("Graphics: "));


    //// Assign elements ////
    hbox->Add(vbox1, 0, wxEXPAND);
    hbox->Add(line_ver_1, 0, wxEXPAND | wxTOP | wxDOWN | wxLEFT | wxRIGHT, 10);
    hbox->Add(vbox2, 1, wxEXPAND);

    //inside hbox
    vbox1->Add(hleftbox1, 2, wxEXPAND);
    vbox1->Add(line_hor_1, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);
    vbox1->Add(hleftbox2, 3, wxEXPAND);
    vbox1->Add(line_hor_2, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);
    vbox1->Add(hleftbox3, 2, wxEXPAND);
    vbox1->Add(line_hor_3, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);
    vbox1->Add(hleftbox4, 0, wxEXPAND);

    vbox2->Add(hrighttbox1, 1, wxEXPAND);
    vbox2->Add(line_hor_4, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);
    vbox2->Add(hrighttbox2, 2, wxEXPAND);
    

    //inside vbox1
    hleftbox1->Add(create_box, 1, wxALIGN_CENTER_VERTICAL | wxTOP, 0);

    //inside hleftbox2
    hleftbox2->Add(simulate_select_box, 1, wxALIGN_CENTER_VERTICAL | wxTOP, 0);
    hleftbox2->Add(simulate_buttons_box, 1, wxEXPAND);

    //inside hleftbox3
    hleftbox3->Add(select_crypto_box, 1, wxALIGN_CENTER_VERTICAL | wxTOP, 0);
    hleftbox3->Add(buttons_crypto_box, 1, wxALIGN_CENTER);

    hleftbox4->Add(stop, 1, wxTOP | wxBOTTOM, 20);

    //inside vbox2
    hrighttbox1->Add(vrighttbox1, 2, wxEXPAND | wxTOP, 20);
    hrighttbox1->Add(line_ver_2, 0, wxEXPAND | wxTOP | wxDOWN | wxLEFT | wxRIGHT, 10);
    hrighttbox1->Add(vrighttbox2, 3, wxEXPAND | wxTOP, 20);

    hrighttbox2->Add(graphics,1);

    //inside create_box
    create_box->Add(text_create, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
    create_box->Add(createData, 1, wxALIGN_CENTER, 10);

    //inside simulate_label_box
    simulate_select_box->Add(simulate_label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
    simulate_select_box->Add(simulate_choice, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
    simulate_buttons_box->Add(simulate_btn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
    simulate_buttons_box->Add(historic_btn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
    simulate_buttons_box->Add(realdata_btn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);

    //inside crypto boxes



    select_crypto_box->Add(text_crypto, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
    select_crypto_box->Add(text_select_crypto, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);

    buttons_crypto_box->Add(cryptoBot, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);



    //inside hrighttbox1
    vrighttbox1->Add(strategy_box, 1, wxEXPAND);
    vrighttbox1->Add(exchange_box, 1, wxEXPAND);
    vrighttbox1->Add(commission_box, 1, wxEXPAND);
    vrighttbox1->Add(cryptocurrency_box, 1, wxEXPAND);
    
    vrighttbox2->Add(position_box, 1, wxEXPAND);
    vrighttbox2->Add(last_order_cc_box, 1, wxEXPAND);
    vrighttbox2->Add(last_order_$_box, 1, wxEXPAND);
    vrighttbox2->Add(benefits_box, 1, wxEXPAND);
    vrighttbox2->Add(benefits_acc_box, 1, wxEXPAND);
    vrighttbox2->Add(interest_box, 1, wxEXPAND);

    //inside vrighttbox1
    strategy_box->Add(strategy, 1, wxALIGN_LEFT | wxLEFT, 20);
    strategy_box->Add(strategy_type, 1, wxALIGN_LEFT);
    // strategy->SetBackgroundColour(wxT("BLUE"));
    strategy_type->SetBackgroundColour(wxT("RED"));
    exchange_box->Add(data_from, 1, wxALIGN_LEFT | wxLEFT, 20);
    exchange_box->Add(exchange,1, wxALIGN_LEFT);
    commission_box->Add(commission, 1, wxALIGN_LEFT | wxLEFT, 20);
    commission_box->Add(commission_value,1, wxALIGN_LEFT);
    cryptocurrency_box->Add(cryptocurrency, 1, wxALIGN_LEFT | wxLEFT, 20);
    cryptocurrency_box->Add(cryptocurrency_type,1, wxALIGN_LEFT);

    //inside vrighttbox2
    position_box->Add(position, 1, wxALIGN_LEFT | wxLEFT, 20);
    position_box->Add(position_bool,1, wxALIGN_LEFT);
    last_order_cc_box->Add(last_order_cc, 1, wxALIGN_LEFT | wxLEFT, 20);
    last_order_cc_box->Add(last_order_cc_value,1, wxALIGN_LEFT);
    last_order_$_box->Add(last_order_$, 1, wxALIGN_LEFT | wxLEFT, 20);
    last_order_$_box->Add(last_order_$_value,1, wxALIGN_LEFT);
    benefits_box->Add(benefits, 1, wxALIGN_LEFT | wxLEFT, 20);
    benefits_box->Add(benefits_value,1, wxALIGN_LEFT);
    benefits_value->SetBackgroundColour(wxT("RED"));
    benefits_acc_box->Add(benefits_acc, 1, wxALIGN_LEFT | wxLEFT, 20);
    benefits_acc_box->Add(benefits_acc_value,1, wxALIGN_LEFT);
    interest_box->Add(interest, 1, wxALIGN_LEFT | wxLEFT, 20);
    interest_box->Add(interest_value,1, wxALIGN_LEFT);


    // Stablish size from Panels
    parent->SetSizer(hbox);

    // Stablish Background Color to Panel.
    //this->SetBackgroundColour((isFromUser == true ? wxT("YELLOW") : wxT("BLUE")));
    
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
