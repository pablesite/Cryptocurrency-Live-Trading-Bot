#include <string>

#include "crypto_gui.h"
#include "simulate_data.h"
#include "strategy.h"
#include <unordered_map>

std::string dataPath = "../";
std::string imgBasePath = dataPath + "images/";

int secs = 0; // secs for test
std::deque<wxCoord> y_val{};

std::string dataSimulated = "dataSimulated";
std::string strategyDataSimulatedBot = "strategyDataSimulatedBot";
std::string historicData = "historicData";
std::string strategyHistoricBot = "strategyHistoricBot";
std::string binanceData = "binanceData";
std::string strategyBinanceBot = "strategyBinanceBot";

wxButton *simulate_btn;
wxButton *stop_simulate_sim_data_btn;
wxButton *historic_btn;
wxButton *stop_simulate_hist_data_btn;
wxButton *realdata_btn;
wxButton *stop_simulate_real_data_btn;

wxStaticText *x_tick_label0;
wxStaticText *x_tick_label1;
wxStaticText *x_tick_label2;
wxStaticText *x_tick_label3;
wxStaticText *x_tick_label4;

typedef std::unordered_map<std::string, pthread_t> ThreadMap;
ThreadMap thrMap;

bool paintGraphics = true;
wxSize oldSize;
double oldValue;

enum
{
  ID_Hello = wxID_HIGHEST + 1,
  ID_CREATE_HISTORICAL_DATA,
  ID_SIMULATE_DATA,
  ID_SIMULATE_DATA_STOP,
  ID_HISTORICAL_DATA,
  ID_HISTORICAL_DATA_STOP,
  ID_REAL_DATA,
  ID_REAL_DATA_STOP
};

wxBEGIN_EVENT_TABLE(CryptoGui, wxFrame)

    EVT_MENU(ID_Hello, CryptoGui::OnHello)
        EVT_MENU(wxID_EXIT, CryptoGui::OnExit)
            EVT_MENU(wxID_ABOUT, CryptoGui::OnAbout)

                EVT_BUTTON(ID_CREATE_HISTORICAL_DATA, CryptoGuiPanel::OnCreateHistoricalData)
                    EVT_BUTTON(ID_SIMULATE_DATA, CryptoGuiPanel::OnStartSimulatedData)
                        EVT_BUTTON(ID_SIMULATE_DATA_STOP, CryptoGuiPanel::OnStopSimulatedData)
                            EVT_BUTTON(ID_HISTORICAL_DATA, CryptoGuiPanel::OnStartHistoricalData)
                                EVT_BUTTON(ID_HISTORICAL_DATA_STOP, CryptoGuiPanel::OnStopHistoricalData)
                                    EVT_BUTTON(ID_REAL_DATA, CryptoGuiPanel::OnStartRealData)
                                        EVT_BUTTON(ID_REAL_DATA_STOP, CryptoGuiPanel::OnStopRealData)

                                            wxEND_EVENT_TABLE()

                                                wxIMPLEMENT_APP(CryptoBot);

bool CryptoBot::OnInit()
{
  // With header and footer, 88 pixels height extra are needed.
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
  SetStatusText("Created by Pablo Ruiz");

  // Create a new Panel //
  wxPanel *panel = new wxPanel(this, -1);
  bool isFromUser = false;

  _cryptoLogic = std::make_shared<CryptoLogic>();
  CryptoGuiPanel *item = new CryptoGuiPanel(panel, isFromUser, _cryptoLogic);
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
}

