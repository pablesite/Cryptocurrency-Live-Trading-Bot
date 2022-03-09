

#include "crypto_gui.h"

typedef std::unordered_map<std::string, pthread_t> ThreadMap;
ThreadMap thrMap;

wxButton *simulate_btn;
wxButton *stop_simulate_sim_data_btn;
wxButton *historic_btn;
wxButton *stop_simulate_hist_data_btn;
wxButton *realdata_btn;
wxButton *stop_simulate_real_data_btn;

std::string dataSimulated = "dataSimulated";
std::string strategyDataSimulatedBot = "strategyDataSimulatedBot";
std::string historicData = "historicData";
std::string strategyHistoricBot = "strategyHistoricBot";
std::string binanceData = "binanceData";
std::string strategyBinanceBot = "strategyBinanceBot";

wxBEGIN_EVENT_TABLE(CryptoGui, wxFrame)

    EVT_MENU(ID_CONFIGURE_STRATEGY, CryptoGui::OnConfigureStrategy)
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
  CryptoGui *frame = new CryptoGui("Cryptoconcurrency Live Trading Bot", wxPoint(50, 50), wxSize(965, 538));
  frame->Show(true);

  return true;
}

CryptoGui::CryptoGui(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{

  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID_CONFIGURE_STRATEGY, "&Configure Strategy...\tCtrl-H",
                   "You can configure input data of strategy from here");
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

  //_cryptoGuiPanel = new CryptoGuiPanel(panel, isFromUser);
  _cryptoGuiPanel = std::make_shared<CryptoGuiPanel>(panel, isFromUser);
}

void CryptoGui::OnExit(wxCommandEvent &event)
{
  Close(true);
}

void CryptoGui::OnAbout(wxCommandEvent &event)
{
  wxMessageBox("This is CryptoBot. Created by Pablo Ruiz",
               "About CryptoBot", wxOK | wxICON_INFORMATION);
}

void CryptoGui::OnConfigureStrategy(wxCommandEvent &event)
{
  wxLogMessage("To do: wxPanel to configure input data of strategy");
}

// void CryptoGui::OnPaint(wxPaintEvent &event) // It is not used
// {

// }

std::string simple_tokenizer(std::string s)
{
  // std::unique_lock<std::mutex> lck(_mtx);
  std::stringstream ss(s);
  std::string word;
  if (ss >> word)
  {
    return word;
  }
  else
  {
    return s;
  }
  // lck.unlock();
}