void CryptoGui::OnPaint(wxPaintEvent &event) // It is not used
{
  std::cout << "\n ON PAINT DE CRYPTOGUI " << std::endl;
  // Graphic Lines
  wxPaintDC dc(this);
  wxSize size = this->GetSize();

  // Crypto Value
  wxPen pen3(wxT("BLUE"), 1, wxPENSTYLE_DOT_DASH);
  dc.SetPen(pen3);
  // dc.DrawCircle (50, 50, 100);

  // //10 - 50567
  // wxCoord x1 = 10;
  // wxCoord y1 = (51000-50567)*size.y/2000;
  // dc.DrawPoint(x1, y1);

  // //20 - 50435
  // wxCoord x2 = 20;
  // wxCoord y2 = (51000-50435)*size.y/2000;
  // dc.DrawPoint(x2, y2);

  // //30 - 50615
  // wxCoord x3 = 30;
  // wxCoord y3 = (51000-50215)*size.y/2000;
  // dc.DrawPoint(x3, y3);

  // //40 - 49923
  // wxCoord x4 = 40;
  // wxCoord y4 = (51000-49723)*size.y/2000;
  // dc.DrawPoint(x4, y4);

  wxCoord x5 = 0;
  wxCoord y5 = 0;
  for (int i = 1; i < size.x; i++)
  {
    x5 = i;
    y5 = (51000 - 49000 - i) * size.y / 2000;
    dc.DrawPoint(x5, y5);
  }
  // dc.DrawLine(150, 150, 150, 200);
  // dc.DrawPoint(40, 170);

  //   for (int i = 0; i<size.x; i++) {
  //         x = i % size.x + 1;
  //         y = rand() % size.y + 1;
  //         dc.DrawPoint(x, y);
  //   }

  // std::cout << "Sizees: " << size.x << " " << size.y << " " << x4 << " " << y4 << " " << x3 << " " << y3 << std::endl;

  // this->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGui::OnTest));
}

CryptoGuiPanel::CryptoGuiPanel(wxPanel *parent, bool isFromUser, std::shared_ptr<CryptoLogic> cryptoLogic)
{

  // Create Box Sizers
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *vbox1 = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *vbox2 = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hleftbox1 = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hleftbox2 = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hrighttbox1 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *hrighttbox2 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *vrighttbox1 = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *vrighttbox2 = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer *create_label_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *create_action_box = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer *simulate_label_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulate_select_crypto_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulate_select_strategy_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulate_sim_data_buttons_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulate_hist_data_buttons_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulate_real_data_buttons_box = new wxBoxSizer(wxHORIZONTAL);

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
  wxStaticText *create_title_label = new wxStaticText(parent, -1, wxT("Create historic data "));
  wxStaticText *text_create = new wxStaticText(parent, -1, wxT("Push to create data: "));
  wxButton *createData = new wxButton(parent, ID_CREATE_HISTORICAL_DATA, wxT("Create Data"));

  wxStaticLine *line_hor_1 = new wxStaticLine(parent, -1);

  // Inside simulate boxes
  wxStaticText *simulate_label = new wxStaticText(parent, -1, wxT("Simulate your strategy "));
  wxStaticText *simulate_select_crypto_label = new wxStaticText(parent, -1, wxT("Select Crypto: "));
  wxStaticText *simulate_select_strategy_label = new wxStaticText(parent, -1, wxT("Select your strategy: "));

  const wxString simulation_crypto_choices = wxT("Bitcoint");
  wxChoice *simulate_choice_crypto = new wxChoice(parent, -1, wxDefaultPosition, wxDefaultSize, 1, &simulation_crypto_choices, wxCB_SORT | wxCB_DROPDOWN, wxDefaultValidator);

  const wxString simulation_choices = wxT("Simple one");
  wxChoice *simulate_choice_strategy = new wxChoice(parent, -1, wxDefaultPosition, wxDefaultSize, 1, &simulation_choices, wxCB_SORT | wxCB_DROPDOWN, wxDefaultValidator);

  wxStaticText *data_simulated_label = new wxStaticText(parent, -1, wxT("Data Simulated: "));

  simulate_btn = new wxButton(parent, ID_SIMULATE_DATA, wxT("Start"));
  stop_simulate_sim_data_btn = new wxButton(parent, ID_SIMULATE_DATA_STOP, wxT("Stop"));
  stop_simulate_sim_data_btn->Enable(false);
  wxStaticText *historic_data_label = new wxStaticText(parent, -1, wxT("Historic Data: "));
  historic_btn = new wxButton(parent, ID_HISTORICAL_DATA, wxT("Start"));
  stop_simulate_hist_data_btn = new wxButton(parent, ID_HISTORICAL_DATA_STOP, wxT("Stop"));
  stop_simulate_hist_data_btn->Enable(false);
  wxStaticText *realtime_data_label = new wxStaticText(parent, -1, wxT("Real Time Data: "));
  realdata_btn = new wxButton(parent, ID_REAL_DATA, wxT("Start"));
  stop_simulate_real_data_btn = new wxButton(parent, ID_REAL_DATA_STOP, wxT("Stop"));
  stop_simulate_real_data_btn->Enable(false);

  // Separator vertical line
  wxStaticLine *line_ver_1 = new wxStaticLine(parent, -1);

  // Inside vrighttbox1
  wxStaticText *strategy = new wxStaticText(parent, -1, wxT("Strategy: "));
  wxStaticText *data_from = new wxStaticText(parent, -1, wxT("Data from: "));
  wxStaticText *commission = new wxStaticText(parent, -1, wxT("Commission: "));
  wxStaticText *cryptocurrency = new wxStaticText(parent, -1, wxT("Crypto: "));

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

  //// Assign elements ////
  hbox->Add(vbox1, 1, wxEXPAND);
  hbox->Add(line_ver_1, 0, wxEXPAND | wxTOP | wxDOWN | wxLEFT | wxRIGHT, 10);
  hbox->Add(vbox2, 3, wxEXPAND);

  // inside hbox
  vbox1->Add(hleftbox1, 1, wxEXPAND);
  vbox1->Add(line_hor_1, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);
  vbox1->Add(hleftbox2, 3, wxEXPAND);

  vbox2->Add(hrighttbox1, 1, wxEXPAND);
  vbox2->Add(line_hor_4, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);
  vbox2->Add(hrighttbox2, 2, wxEXPAND);

  // inside vbox1
  hleftbox1->Add(create_label_box, 1, wxALIGN_CENTER | wxTOP, 20);
  hleftbox1->Add(create_action_box, 1, wxEXPAND | wxTOP, 0);

  // inside hleftbox2
  hleftbox2->Add(simulate_label_box, 1, wxALIGN_CENTER | wxTOP, 0);
  hleftbox2->Add(simulate_select_crypto_box, 1, wxEXPAND);
  hleftbox2->Add(simulate_select_strategy_box, 1, wxEXPAND);
  hleftbox2->Add(simulate_sim_data_buttons_box, 1, wxEXPAND);
  hleftbox2->Add(simulate_hist_data_buttons_box, 1, wxEXPAND);
  hleftbox2->Add(simulate_real_data_buttons_box, 1, wxEXPAND | wxBOTTOM, 10);

  // inside vbox2
  hrighttbox1->Add(vrighttbox1, 2, wxEXPAND | wxTOP, 20);
  hrighttbox1->Add(line_ver_2, 0, wxEXPAND | wxTOP | wxDOWN | wxLEFT | wxRIGHT, 10);
  hrighttbox1->Add(vrighttbox2, 3, wxEXPAND | wxTOP, 20);

  // inside create_box
  create_label_box->Add(create_title_label, 1, wxALIGN_CENTER_HORIZONTAL | wxLEFT, 10);
  create_action_box->Add(text_create, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  create_action_box->Add(createData, 1, wxALIGN_CENTER, 10);

  // inside simulate_label_box
  simulate_label_box->Add(simulate_label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulate_select_crypto_box->Add(simulate_select_crypto_label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulate_select_crypto_box->Add(simulate_choice_crypto, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulate_select_strategy_box->Add(simulate_select_strategy_label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulate_select_strategy_box->Add(simulate_choice_strategy, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);

  simulate_sim_data_buttons_box->Add(data_simulated_label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  simulate_sim_data_buttons_box->Add(simulate_btn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  simulate_sim_data_buttons_box->Add(stop_simulate_sim_data_btn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);

  simulate_hist_data_buttons_box->Add(historic_data_label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  simulate_hist_data_buttons_box->Add(historic_btn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  simulate_hist_data_buttons_box->Add(stop_simulate_hist_data_btn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);

  simulate_real_data_buttons_box->Add(realtime_data_label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  simulate_real_data_buttons_box->Add(realdata_btn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  simulate_real_data_buttons_box->Add(stop_simulate_real_data_btn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);

  // inside hrighttbox1
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

  // inside vrighttbox1
  strategy_box->Add(strategy, 1, wxALIGN_LEFT | wxLEFT, 20);
  strategy_box->Add(strategy_type, 1, wxALIGN_LEFT);
  // strategy->SetBackgroundColour(wxT("BLUE"));
  strategy_type->SetBackgroundColour(wxT("RED"));
  exchange_box->Add(data_from, 1, wxALIGN_LEFT | wxLEFT, 20);
  exchange_box->Add(exchange, 1, wxALIGN_LEFT);
  commission_box->Add(commission, 1, wxALIGN_LEFT | wxLEFT, 20);
  commission_box->Add(commission_value, 1, wxALIGN_LEFT);
  cryptocurrency_box->Add(cryptocurrency, 1, wxALIGN_LEFT | wxLEFT, 20);
  cryptocurrency_box->Add(cryptocurrency_type, 1, wxALIGN_LEFT);

  // inside vrighttbox2
  position_box->Add(position, 1, wxALIGN_LEFT | wxLEFT, 20);
  position_box->Add(position_bool, 1, wxALIGN_LEFT);
  last_order_cc_box->Add(last_order_cc, 1, wxALIGN_LEFT | wxLEFT, 20);
  last_order_cc_box->Add(last_order_cc_value, 1, wxALIGN_LEFT);
  last_order_$_box->Add(last_order_$, 1, wxALIGN_LEFT | wxLEFT, 20);
  last_order_$_box->Add(last_order_$_value, 1, wxALIGN_LEFT);
  benefits_box->Add(benefits, 1, wxALIGN_LEFT | wxLEFT, 20);
  benefits_box->Add(benefits_value, 1, wxALIGN_LEFT);
  benefits_value->SetBackgroundColour(wxT("RED"));
  benefits_acc_box->Add(benefits_acc, 1, wxALIGN_LEFT | wxLEFT, 20);
  benefits_acc_box->Add(benefits_acc_value, 1, wxALIGN_LEFT);
  interest_box->Add(interest, 1, wxALIGN_LEFT | wxLEFT, 20);
  interest_box->Add(interest_value, 1, wxALIGN_LEFT);

  // Graphics
  // graphics_results = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxPanelNameStr);
  // hrighttbox2->Add(graphics_results, 1, wxEXPAND | wxTOP | wxDOWN | wxLEFT | wxRIGHT, 20);
  // graphics_results->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGui::OnPaint));

  //_cryptoGraphic = std::make_shared<CryptoGraphic>(parent, wxID_ANY);
  _cryptoGraphic = new CryptoGraphic(parent, wxID_ANY);

  hrighttbox2->Add(_cryptoGraphic, 1, wxEXPAND | wxTOP | wxDOWN | wxLEFT | wxRIGHT, 20);
  // cryptoLogic->SetCryptoGraphicHandle(_cryptoGraphic); //ESTO CREO QUE NO ES NECESARIO

  // Stablish size from Panels
  parent->SetSizer(hbox);

  // Stablish Background Color to Panel.
  // this->SetBackgroundColour((isFromUser == true ? wxT("YELLOW") : wxT("BLUE")));
}

// CryptoGuiPanel::~CryptoGuiPanel()
// {}

void CryptoGuiPanel::OnCreateHistoricalData(wxCommandEvent &event)
{

  std::cout << "\nCreating new data series with real data: " << std::endl;

  // REAL DATA IN REAL TIME
  std::shared_ptr<Binance> binancePtr = std::make_shared<Binance>();
  std::thread binanceData = std::thread(&Binance::fetchData, binancePtr);

  // 2. CREATE NEW DATA SERIES
  std::shared_ptr<HistoricData> dataFilePtr = std::make_shared<HistoricData>();
  std::thread writeHistoricData = std::thread(&HistoricData::createHistoricData, dataFilePtr, binancePtr);

  writeHistoricData.detach();
  binanceData.detach();
}

void CryptoGuiPanel::OnStartSimulatedData(wxCommandEvent &event)
{
  std::cout << "\nOn Start Simulated Data: " << std::endl;
  StartStrategy<SimulateData>(dataSimulated, strategyDataSimulatedBot, simulate_btn, stop_simulate_sim_data_btn);
}

void CryptoGuiPanel::OnStopSimulatedData(wxCommandEvent &event)
{
  std::cout << "\nStopping Simulated Data Threads" << std::endl;
  std::vector<std::string> threadsToKill = {dataSimulated, strategyDataSimulatedBot};
  KillThreads(threadsToKill, simulate_btn, stop_simulate_sim_data_btn);
}

void CryptoGuiPanel::OnStartHistoricalData(wxCommandEvent &event)
{
  std::cout << "\nOn Start Historical Data: " << std::endl;
  StartStrategy<HistoricData>(historicData, strategyHistoricBot, historic_btn, stop_simulate_hist_data_btn);
}

void CryptoGuiPanel::OnStopHistoricalData(wxCommandEvent &event)
{
  std::cout << "\nStopping Historical Data Threads" << std::endl;
  std::vector<std::string> threadsToKill = {historicData, strategyHistoricBot};
  KillThreads(threadsToKill, historic_btn, stop_simulate_hist_data_btn);
}

void CryptoGuiPanel::OnStartRealData(wxCommandEvent &event)
{
  std::cout << "\nOn Start Real Data: " << std::endl;
  StartStrategy<Binance>(binanceData, strategyBinanceBot, realdata_btn, stop_simulate_real_data_btn);
}

void CryptoGuiPanel::OnStopRealData(wxCommandEvent &event)
{
  std::cout << "\nStopping Real Data Threads" << std::endl;
  std::vector<std::string> threadsToKill = {binanceData, strategyBinanceBot};
  KillThreads(threadsToKill, realdata_btn, stop_simulate_real_data_btn);
}

template <class T>
void CryptoGuiPanel::StartStrategy(std::string dataThrName, std::string strategyThrName, wxButton *start_btn, wxButton *stop_btn)
{

  // Data thread
  std::shared_ptr<T> dataPtr = std::make_shared<T>();
  std::thread dataThr = std::thread(&T::fetchData, dataPtr);

  // Strategy thread
  std::shared_ptr<Strategy> strategyPtr = std::make_shared<Strategy>(dataPtr);
  strategyPtr->SetCryptoGraphicHandle(_cryptoGraphic);
  std::thread strategyThr = std::thread(&Strategy::cryptoBot, strategyPtr);

  // Save reference for threads
  thrMap[dataThrName] = dataThr.native_handle();
  thrMap[strategyThrName] = strategyThr.native_handle();

  // Manage buttons
  start_btn->Enable(false);
  stop_btn->Enable(true);

  // Detach threads
  dataThr.detach();
  strategyThr.detach();
}

void CryptoGuiPanel::KillThreads(std::vector<std::string> threadsToKill, wxButton *start_btn, wxButton *stop_btn)
{

  ThreadMap::const_iterator it;

  for (std::string thrToKill : threadsToKill)
  {
    it = thrMap.find(thrToKill);
    if (it != thrMap.end())
    {
      pthread_cancel(it->second);
      thrMap.erase(thrToKill);
      std::cout << "Thread " << thrToKill << " killed:" << std::endl;
    }
  }

  // Manage buttons
  start_btn->Enable(true);
  stop_btn->Enable(false);

  std::cout << std::endl;
}

BEGIN_EVENT_TABLE(CryptoGraphic, wxPanel)
// EVT_PAINT(CryptoGraphic::paintEvent) // catch paint events
END_EVENT_TABLE()

CryptoGraphic::CryptoGraphic(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxPanelNameStr)
{
  // sizer will take care of determining the needed scroll size

  //_cryptoGraphicPanel = new wxPanel(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxPanelNameStr);

  //   _dialogSizer = new wxBoxSizer(wxVERTICAL);
  //   this->SetSizer(_dialogSizer);

  // allow for PNG images to be handled
  //   wxInitAllImageHandlers();

  // this->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGui::OnPaint));
  //  create chat logic instance
  /*** TASK 1. create new unique smart pointer in stack ***/

  // _cryptoLogic = std::make_unique<CryptoLogic>();

  // pass pointer to chatbot dialog so answers can be displayed in GUI
  //_cryptoLogic->SetCryptoGraphicHandle(this);

  // load answer graph from file
  //   _cryptoLogic->LoadAnswerGraphFromFile(dataPath + "src/answergraph.txt");

  this->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGraphic::OnPaint));
  x_tick_label0 = new wxStaticText(this, -1, wxT(""));
  x_tick_label1 = new wxStaticText(this, -1, wxT(""));
  x_tick_label2 = new wxStaticText(this, -1, wxT(""));
  x_tick_label3 = new wxStaticText(this, -1, wxT(""));
  x_tick_label4 = new wxStaticText(this, -1, wxT(""));

  // x_tick_label1->SetLabel(wxString::Format(wxT("x: %d"), 243 ));
}

CryptoGraphic::~CryptoGraphic()
{
  // delete _chatLogic;
}

void CryptoGraphic::setActualValue(double value)
{
  _actual_value = value;
  //oldValue = value;
  Refresh();
}

void CryptoGraphic::paintEvent(wxPaintEvent &evt) // It is not used
{

  // // wxPaintDC dc(this);
  // // render(dc);
  // // Graphic Lines
  // wxPaintDC dc(this);
  // wxPen pen1(wxT("BLACK"), 2, wxPENSTYLE_SOLID);
  // dc.SetPen(pen1);
  // wxSize size = this->GetSize();
  // wxCoord xOrig = 0;
  // wxCoord yOrig = size.y - 1;
  // wxCoord xYmax = 0;
  // wxCoord yYmax = 0;
  // wxCoord xXmax = size.x - 1;
  // wxCoord yXmax = size.y - 1;
  // dc.DrawLine(xOrig, yOrig, xYmax, yYmax);
  // dc.DrawLine(xOrig, yOrig, xXmax, yXmax);

  // // Intermediate Lins
  // // wxPen (const wxColour &colour, int width=1, wxPenStyle style=wxPENSTYLE_SOLID)
  // wxPen pen2(wxT("RED"), 2, wxPENSTYLE_DOT_DASH);
  // dc.SetPen(pen2);
  // // dc.DrawCircle (50, 50, 100);
  // wxCoord xUp1 = 0;
  // wxCoord yUp1 = (size.y - 1) / 4;
  // wxCoord xUp2 = size.x - 1;
  // wxCoord yUp2 = (size.y - 1) / 4;
  // wxCoord xDown1 = 0;
  // wxCoord yDown = (size.y - 1) * 3 / 4;
  // wxCoord xDown2 = size.x - 1;
  // wxCoord yDown2 = (size.y - 1) * 3 / 4;
  // dc.DrawLine(xUp1, yUp1, xUp2, yUp2);
  // dc.DrawLine(xDown1, yDown, xDown2, yDown2);
}

void CryptoGraphic::paintNow() // It is not used...
{
  // wxPaintDC dc(this);
  // render(dc);
}


void CryptoGraphic::drawAxis(wxDC &dc, wxSize size)
{
  wxPen pen1(wxT("BLACK"), 2, wxPENSTYLE_SOLID);
  dc.SetPen(pen1);
  wxCoord xOrig = 50;
  wxCoord yOrig = size.y - 30;
  wxCoord xYmax = 50;
  wxCoord yYmax = 0;
  wxCoord xXmax = size.x - 1;
  wxCoord yXmax = size.y - 30;
  dc.DrawLine(xOrig, yOrig, xYmax, yYmax);
  dc.DrawLine(xOrig, yOrig, xXmax, yXmax);
}


int CryptoGraphic::valueToPixel(int value, int sizey)
{
  return (sizey - 30) * (65000 - value) / 65000;
}

void CryptoGraphic::render(wxDC &dc) // It is not used...
{

  wxSize size = this->GetSize();

  if (oldSize != size)
  {
    paintGraphics = false;
    oldSize = size;
    x_tick_label0->SetLabel(wxString::Format(wxT("%d"), 0));
    x_tick_label1->SetLabel(wxString::Format(wxT("%d"), 65000 * 1 / 4));
    x_tick_label2->SetLabel(wxString::Format(wxT("%d"), 65000 * 2 / 4));
    x_tick_label3->SetLabel(wxString::Format(wxT("%d"), 65000 * 3 / 4));
    x_tick_label4->SetLabel(wxString::Format(wxT("%d"), 65000 * 4 / 4));
  }
  else
  {
    if(oldValue !=_actual_value){
      paintGraphics = true;
    }
    
  }

  // Draw axis
  // wxPen pen1(wxT("BLACK"), 2, wxPENSTYLE_SOLID);
  // dc.SetPen(pen1);
  // wxCoord xOrig = 50;
  // wxCoord yOrig = size.y - 30;
  // wxCoord xYmax = 50;
  // wxCoord yYmax = 0;
  // wxCoord xXmax = size.x - 1;
  // wxCoord yXmax = size.y - 30;
  // dc.DrawLine(xOrig, yOrig, xYmax, yYmax);
  // dc.DrawLine(xOrig, yOrig, xXmax, yXmax);
  drawAxis(dc, size);


  // Draw ticks
  wxCoord xOrig = 50;
  
  wxCoord y_tick_0 = (size.y - 10 - 30) * 4 / 4 + 10;
  wxCoord y_tick_1 = (size.y - 10 - 30) * 3 / 4 + 10;
  wxCoord y_tick_2 = (size.y - 10 - 30) * 2 / 4 + 10;
  wxCoord y_tick_3 = (size.y - 10 - 30) * 1 / 4 + 10;
  wxCoord y_tick_4 = 10;

  dc.DrawLine(45, y_tick_0, xOrig, y_tick_0);
  dc.DrawLine(45, y_tick_1, xOrig, y_tick_1);
  dc.DrawLine(45, y_tick_2, xOrig, y_tick_2);
  dc.DrawLine(45, y_tick_3, xOrig, y_tick_3);
  dc.DrawLine(45, y_tick_4, xOrig, y_tick_4);

  x_tick_label0->SetPosition(wxPoint(0, y_tick_0 - 9));
  x_tick_label1->SetPosition(wxPoint(0, y_tick_1 - 9));
  x_tick_label2->SetPosition(wxPoint(0, y_tick_2 - 9));
  x_tick_label3->SetPosition(wxPoint(0, y_tick_3 - 9));
  x_tick_label4->SetPosition(wxPoint(0, y_tick_4 - 9));

  // Draw Quartiles
  wxPen pen2(wxT("RED"), 2, wxPENSTYLE_DOT_DASH);
  dc.SetPen(pen2);

  wxCoord xUp1 = 50;
  wxCoord yUp1 = y_tick_1;
  wxCoord xUp2 = size.x - 1;
  wxCoord yUp2 = y_tick_1;
  wxCoord xDown1 = 50;
  wxCoord yDown = y_tick_3;
  wxCoord xDown2 = size.x - 1;
  wxCoord yDown2 = y_tick_3;
  dc.DrawLine(xUp1, yUp1, xUp2, yUp2);
  dc.DrawLine(xDown1, yDown, xDown2, yDown2);

  std::cout << xDown1 << " " << yDown << " " << xDown2 << " " << yDown2 << std::endl;

  // Draw line of value
  wxPen pen3(wxT("GREEN"), 3, wxPENSTYLE_DOT_DASH);
  dc.SetPen(pen3);

  std::deque<wxCoord> x_val{};
  for (size_t z = 0; z < 10; ++z)
  {
    x_val.emplace_back(50 + (z * size.x) / 10); // 60 are the seconds to represent in the plot
    // std::cout << " " << 50+(z * size.x)/10<< " " << std::endl;
  }

  for (size_t i = 0; i < y_val.size(); ++i)
  {
    if (i >= 1)
    {
      dc.DrawLine(x_val[i - 1], valueToPixel(y_val[i - 1], size.y), x_val[i], valueToPixel(y_val[i], size.y));
    }
  }

  // Update line of values
  if (paintGraphics)
  {

    y_val.emplace_back(_actual_value);
    oldValue =_actual_value;
    if (y_val.size() > 10)
    {
      y_val.pop_front();
    }
  }
}

void CryptoGraphic::OnPaint(wxPaintEvent &event)
{
  wxPaintDC dc(this);
  render(dc);
}