CryptoGuiPanel::CryptoGuiPanel(wxPanel *parent, bool isFromUser)
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
  wxBoxSizer *simulate_select_exchange_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulate_select_crypto_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulate_select_investment_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulate_select_strategy_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulate_sim_data_buttons_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulate_hist_data_buttons_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulate_real_data_buttons_box = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer *strategy_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *exchange_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *commission_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *cryptocurrency_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *investment_box = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer *position_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *last_order_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *benefits_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *interest_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *number_of_orders_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *benefits_acc_box = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *interest_acc_box = new wxBoxSizer(wxHORIZONTAL);

  //// Define elements ////

  // Inside create_box
  wxStaticText *create_title_label = new wxStaticText(parent, -1, wxT("Create historic data "));
  wxStaticText *text_create = new wxStaticText(parent, -1, wxT("Push to create data: "));
  wxButton *createData = new wxButton(parent, ID_CREATE_HISTORICAL_DATA, wxT("Create Data"));

  wxStaticLine *line_hor_1 = new wxStaticLine(parent, -1);

  // Inside simulate boxes
  wxStaticText *simulate_label = new wxStaticText(parent, -1, wxT("Simulate your strategy "));
  wxStaticText *simulate_select_exchange_label = new wxStaticText(parent, -1, wxT("Select Exchange: "));
  wxStaticText *simulate_select_crypto_label = new wxStaticText(parent, -1, wxT("Select Cryptoconcurrency: "));
  wxStaticText *simulate_select_investment_label = new wxStaticText(parent, -1, wxT("Select Investment: "));
  wxStaticText *simulate_select_strategy_label = new wxStaticText(parent, -1, wxT("Select your strategy: "));

  const wxString simulation_exchange_choices = wxT("Binance");
  wxChoice *simulate_choice_exchange = new wxChoice(parent, -1, wxDefaultPosition, wxDefaultSize, 1, &simulation_exchange_choices, wxCB_SORT | wxCB_DROPDOWN, wxDefaultValidator);
  simulate_choice_exchange->SetSelection(0);
  _exchange = simulate_choice_exchange->GetString(simulate_choice_exchange->GetSelection());

  const wxString simulation_crypto_choices = wxT("Bitcoint");
  wxChoice *simulate_choice_crypto = new wxChoice(parent, -1, wxDefaultPosition, wxDefaultSize, 1, &simulation_crypto_choices, wxCB_SORT | wxCB_DROPDOWN, wxDefaultValidator);
  simulate_choice_crypto->SetSelection(0);
  _cryptoConcurrency = simulate_choice_crypto->GetString(simulate_choice_crypto->GetSelection());

  const wxString simulation_strategy_choices = wxT("Standard");
  wxChoice *simulate_choice_strategy = new wxChoice(parent, -1, wxDefaultPosition, wxDefaultSize, 1, &simulation_strategy_choices, wxCB_SORT | wxCB_DROPDOWN, wxDefaultValidator);
  simulate_choice_strategy->SetSelection(0);
  _strategy = simulate_choice_strategy->GetString(simulate_choice_strategy->GetSelection());

  const wxString simulation_investment_choices = wxT("50 $");
  wxChoice *simulate_choice_investment = new wxChoice(parent, -1, wxDefaultPosition, wxDefaultSize, 1, &simulation_investment_choices, wxCB_SORT | wxCB_DROPDOWN, wxDefaultValidator);
  simulate_choice_investment->SetSelection(0);
  _investment = simulate_choice_investment->GetString(simulate_choice_investment->GetSelection());

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
  wxStaticText *data_from = new wxStaticText(parent, -1, wxT("Data from: "));
  wxStaticText *commission = new wxStaticText(parent, -1, wxT("Commission: "));
  wxStaticText *cryptocurrency = new wxStaticText(parent, -1, wxT("Crypto: "));
  wxStaticText *investment = new wxStaticText(parent, -1, wxT("Investment: "));
  wxStaticText *strategy = new wxStaticText(parent, -1, wxT("Strategy: "));

  // Set text variables
  _exchangeTxt = new wxStaticText(parent, -1, _exchange);
  _commissionValue = new wxStaticText(parent, -1, wxT("0.075 %"));
  _cryptocurrencyType = new wxStaticText(parent, -1, _cryptoConcurrency);
  _investmentValue = new wxStaticText(parent, -1, _investment);
  _strategyType = new wxStaticText(parent, -1, _strategy);

  // Separator vertical line
  wxStaticLine *line_ver_2 = new wxStaticLine(parent, -1);

  // Inside vrighttbox2
  wxStaticText *position = new wxStaticText(parent, -1, wxT("Open position: "));
  wxStaticText *last_order = new wxStaticText(parent, -1, wxT("Last order (btc): "));
  wxStaticText *benefits = new wxStaticText(parent, -1, wxT("Benefits ($): "));
  wxStaticText *interest = new wxStaticText(parent, -1, wxT("Interest (%): "));
  wxStaticText *number_of_orders = new wxStaticText(parent, -1, wxT("Number of orders: "));
  wxStaticText *benefits_acc = new wxStaticText(parent, -1, wxT("Benefits accumulated ($): "));
  wxStaticText *interest_acc = new wxStaticText(parent, -1, wxT("Interest accumulated (%): "));

  // Set text variables (TO DO) //
  _openPositionValue = new wxStaticText(parent, -1, wxT("False"));
  _lastOrderValue = new wxStaticText(parent, -1, wxT("0"));
  _benefitsValue = new wxStaticText(parent, -1, wxT("0"));
  _interestValue = new wxStaticText(parent, -1, wxT("0"));
  _numberOfOrdersValue = new wxStaticText(parent, -1, wxT("0"));
  _benefitsAccValue = new wxStaticText(parent, -1, wxT("0"));
  _interestAccValue = new wxStaticText(parent, -1, wxT("0"));

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
  hleftbox2->Add(simulate_select_exchange_box, 1, wxEXPAND);
  hleftbox2->Add(simulate_select_crypto_box, 1, wxEXPAND);
  hleftbox2->Add(simulate_select_investment_box, 1, wxEXPAND);
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
  simulate_select_exchange_box->Add(simulate_select_exchange_label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulate_select_exchange_box->Add(simulate_choice_exchange, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulate_select_crypto_box->Add(simulate_select_crypto_label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulate_select_crypto_box->Add(simulate_choice_crypto, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulate_select_investment_box->Add(simulate_select_investment_label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulate_select_investment_box->Add(simulate_choice_investment, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
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
  vrighttbox1->Add(exchange_box, 1, wxEXPAND);
  vrighttbox1->Add(commission_box, 1, wxEXPAND);
  vrighttbox1->Add(cryptocurrency_box, 1, wxEXPAND);
  vrighttbox1->Add(investment_box, 1, wxEXPAND);
  vrighttbox1->Add(strategy_box, 1, wxEXPAND);

  vrighttbox2->Add(position_box, 1, wxEXPAND);
  vrighttbox2->Add(last_order_box, 1, wxEXPAND);
  vrighttbox2->Add(benefits_box, 1, wxEXPAND);
  vrighttbox2->Add(interest_box, 1, wxEXPAND);
  vrighttbox2->Add(number_of_orders_box, 1, wxEXPAND);
  vrighttbox2->Add(benefits_acc_box, 1, wxEXPAND);
  vrighttbox2->Add(interest_acc_box, 1, wxEXPAND);

  // inside vrighttbox1
  strategy_box->Add(strategy, 1, wxALIGN_LEFT | wxLEFT, 20);
  strategy_box->Add(_strategyType, 1, wxALIGN_LEFT);
  // strategy->SetBackgroundColour(wxT("BLUE"));
  // _strategyType->SetBackgroundColour(wxT("RED"));
  exchange_box->Add(data_from, 1, wxALIGN_LEFT | wxLEFT, 20);
  exchange_box->Add(_exchangeTxt, 1, wxALIGN_LEFT);
  commission_box->Add(commission, 1, wxALIGN_LEFT | wxLEFT, 20);
  commission_box->Add(_commissionValue, 1, wxALIGN_LEFT);
  cryptocurrency_box->Add(cryptocurrency, 1, wxALIGN_LEFT | wxLEFT, 20);
  cryptocurrency_box->Add(_cryptocurrencyType, 1, wxALIGN_LEFT);
  investment_box->Add(investment, 1, wxALIGN_LEFT | wxLEFT, 20);
  investment_box->Add(_investmentValue, 1, wxALIGN_LEFT);

  // inside vrighttbox2
  position_box->Add(position, 1, wxALIGN_LEFT | wxLEFT, 20);
  position_box->Add(_openPositionValue, 1, wxALIGN_LEFT);
  last_order_box->Add(last_order, 1, wxALIGN_LEFT | wxLEFT, 20);
  last_order_box->Add(_lastOrderValue, 1, wxALIGN_LEFT);
  benefits_box->Add(benefits, 1, wxALIGN_LEFT | wxLEFT, 20);
  benefits_box->Add(_benefitsValue, 1, wxALIGN_LEFT);
  interest_box->Add(interest, 1, wxALIGN_LEFT | wxLEFT, 20);
  interest_box->Add(_interestValue, 1, wxALIGN_LEFT);
  number_of_orders_box->Add(number_of_orders, 1, wxALIGN_LEFT | wxLEFT, 20);
  number_of_orders_box->Add(_numberOfOrdersValue, 1, wxALIGN_LEFT);
  benefits_acc_box->Add(benefits_acc, 1, wxALIGN_LEFT | wxLEFT, 20);
  benefits_acc_box->Add(_benefitsAccValue, 1, wxALIGN_LEFT);
  interest_acc_box->Add(interest_acc, 1, wxALIGN_LEFT | wxLEFT, 20);
  interest_acc_box->Add(_interestAccValue, 1, wxALIGN_LEFT);





  _cryptoGraphic = std::make_shared<CryptoGraphic>(parent, wxID_ANY);
  //_cryptoGraphic = new CryptoGraphic(parent, wxID_ANY);

  hrighttbox2->Add(_cryptoGraphic.get(), 1, wxEXPAND | wxTOP | wxDOWN | wxLEFT | wxRIGHT, 20);

  // Stablish size from Panels
  parent->SetSizer(hbox);

  // Stablish Background Color to Panel.
  // this->SetBackgroundColour((isFromUser == true ? wxT("YELLOW") : wxT("BLUE")));
}

CryptoGuiPanel::~CryptoGuiPanel()
{}

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
  StartStrategy<SimulateData>(dataSimulated, strategyDataSimulatedBot, stop_simulate_sim_data_btn);
}

void CryptoGuiPanel::OnStopSimulatedData(wxCommandEvent &event)
{
  std::cout << "\nStopping Simulated Data Threads" << std::endl;
  std::vector<std::string> threadsToKill = {dataSimulated, strategyDataSimulatedBot};
  KillThreads(threadsToKill, stop_simulate_sim_data_btn);
}

void CryptoGuiPanel::OnStartHistoricalData(wxCommandEvent &event)
{
  std::cout << "\nOn Start Historical Data: " << std::endl;
  StartStrategy<HistoricData>(historicData, strategyHistoricBot, stop_simulate_hist_data_btn);
}

void CryptoGuiPanel::OnStopHistoricalData(wxCommandEvent &event)
{
  std::cout << "\nStopping Historical Data Threads" << std::endl;
  std::vector<std::string> threadsToKill = {historicData, strategyHistoricBot};
  KillThreads(threadsToKill, stop_simulate_hist_data_btn);
}

void CryptoGuiPanel::OnStartRealData(wxCommandEvent &event)
{
  std::cout << "\nOn Start Real Data: " << std::endl;
  // _commissionValue->SetLabel(wxString::Format(wxT("%d"), 5));

  StartStrategy<Binance>(binanceData, strategyBinanceBot, stop_simulate_real_data_btn); // TEST PARA VER SI AQUÍ ESTARÏA GUAY...
}

void CryptoGuiPanel::OnStopRealData(wxCommandEvent &event)
{
  // std::cout << "\nStopping Real Data Threads" << std::endl;
  std::vector<std::string> threadsToKill = {binanceData, strategyBinanceBot};
  KillThreads(threadsToKill, stop_simulate_real_data_btn);
}

template <class T>
void CryptoGuiPanel::StartStrategy(std::string dataThrName, std::string strategyThrName, wxButton *stopBtn)
{
  // Data thread
  std::shared_ptr<T> dataPtr = std::make_shared<T>();
  std::thread dataThr = std::thread(&T::fetchData, dataPtr);

  // Strategy thread
  std::shared_ptr<Strategy> strategyPtr = std::make_shared<Strategy>(dataPtr);
  strategyPtr->SetCryptoGraphicHandle(_cryptoGraphic);
  strategyPtr->SetCryptoGuiPanelHandle(_cryptoGuiPanel); // no sé si será necesario. Sólo para el caso en que en strategy tenga que meter cosas hacia criptoGuiPanel. Si las puedo leer desde criptoGuiPanel no hace falta
  std::thread strategyThr = std::thread(&Strategy::cryptoBot, strategyPtr);

  // Save reference for threads
  thrMap[dataThrName] = dataThr.native_handle();
  thrMap[strategyThrName] = strategyThr.native_handle();

  // std::this_thread::sleep_for(std::chrono::milliseconds(3000)); // con esto casi siempre me aseguro que al parar hilos no pete. Pero hay que afinar mejor
  //  Manage buttons
  simulate_btn->Enable(false);
  historic_btn->Enable(false);
  realdata_btn->Enable(false);
  stopBtn->Enable(true);

  // Detach threads
  dataThr.detach();
  strategyThr.detach();

  //
  // std::unique_lock<std::mutex> lck(_mtx);
  paintGraphics = true;
  _updateGraphics = true;
  // lck.unlock();
}

void CryptoGuiPanel::KillThreads(std::vector<std::string> threadsToKill, wxButton *stopBtn)
{

  ThreadMap::const_iterator it;

  // for (std::string thrToKill : threadsToKill)
  // {
  //   it = thrMap.find(thrToKill);
  //   if (it != thrMap.end())
  //   {
  //     _simulateDataPtr->unblockThread();
  //     int s = pthread_cancel(it->second);
  //     if (s != 0)
  //     {
  //       std::cout << "Thread " << thrToKill << " can't be killed." << std::endl;
  //     }
  //     else
  //     {
  //       thrMap.erase(thrToKill);
  //       std::cout << "Thread " << thrToKill << " killed. S= " << s << std::endl;
  //     }

  //   }

  for (std::string thrToKill : threadsToKill)
  {
    if (thrToKill != "strategyDataSimulatedBot" && thrToKill != "strategyHistoricBot" && thrToKill != "strategyBinanceBot")
    {
      // std::cout << "THREAD: " << thrToKill << std::endl;
      it = thrMap.find(thrToKill);
      if (it != thrMap.end())
      {
        pthread_cancel(it->second);
        thrMap.erase(thrToKill);
        //_simulateDataPtr->unblockThread();
      }
    }
  }

  // for (std::string thrToKill : threadsToKill)
  // {
  //   if (thrToKill == "strategyDataSimulatedBot" || thrToKill == "strategyHistoricBot" || thrToKill == "strategyBinanceBot")
  //   {
  //     std::cout << "THREADSECOND: " << thrToKill << std::endl;
  //     it = thrMap.find(thrToKill);
  //     if (it != thrMap.end())
  //     {
  //       pthread_cancel(it->second);
  //       std::cout << "aDIOS: " << thrToKill << std::endl;
  //       thrMap.erase(thrToKill);
  //     }
  //   }
  // }

  // Manage buttons
  simulate_btn->Enable(true);
  historic_btn->Enable(true);
  realdata_btn->Enable(true);
  stopBtn->Enable(false);

  //
  // std::unique_lock<std::mutex> lck(_mtx);
  paintGraphics = false;

  y_val.clear();
  secs = 0;
  // lck.unlock();
  // std::cout << std::endl;
}

void CryptoGuiPanel::setStrategyHandle(std::shared_ptr<Strategy> strategy)
{
  _strategyPtr = strategy;
}


void CryptoGuiPanel::setOutputDataStrategy(bool openPosition, double order, double benefit, int nOrders, double benefitsAcc, double investmentAcc)
{
  std::unique_lock<std::mutex> lck(_mtx);
  _openPosition = openPosition;
  _order = order;
  _benefit = benefit;
  _nOrders = nOrders;
  _benefitsAcc = benefitsAcc;
  _investmentAcc = investmentAcc;
  lck.unlock();
}

void CryptoGuiPanel::updateOutputData()
{

  // std::unique_lock<std::mutex> lck(_mtx);
  _openPositionValue->SetLabel(wxString::Format(wxT("%s"), _openPosition ? "true" : "false"));
  _lastOrderValue->SetLabel(wxString::Format(wxT("%f"), _order));
  _benefitsValue->SetLabel(wxString::Format(wxT("%.2f"), _benefit));
  _interestValue->SetLabel(wxString::Format(wxT("%.2f"), _benefit / std::stod(_investment) * 100));
  _numberOfOrdersValue->SetLabel(wxString::Format(wxT("%d"), _nOrders));
  _benefitsAccValue->SetLabel(wxString::Format(wxT("%.2f"), _benefitsAcc));
  _interestAccValue->SetLabel(wxString::Format(wxT("%.2f"), _benefitsAcc / std::stod(_investment) * 100));
  // lck.unlock();
}

std::string CryptoGuiPanel::getExchange()
{
  return _exchange;
}

std::string CryptoGuiPanel::getCryptoConcurrency()
{
  return _cryptoConcurrency;
}

std::string CryptoGuiPanel::getStrategy()
{
  return _strategy;
}

double CryptoGuiPanel::getInvestment()
{
  return std::stod(simple_tokenizer(_investment));
}

BEGIN_EVENT_TABLE(CryptoGraphic, wxPanel)
// EVT_PAINT(CryptoGraphic::paintEvent) // catch paint events
END_EVENT_TABLE()

CryptoGraphic::CryptoGraphic(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxPanelNameStr)
{
  this->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGraphic::OnPaint));
  this->createTicks();
}

CryptoGraphic::~CryptoGraphic()
{
  // delete _chatLogic;
}

void CryptoGraphic::setActualValue(double value)
{
  std::unique_lock<std::mutex> lck(_mtx);
  secs++;

  if (_updateGraphics)
  {
    _value = value;
    _updateGraphics = false;
    Refresh();
  }
  lck.unlock();
}

void CryptoGraphic::setLimits(double base, bool openPosition, double entry, double bottomBreak, double recession, double topBreak)
{
  std::unique_lock<std::mutex> lck(_mtx);
  _base = base;

  if (!openPosition)
  {
    // limits to buy
    _limitUp = (int)((1 + entry) * _base);
    _limitDown = (int)((1 + bottomBreak) * _base);
  }
  else
  {
    // limits to sell
    _limitUp = (int)((1 + topBreak) * _base);
    _limitDown = (int)((1 + recession) * _base);
  }

  if ((_limitUp - _base) > (_base - _limitDown))
  {
    maxValue = (int)(2 * _limitUp - _base);
    minValue = (int)(_base - 2 * (_limitUp - _base));
  }
  else
  {
    maxValue = (int)(_base + 2 * (_base - _limitDown));
    minValue = (int)(2 * _limitDown - _base);
  }
  lck.unlock();
}


void CryptoGraphic::drawAxis(wxDC &dc, wxSize size)
{
  // std::unique_lock<std::mutex> lck(_mtx);
  wxCoord xOrig = xBorderLeft;
  wxCoord yOrig = size.y - yBorderUp;
  wxCoord xYmax = xBorderLeft;
  wxCoord yYmax = yBorderDown;
  wxCoord xXmax = size.x - xBorderRight;
  wxCoord yXmax = size.y - yBorderUp;
  dc.DrawLine(xOrig, yOrig, xYmax, yYmax);
  dc.DrawLine(xOrig, yOrig, xXmax, yXmax);
  // lck.unlock();
}

void CryptoGraphic::drawTics(wxDC &dc, wxSize size)
{
  // std::unique_lock<std::mutex> lck(_mtx);
  // Revisar variables estáticas

  wxCoord xOrig = xBorderLeft;

  wxCoord y_tick_0 = (size.y - yBorderDown - yBorderUp) * 4 / 4 + yBorderDown;
  wxCoord y_tick_1 = valueToPixel(_limitDown, size.y);
  wxCoord y_tick_2 = (size.y - yBorderDown - yBorderUp) * 2 / 4 + yBorderDown;
  wxCoord y_tick_3 = valueToPixel(_limitUp, size.y);
  wxCoord y_tick_4 = yBorderDown;

  dc.DrawLine(45, y_tick_0, xOrig, y_tick_0);
  dc.DrawLine(45, y_tick_1, xOrig, y_tick_1);
  dc.DrawLine(45, y_tick_2, xOrig, y_tick_2);
  dc.DrawLine(45, y_tick_3, xOrig, y_tick_3);
  dc.DrawLine(45, y_tick_4, xOrig, y_tick_4);

  _yTickLabel0->SetPosition(wxPoint(0, y_tick_0 - 9));
  _yTickLabel1->SetPosition(wxPoint(0, y_tick_1 - 9));
  _yTickLabel2->SetPosition(wxPoint(0, y_tick_2 - 9));
  _yTickLabel3->SetPosition(wxPoint(0, y_tick_3 - 9));
  _yTickLabel4->SetPosition(wxPoint(0, y_tick_4 - 9));

  wxCoord x_tick_0 = xBorderLeft;
  wxCoord x_tick_1 = xBorderLeft + (size.x - xBorderLeft - xBorderRight) * 1 / 4;
  wxCoord x_tick_2 = xBorderLeft + (size.x - xBorderLeft - xBorderRight) * 2 / 4;
  wxCoord x_tick_3 = xBorderLeft + (size.x - xBorderLeft - xBorderRight) * 3 / 4;
  wxCoord x_tick_4 = xBorderLeft + (size.x - xBorderLeft - xBorderRight) * 4 / 4;

  dc.DrawLine(x_tick_0, size.y - 30, x_tick_0, size.y - 25);
  dc.DrawLine(x_tick_1, size.y - 30, x_tick_1, size.y - 25);
  dc.DrawLine(x_tick_2, size.y - 30, x_tick_2, size.y - 25);
  dc.DrawLine(x_tick_3, size.y - 30, x_tick_3, size.y - 25);
  dc.DrawLine(x_tick_4, size.y - 30, x_tick_4, size.y - 25);

  _xTickLabel0->SetPosition(wxPoint(x_tick_0 - 5, size.y - 20));
  _xTickLabel1->SetPosition(wxPoint(x_tick_1 - 5, size.y - 20));
  _xTickLabel2->SetPosition(wxPoint(x_tick_2 - 5, size.y - 20));
  _xTickLabel3->SetPosition(wxPoint(x_tick_3 - 5, size.y - 20));
  _xTickLabel4->SetPosition(wxPoint(x_tick_4 - 5, size.y - 20));
  // lck.unlock();
}

void CryptoGraphic::drawQuartiles(wxDC &dc, wxSize size)
{
  // std::unique_lock<std::mutex> lck(_mtx);
  wxCoord y_tick_1 = valueToPixel(_limitDown, size.y);
  wxCoord y_tick_3 = valueToPixel(_limitUp, size.y);

  wxCoord xUp1 = xBorderLeft;
  wxCoord yUp1 = y_tick_1;
  wxCoord xUp2 = size.x - xBorderRight;
  wxCoord yUp2 = y_tick_1;
  wxCoord xDown1 = xBorderLeft;
  wxCoord yDown = y_tick_3;
  wxCoord xDown2 = size.x - xBorderRight;
  wxCoord yDown2 = y_tick_3;
  dc.DrawLine(xUp1, yUp1, xUp2, yUp2);
  dc.DrawLine(xDown1, yDown, xDown2, yDown2);
  // lck.unlock();
}

void CryptoGraphic::drawGraphic(wxDC &dc, wxSize size)
{
  // std::unique_lock<std::mutex> lck(_mtx);
  std::deque<wxCoord> x_val{};
  for (size_t z = 0; z <= xTime; ++z)
  {
    x_val.emplace_back((z * (size.x - xBorderLeft - xBorderRight) / xTime) + xBorderLeft);
  }

  for (size_t i = 0; i < y_val.size(); ++i)
  {
    if (i >= 1)
    {
      dc.DrawLine(x_val[i - 1], valueToPixel(y_val[i - 1], size.y), x_val[i], valueToPixel(y_val[i], size.y));
    }
  }
  // lck.unlock();
}

void CryptoGraphic::updateVectorValues()
{
  y_val.emplace_back(_value);
  if (y_val.size() > xTime + 1)
  {
    y_val.pop_front();
  }

}

void CryptoGraphic::createTicks()
{
  _yTickLabel0 = new wxStaticText(this, -1, wxT(""));
  _yTickLabel1 = new wxStaticText(this, -1, wxT(""));
  _yTickLabel2 = new wxStaticText(this, -1, wxT(""));
  _yTickLabel3 = new wxStaticText(this, -1, wxT(""));
  _yTickLabel4 = new wxStaticText(this, -1, wxT(""));

  _xTickLabel0 = new wxStaticText(this, -1, wxT(""));
  _xTickLabel1 = new wxStaticText(this, -1, wxT(""));
  _xTickLabel2 = new wxStaticText(this, -1, wxT(""));
  _xTickLabel3 = new wxStaticText(this, -1, wxT(""));
  _xTickLabel4 = new wxStaticText(this, -1, wxT(""));
}

void CryptoGraphic::updateTicks()
{
  _yTickLabel0->SetLabel(wxString::Format(wxT("%d"), minValue));
  _yTickLabel1->SetLabel(wxString::Format(wxT("%d"), _limitDown));
  _yTickLabel2->SetLabel(wxString::Format(wxT("%d"), (int)_base));
  _yTickLabel3->SetLabel(wxString::Format(wxT("%d"), _limitUp));
  _yTickLabel4->SetLabel(wxString::Format(wxT("%d"), maxValue));

  if (secs - 2 < 1)
  {
    _xTickLabel0->SetLabel(wxString::Format(wxT("%s"), " "));
  }
  if (secs > 1 && secs <= xTime + 2)
  {
    _xTickLabel0->SetLabel(wxString::Format(wxT("%d"), secs - 2));
  }

  if (secs - 2 - xTime * 1 / 4 <= 0)
  {
    _xTickLabel1->SetLabel(wxString::Format(wxT("%s"), " "));
  }
  if (secs - 2 - xTime * 1 / 4 >= 0 && secs <= xTime + 2)
  {
    _xTickLabel1->SetLabel(wxString::Format(wxT("%d"), (int)(secs - 2 - xTime * 1 / 4)));
  }

  if (secs - 2 - xTime * 2 / 4 <= 0)
  {
    _xTickLabel2->SetLabel(wxString::Format(wxT("%s"), " "));
  }
  if (secs - 2 - xTime * 2 / 4 >= 0 && secs <= xTime + 2)
  {
    _xTickLabel2->SetLabel(wxString::Format(wxT("%d"), (int)(secs - 2 - xTime * 2 / 4)));
  }

  if (secs - 2 - xTime * 3 / 4 <= 0)
  {
    _xTickLabel3->SetLabel(wxString::Format(wxT("%s"), " "));
  }
  if (secs - 2 - xTime * 3 / 4 >= 0 && secs <= xTime + 2)
  {
    _xTickLabel3->SetLabel(wxString::Format(wxT("%d"), (int)(secs - 2 - xTime * 3 / 4)));
  }

  if (secs - 2 - xTime <= 0)
  {
    _xTickLabel4->SetLabel(wxString::Format(wxT("%s"), " "));
  }
  if (secs - 2 - xTime >= 0 && secs <= xTime + 2)
  {
    _xTickLabel4->SetLabel(wxString::Format(wxT("%d"), (int)(secs - 2 - xTime)));
  }
  // std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  // lck.unlock();
}

int CryptoGraphic::valueToPixel(int value, int sizey)
{

  // Revisar que maxValue y minValue no sean cero!!
  return (sizey - yBorderUp - yBorderDown) * (maxValue - value) / (maxValue - minValue) + yBorderDown;
}





void CryptoGraphic::render(wxDC &dc)
{

  //  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  // std::unique_lock<std::mutex> lck(_mtx);
  wxSize size = this->GetSize();

  // Logics of update graphic
  if (oldSecs != secs)
  {
    updateTicks();
    updateVectorValues();
    _cryptoGuiPanel->updateOutputData();
    // lck.lock();
    oldSecs = secs;
    // lck.unlock();
    // Aquí debería lanzar la signal para que siguiera la estrategia mandándome datos
    // // // updateGraphics = true;
    // // // std::cout << "UPDATE GRAPHICS IN GUI: " << updateGraphics << std::endl;
    // // // _cdtGraphic.notify_one();
    _updateGraphics = true;
  }
  // else
  // {
  //   updateGraphics = false;
  // }

  // Draw axis
  //  lck.lock();
  wxPen pen1(wxT("BLACK"), 2, wxPENSTYLE_SOLID);
  dc.SetPen(pen1);
  // lck.unlock();
  drawAxis(dc, size);

  // Draw ticks
  drawTics(dc, size);

  // Draw Quartiles
  // lck.lock();
  wxPen pen2(wxT("RED"), 2, wxPENSTYLE_DOT_DASH);
  dc.SetPen(pen2);
  // lck.unlock();
  drawQuartiles(dc, size);

  // Draw line of value
  // lck.lock();
  wxPen pen3(wxT("GREEN"), 3, wxPENSTYLE_DOT_DASH);
  dc.SetPen(pen3);
  // lck.unlock();
  drawGraphic(dc, size);

  // lck.unlock();
}

void CryptoGraphic::OnPaint(wxPaintEvent &event)
{
  std::unique_lock<std::mutex> lck(_mtx);

  wxPaintDC dc(this);
  if (paintGraphics)
  {
    render(dc);
  }
  lck.unlock();
}