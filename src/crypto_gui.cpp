#include "crypto_gui.h"

// shared variables in CryptoGuiPanel and CryptoGraphic
typedef std::unordered_map<std::string, pthread_t> ThreadMap;
ThreadMap thrMap;

std::promise<int> prom;

wxButton *createData;
wxButton *stopData;
wxButton *simulateBtn;
wxButton *stopSimulateSimDataBtn;
wxButton *historicBtn;
wxButton *stopSimulateHistDataBtn;
wxButton *realdataBtn;
wxButton *stopSimulateRealDataBtn;

std::string writeHistoricData = "writeHistoricData";
std::string dataSimulated = "dataSimulated";
std::string strategyDataSimulatedBot = "strategyDataSimulatedBot";
std::string historicData = "historicData";
std::string strategyHistoricBot = "strategyHistoricBot";
std::string binanceData = "binanceData";
std::string strategyBinanceBot = "strategyBinanceBot";

// event table
wxBEGIN_EVENT_TABLE(CryptoGui, wxFrame)

EVT_MENU(ID_CONFIGURE_STRATEGY, CryptoGui::OnConfigureStrategy)
EVT_MENU(wxID_EXIT, CryptoGui::OnExit)
EVT_MENU(wxID_ABOUT, CryptoGui::OnAbout)

EVT_BUTTON(ID_CREATE_HISTORICAL_DATA, CryptoGuiPanel::OnCreateHistoricalData)
EVT_BUTTON(ID_STOP_HISTORICAL_DATA, CryptoGuiPanel::OnStopCreationData)
EVT_BUTTON(ID_SIMULATE_DATA, CryptoGuiPanel::OnStartSimulatedData)
EVT_BUTTON(ID_SIMULATE_DATA_STOP, CryptoGuiPanel::OnStopSimulatedData)
EVT_BUTTON(ID_HISTORICAL_DATA, CryptoGuiPanel::OnStartHistoricalData)
EVT_BUTTON(ID_HISTORICAL_DATA_STOP, CryptoGuiPanel::OnStopHistoricalData)
EVT_BUTTON(ID_REAL_DATA, CryptoGuiPanel::OnStartRealData)
EVT_BUTTON(ID_REAL_DATA_STOP, CryptoGuiPanel::OnStopRealData)

wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(CryptoBot);

// entry point of CryptoBot
bool CryptoBot::OnInit()
{
  // new CryptoGui
  CryptoGui *frame = new CryptoGui("Cryptoconcurrency Live Trading Bot", wxPoint(50, 50), wxSize(965, 538)); // Taking into account header and footer, 88 pixels height extra are needed.
  frame->Show(true);

  return true;
}

// constructor of CryptoGui
CryptoGui::CryptoGui(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
  // menuFile
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID_CONFIGURE_STRATEGY, "&Configure Strategy...\tCtrl-H", "You can configure input data of strategy from here");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  // menuHelp
  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  // menuBar
  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");
  SetMenuBar(menuBar);

  // statusBar
  CreateStatusBar();
  SetStatusText("Created by Pablo Ruiz");

  // new CryptoGuiPanel
  wxPanel *panel = new wxPanel(this, -1);
  _cryptoGuiPanel = std::make_shared<CryptoGuiPanel>(panel);
}

// menu On Configure Strategy
void CryptoGui::OnConfigureStrategy(wxCommandEvent &event)
{
  wxLogMessage("To do: wxPanel to configure input data of strategy");
}

// menu On About
void CryptoGui::OnAbout(wxCommandEvent &event)
{
  wxMessageBox("This is CryptoBot. Created by Pablo Ruiz",
               "About CryptoBot", wxOK | wxICON_INFORMATION);
}

// menu On Exit
void CryptoGui::OnExit(wxCommandEvent &event)
{
  Close(true);
}

// CryptoGuiPanel constructor. Definition and position of all the elements un tue Gui
CryptoGuiPanel::CryptoGuiPanel(wxPanel *parent)
{
  // create Box Sizers
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *vbox1 = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *vbox2 = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hleftbox1 = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hleftbox2 = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hrighttbox1 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *hrighttbox2 = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *vrighttbox1 = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *vrighttbox2 = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer *createLabelBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *createActionBox = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer *simulateLabelBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulateSelectExchangeBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulateSelectCryptoBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulateSelectInvestmentBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulateSelectStrategyBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulateSimDataButtonsBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulateHistDataButtonsBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *simulateRealDataButtonsBox = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer *strategyBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *exchangeBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *commissionBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *cryptocurrencyBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *investmentBox = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer *positionBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *lastOrderBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *benefitsBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *interestBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *numberOfOrdersBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *benefitsAccBox = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer *interestAccBox = new wxBoxSizer(wxHORIZONTAL);

  // define elements
  // inside create_box
  wxStaticText *createTitleLabel = new wxStaticText(parent, -1, wxT("Create historic data "));
  wxStaticText *textCreate = new wxStaticText(parent, -1, wxT("Push to create data: "));
  createData = new wxButton(parent, ID_CREATE_HISTORICAL_DATA, wxT("Create Data"));
  stopData = new wxButton(parent, ID_STOP_HISTORICAL_DATA, wxT("Stop and Save"));
  stopData->Enable(false);

  wxStaticLine *lineHor1 = new wxStaticLine(parent, -1);

  // inside simulate boxes
  wxStaticText *simulateLabel = new wxStaticText(parent, -1, wxT("Simulate your strategy "));
  wxStaticText *simulateSelectExchangeLabel = new wxStaticText(parent, -1, wxT("Select Exchange: "));
  wxStaticText *simulateSelectCryptoLabel = new wxStaticText(parent, -1, wxT("Select Cryptoconcurrency: "));
  wxStaticText *simulateSelectInvestmentLabel = new wxStaticText(parent, -1, wxT("Select Investment: "));
  wxStaticText *simulateSelectStrategyLabel = new wxStaticText(parent, -1, wxT("Select your strategy: "));

  const wxString simulationExchangeChoices = wxT("Binance");
  wxChoice *simulateChoiceExchange = new wxChoice(parent, -1, wxDefaultPosition, wxDefaultSize, 1, &simulationExchangeChoices, wxCB_SORT | wxCB_DROPDOWN, wxDefaultValidator);
  simulateChoiceExchange->SetSelection(0);
  _exchange = simulateChoiceExchange->GetString(simulateChoiceExchange->GetSelection());

  const wxString simulationCryptoChoices = wxT("Bitcoint");
  wxChoice *simulateChoiceCrypto = new wxChoice(parent, -1, wxDefaultPosition, wxDefaultSize, 1, &simulationCryptoChoices, wxCB_SORT | wxCB_DROPDOWN, wxDefaultValidator);
  simulateChoiceCrypto->SetSelection(0);
  _cryptoConcurrency = simulateChoiceCrypto->GetString(simulateChoiceCrypto->GetSelection());

  const wxString simulationStrategyChoices = wxT("Standard");
  wxChoice *simulateChoiceStrategy = new wxChoice(parent, -1, wxDefaultPosition, wxDefaultSize, 1, &simulationStrategyChoices, wxCB_SORT | wxCB_DROPDOWN, wxDefaultValidator);
  simulateChoiceStrategy->SetSelection(0);
  _strategy = simulateChoiceStrategy->GetString(simulateChoiceStrategy->GetSelection());

  const wxString simulationInvestmentChoices = wxT("50 $");
  wxChoice *simulateChoiceInvestment = new wxChoice(parent, -1, wxDefaultPosition, wxDefaultSize, 1, &simulationInvestmentChoices, wxCB_SORT | wxCB_DROPDOWN, wxDefaultValidator);
  simulateChoiceInvestment->SetSelection(0);
  _investment = simulateChoiceInvestment->GetString(simulateChoiceInvestment->GetSelection());

  wxStaticText *dataSimulatedLabel = new wxStaticText(parent, -1, wxT("Data Simulated: "));

  simulateBtn = new wxButton(parent, ID_SIMULATE_DATA, wxT("Start"));
  stopSimulateSimDataBtn = new wxButton(parent, ID_SIMULATE_DATA_STOP, wxT("Stop"));
  stopSimulateSimDataBtn->Enable(false);
  wxStaticText *historic_data_label = new wxStaticText(parent, -1, wxT("Historic Data: "));
  historicBtn = new wxButton(parent, ID_HISTORICAL_DATA, wxT("Start"));
  stopSimulateHistDataBtn = new wxButton(parent, ID_HISTORICAL_DATA_STOP, wxT("Stop"));
  stopSimulateHistDataBtn->Enable(false);
  wxStaticText *realtime_data_label = new wxStaticText(parent, -1, wxT("Real Time Data: "));
  realdataBtn = new wxButton(parent, ID_REAL_DATA, wxT("Start"));
  stopSimulateRealDataBtn = new wxButton(parent, ID_REAL_DATA_STOP, wxT("Stop"));
  stopSimulateRealDataBtn->Enable(false);

  // separator vertical line
  wxStaticLine *lineVer1 = new wxStaticLine(parent, -1);

  // inside vrighttbox1
  wxStaticText *dataFrom = new wxStaticText(parent, -1, wxT("Data from: "));
  wxStaticText *commission = new wxStaticText(parent, -1, wxT("Commission: "));
  wxStaticText *cryptocurrency = new wxStaticText(parent, -1, wxT("Crypto: "));
  wxStaticText *investment = new wxStaticText(parent, -1, wxT("Investment: "));
  wxStaticText *strategy = new wxStaticText(parent, -1, wxT("Strategy: "));

  // set text variables
  _exchangeTxt = new wxStaticText(parent, -1, _exchange);
  _commissionValue = new wxStaticText(parent, -1, wxT("0.075 %"));
  _cryptocurrencyType = new wxStaticText(parent, -1, _cryptoConcurrency);
  _investmentValue = new wxStaticText(parent, -1, _investment);
  _strategyType = new wxStaticText(parent, -1, _strategy);

  // separator vertical line
  wxStaticLine *lineVer2 = new wxStaticLine(parent, -1);

  // inside vrighttbox2
  wxStaticText *position = new wxStaticText(parent, -1, wxT("Open position: "));
  wxStaticText *lastOrder = new wxStaticText(parent, -1, wxT("Last order (btc): "));
  wxStaticText *benefits = new wxStaticText(parent, -1, wxT("Benefits ($): "));
  wxStaticText *interest = new wxStaticText(parent, -1, wxT("Interest (%): "));
  wxStaticText *numberOfOrders = new wxStaticText(parent, -1, wxT("Number of orders: "));
  wxStaticText *benefitsAcc = new wxStaticText(parent, -1, wxT("Benefits accumulated ($): "));
  wxStaticText *interestAcc = new wxStaticText(parent, -1, wxT("Interest accumulated (%): "));

  // set text variables (TO DO) //
  _openPositionValue = new wxStaticText(parent, -1, wxT("False"));
  _lastOrderValue = new wxStaticText(parent, -1, wxT("0"));
  _benefitsValue = new wxStaticText(parent, -1, wxT("0"));
  _interestValue = new wxStaticText(parent, -1, wxT("0"));
  _numberOfOrdersValue = new wxStaticText(parent, -1, wxT("0"));
  _benefitsAccValue = new wxStaticText(parent, -1, wxT("0"));
  _interestAccValue = new wxStaticText(parent, -1, wxT("0"));

  // separator horizontal line
  wxStaticLine *lineHor4 = new wxStaticLine(parent, -1);

  // assign elements
  hbox->Add(vbox1, 1, wxEXPAND);
  hbox->Add(lineVer1, 0, wxEXPAND | wxTOP | wxDOWN | wxLEFT | wxRIGHT, 10);
  hbox->Add(vbox2, 3, wxEXPAND);

  // inside hbox
  vbox1->Add(hleftbox1, 1, wxEXPAND);
  vbox1->Add(lineHor1, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);
  vbox1->Add(hleftbox2, 3, wxEXPAND);

  vbox2->Add(hrighttbox1, 1, wxEXPAND);
  vbox2->Add(lineHor4, 0, wxEXPAND | wxLEFT | wxRIGHT, 20);
  vbox2->Add(hrighttbox2, 2, wxEXPAND);

  // inside vbox1
  hleftbox1->Add(createLabelBox, 1, wxALIGN_CENTER | wxTOP, 20);
  hleftbox1->Add(createActionBox, 1, wxEXPAND | wxTOP, 0);

  // inside hleftbox2
  hleftbox2->Add(simulateLabelBox, 1, wxALIGN_CENTER | wxTOP, 0);
  hleftbox2->Add(simulateSelectExchangeBox, 1, wxEXPAND);
  hleftbox2->Add(simulateSelectCryptoBox, 1, wxEXPAND);
  hleftbox2->Add(simulateSelectInvestmentBox, 1, wxEXPAND);
  hleftbox2->Add(simulateSelectStrategyBox, 1, wxEXPAND);
  hleftbox2->Add(simulateSimDataButtonsBox, 1, wxEXPAND);
  hleftbox2->Add(simulateHistDataButtonsBox, 1, wxEXPAND);
  hleftbox2->Add(simulateRealDataButtonsBox, 1, wxEXPAND | wxBOTTOM, 10);

  // inside vbox2
  hrighttbox1->Add(vrighttbox1, 2, wxEXPAND | wxTOP, 20);
  hrighttbox1->Add(lineVer2, 0, wxEXPAND | wxTOP | wxDOWN | wxLEFT | wxRIGHT, 10);
  hrighttbox1->Add(vrighttbox2, 3, wxEXPAND | wxTOP, 20);

  // inside create_box
  createLabelBox->Add(createTitleLabel, 1, wxALIGN_CENTER_HORIZONTAL | wxLEFT, 10);
  createActionBox->Add(textCreate, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  createActionBox->Add(createData, 1, wxALIGN_CENTER, 10);
  createActionBox->Add(stopData, 1, wxALIGN_CENTER, 10);

  // inside simulateLabelBox
  simulateLabelBox->Add(simulateLabel, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulateSelectExchangeBox->Add(simulateSelectExchangeLabel, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulateSelectExchangeBox->Add(simulateChoiceExchange, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulateSelectCryptoBox->Add(simulateSelectCryptoLabel, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulateSelectCryptoBox->Add(simulateChoiceCrypto, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulateSelectInvestmentBox->Add(simulateSelectInvestmentLabel, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulateSelectInvestmentBox->Add(simulateChoiceInvestment, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulateSelectStrategyBox->Add(simulateSelectStrategyLabel, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
  simulateSelectStrategyBox->Add(simulateChoiceStrategy, 1, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);

  simulateSimDataButtonsBox->Add(dataSimulatedLabel, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  simulateSimDataButtonsBox->Add(simulateBtn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  simulateSimDataButtonsBox->Add(stopSimulateSimDataBtn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);

  simulateHistDataButtonsBox->Add(historic_data_label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  simulateHistDataButtonsBox->Add(historicBtn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  simulateHistDataButtonsBox->Add(stopSimulateHistDataBtn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);

  simulateRealDataButtonsBox->Add(realtime_data_label, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  simulateRealDataButtonsBox->Add(realdataBtn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
  simulateRealDataButtonsBox->Add(stopSimulateRealDataBtn, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);

  // inside hrighttbox1
  vrighttbox1->Add(exchangeBox, 1, wxEXPAND);
  vrighttbox1->Add(commissionBox, 1, wxEXPAND);
  vrighttbox1->Add(cryptocurrencyBox, 1, wxEXPAND);
  vrighttbox1->Add(investmentBox, 1, wxEXPAND);
  vrighttbox1->Add(strategyBox, 1, wxEXPAND);

  vrighttbox2->Add(positionBox, 1, wxEXPAND);
  vrighttbox2->Add(lastOrderBox, 1, wxEXPAND);
  vrighttbox2->Add(benefitsBox, 1, wxEXPAND);
  vrighttbox2->Add(interestBox, 1, wxEXPAND);
  vrighttbox2->Add(numberOfOrdersBox, 1, wxEXPAND);
  vrighttbox2->Add(benefitsAccBox, 1, wxEXPAND);
  vrighttbox2->Add(interestAccBox, 1, wxEXPAND);

  // inside vrighttbox1
  strategyBox->Add(strategy, 1, wxALIGN_LEFT | wxLEFT, 20);
  strategyBox->Add(_strategyType, 1, wxALIGN_LEFT);
  exchangeBox->Add(dataFrom, 1, wxALIGN_LEFT | wxLEFT, 20);
  exchangeBox->Add(_exchangeTxt, 1, wxALIGN_LEFT);
  commissionBox->Add(commission, 1, wxALIGN_LEFT | wxLEFT, 20);
  commissionBox->Add(_commissionValue, 1, wxALIGN_LEFT);
  cryptocurrencyBox->Add(cryptocurrency, 1, wxALIGN_LEFT | wxLEFT, 20);
  cryptocurrencyBox->Add(_cryptocurrencyType, 1, wxALIGN_LEFT);
  investmentBox->Add(investment, 1, wxALIGN_LEFT | wxLEFT, 20);
  investmentBox->Add(_investmentValue, 1, wxALIGN_LEFT);

  // inside vrighttbox2
  positionBox->Add(position, 1, wxALIGN_LEFT | wxLEFT, 20);
  positionBox->Add(_openPositionValue, 1, wxALIGN_LEFT);
  lastOrderBox->Add(lastOrder, 1, wxALIGN_LEFT | wxLEFT, 20);
  lastOrderBox->Add(_lastOrderValue, 1, wxALIGN_LEFT);
  benefitsBox->Add(benefits, 1, wxALIGN_LEFT | wxLEFT, 20);
  benefitsBox->Add(_benefitsValue, 1, wxALIGN_LEFT);
  interestBox->Add(interest, 1, wxALIGN_LEFT | wxLEFT, 20);
  interestBox->Add(_interestValue, 1, wxALIGN_LEFT);
  numberOfOrdersBox->Add(numberOfOrders, 1, wxALIGN_LEFT | wxLEFT, 20);
  numberOfOrdersBox->Add(_numberOfOrdersValue, 1, wxALIGN_LEFT);
  benefitsAccBox->Add(benefitsAcc, 1, wxALIGN_LEFT | wxLEFT, 20);
  benefitsAccBox->Add(_benefitsAccValue, 1, wxALIGN_LEFT);
  interestAccBox->Add(interestAcc, 1, wxALIGN_LEFT | wxLEFT, 20);
  interestAccBox->Add(_interestAccValue, 1, wxALIGN_LEFT);

  // new area for graphics
  _cryptoGraphic = std::make_shared<CryptoGraphic>(parent, wxID_ANY);
  hrighttbox2->Add(_cryptoGraphic.get(), 1, wxEXPAND | wxTOP | wxDOWN | wxLEFT | wxRIGHT, 20);
  parent->SetSizer(hbox);
}

// create historic data from Binance in real time
void CryptoGuiPanel::OnCreateHistoricalData(wxCommandEvent &event)
{
  std::cout << "\nCreating new data series with real data: " << std::endl;

  // real data in real time
  std::shared_ptr<Binance> binancePtr = std::make_shared<Binance>();
  std::thread binanceData = std::thread(&Binance::fetchData, binancePtr);

  // std::promise<int> prom;                      // create promise
  std::future<int> fut = prom.get_future();    // engagement with future

  // create new data series
  std::shared_ptr<HistoricData> dataFilePtr = std::make_shared<HistoricData>();
  std::thread writeHistoricData = std::thread(&HistoricData::createHistoricData, dataFilePtr, binancePtr);
  std::thread closeFile = std::thread(&HistoricData::closeFile, dataFilePtr, std::ref(fut));
  
  // save reference for threads. Necessary to kill later
  thrMap["binanceData"] = binanceData.native_handle();
  thrMap["writeHistoricData"] = writeHistoricData.native_handle();
  thrMap["closeFile"] = closeFile.native_handle();

  // manage buttons
  stopData->Enable(true);
  createData->Enable(false);

  writeHistoricData.detach();
  binanceData.detach();
  closeFile.detach();
  
}

// on stop historical data
void CryptoGuiPanel::OnStopCreationData(wxCommandEvent &event)
{
  std::cout << "\nStopping Creation of Data" << std::endl;
  stopData->Enable(false);
  prom.set_value(1); 
}

// on start simulated data
void CryptoGuiPanel::OnStartSimulatedData(wxCommandEvent &event)
{
  std::cout << "\nOn Start Simulated Data: " << std::endl;
  StartStrategy<SimulateData>(dataSimulated, strategyDataSimulatedBot, stopSimulateSimDataBtn);
}

// on stop simulated data
void CryptoGuiPanel::OnStopSimulatedData(wxCommandEvent &event)
{
  std::cout << "\nStopping Simulated Data Threads" << std::endl;
  std::vector<std::string> threadsToKill = {dataSimulated, strategyDataSimulatedBot};
  KillThreads(threadsToKill, stopSimulateSimDataBtn);
}

// on start historical data
void CryptoGuiPanel::OnStartHistoricalData(wxCommandEvent &event)
{
  std::cout << "\nOn Start Historical Data: " << std::endl;
  StartStrategy<HistoricData>(historicData, strategyHistoricBot, stopSimulateHistDataBtn);
}

// on stop historical data
void CryptoGuiPanel::OnStopHistoricalData(wxCommandEvent &event)
{
  std::cout << "\nStopping Historical Data Threads" << std::endl;
  std::vector<std::string> threadsToKill = {historicData, strategyHistoricBot};
  KillThreads(threadsToKill, stopSimulateHistDataBtn);
}

// on start real data
void CryptoGuiPanel::OnStartRealData(wxCommandEvent &event)
{
  std::cout << "\nOn Start Real Data: " << std::endl;
  StartStrategy<Binance>(binanceData, strategyBinanceBot, stopSimulateRealDataBtn);
}

// on stop real data
void CryptoGuiPanel::OnStopRealData(wxCommandEvent &event)
{
  std::cout << "\nStopping Real Data Threads" << std::endl;
  std::vector<std::string> threadsToKill = {binanceData, strategyBinanceBot};
  KillThreads(threadsToKill, stopSimulateRealDataBtn);
}

// generic function to start cryptoBot working with any type of data
template <class T>
void CryptoGuiPanel::StartStrategy(std::string dataThrName, std::string strategyThrName, wxButton *stopBtn)
{
  // data thread
  std::shared_ptr<T> dataPtr = std::make_shared<T>();
  std::thread dataThr = std::thread(&T::fetchData, dataPtr);

  // strategy thread
  std::shared_ptr<Strategy> strategyPtr = std::make_shared<Strategy>(dataPtr);
  strategyPtr->SetCryptoGraphicHandle(_cryptoGraphic);
  strategyPtr->SetCryptoGuiPanelHandle(_cryptoGuiPanel); 
  std::thread strategyThr = std::thread(&Strategy::cryptoBot, strategyPtr);

  // save reference for threads. Necessary to kill later
  thrMap[dataThrName] = dataThr.native_handle();
  thrMap[strategyThrName] = strategyThr.native_handle();

  // manage buttons
  simulateBtn->Enable(false);
  historicBtn->Enable(false);
  realdataBtn->Enable(false);
  stopBtn->Enable(true);

  // booleans to manage graphics
  _paintGraphics = true;
  _updateGraphics = true;

  // detach threads
  dataThr.detach();
  strategyThr.detach();
}

// generic function to stop threads
void CryptoGuiPanel::KillThreads(std::vector<std::string> threadsToKill, wxButton *stopBtn)
{
  ThreadMap::const_iterator it;

  
  for (std::string thrToKill : threadsToKill)
  {
    std::cout << "test " << thrToKill <<std::endl;
    // FOR THE FUTURE: Kill also strategy threads
    if (thrToKill != "strategyDataSimulatedBot" && thrToKill != "strategyHistoricBot" && thrToKill != "strategyBinanceBot")
    {
      it = thrMap.find(thrToKill);
      if (it != thrMap.end())
      {
        std::cout << thrToKill << std::endl;
        pthread_cancel(it->second);
        thrMap.erase(thrToKill);
      }
    }
  }

  // Manage buttons
  simulateBtn->Enable(true);
  historicBtn->Enable(true);
  realdataBtn->Enable(true);
  stopBtn->Enable(false);

  // booleans to manage graphics
  _paintGraphics = false;
  _updateGraphics = false;

  // clear graphic
  y_val.clear();
  secs = 0;
}

// handler function to set shared pointer from strategy
void CryptoGuiPanel::setStrategyHandle(std::shared_ptr<Strategy> strategy)
{
  _strategyPtr = strategy;
}

// propietary function - set output data from strategy in crypto gui panel
void CryptoGuiPanel::setOutputDataStrategy(bool openPosition, double order, double benefit, int nOrders, double benefitsAcc, double investmentAcc)
{
  // lock shared variables
  std::unique_lock<std::mutex> lck(_mtx);
  _openPosition = openPosition;
  _order = order;
  _benefit = benefit;
  _nOrders = nOrders;
  _benefitsAcc = benefitsAcc;
  _investmentAcc = investmentAcc;
  lck.unlock();
}

// propietary function - set labels for outputs data
void CryptoGuiPanel::updateOutputData()
{
  _openPositionValue->SetLabel(wxString::Format(wxT("%s"), _openPosition ? "true" : "false"));
  _lastOrderValue->SetLabel(wxString::Format(wxT("%f"), _order));
  _benefitsValue->SetLabel(wxString::Format(wxT("%.2f"), _benefit));
  _interestValue->SetLabel(wxString::Format(wxT("%.2f"), _benefit / std::stod(_investment) * 100));
  _numberOfOrdersValue->SetLabel(wxString::Format(wxT("%d"), _nOrders));
  _benefitsAccValue->SetLabel(wxString::Format(wxT("%.2f"), _benefitsAcc));
  _interestAccValue->SetLabel(wxString::Format(wxT("%.2f"), _benefitsAcc / std::stod(_investment) * 100));
}

// geters
std::string CryptoGuiPanel::getExchange() { return _exchange; }
std::string CryptoGuiPanel::getCryptoConcurrency() { return _cryptoConcurrency; }
std::string CryptoGuiPanel::getStrategy() { return _strategy; }
double CryptoGuiPanel::getInvestment() { return std::stod(getFirstValue(_investment)); }

// helper function
std::string CryptoGuiPanel::getFirstValue(std::string s)
{
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
}

// constructor of CryptoGraphic
CryptoGraphic::CryptoGraphic(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxPanelNameStr)
{
  this->Connect(wxEVT_PAINT, wxPaintEventHandler(CryptoGraphic::OnPaint));
  this->createTicks();
}

// update of value from the cryptoconcurrency
void CryptoGraphic::setActualValue(double value)
{
  std::unique_lock<std::mutex> lck(_mtx);
  if (_updateGraphics) // this will prevent it from being refreshed again before the previous refresh is finished.
  {
    _value = value;
    _updateGraphics = false;
    Refresh();
  }
  secs++;
  lck.unlock();
}

// set limits in graphics
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

// event on paint. It triggers when refresh()
void CryptoGraphic::OnPaint(wxPaintEvent &event)
{
  std::unique_lock<std::mutex> lck(_mtx);

  wxPaintDC dc(this);
  if (_paintGraphics)
  {
    render(dc);
  }
  lck.unlock();
}

// function for drawing axis
void CryptoGraphic::drawAxis(wxDC &dc, wxSize size)
{
  wxCoord xOrig = xBorderLeft;
  wxCoord yOrig = size.y - yBorderUp;
  wxCoord xYmax = xBorderLeft;
  wxCoord yYmax = yBorderDown;
  wxCoord xXmax = size.x - xBorderRight;
  wxCoord yXmax = size.y - yBorderUp;
  dc.DrawLine(xOrig, yOrig, xYmax, yYmax);
  dc.DrawLine(xOrig, yOrig, xXmax, yXmax);
}

// function for drawing ticks
void CryptoGraphic::drawTics(wxDC &dc, wxSize size)
{
  wxCoord xOrig = xBorderLeft;

  wxCoord yTick0 = (size.y - yBorderDown - yBorderUp) * 4 / 4 + yBorderDown;
  wxCoord yTick1 = valueToPixel(_limitDown, size.y);
  wxCoord yTick2 = (size.y - yBorderDown - yBorderUp) * 2 / 4 + yBorderDown;
  wxCoord yTick3 = valueToPixel(_limitUp, size.y);
  wxCoord yTick4 = yBorderDown;

  dc.DrawLine(45, yTick0, xOrig, yTick0);
  dc.DrawLine(45, yTick1, xOrig, yTick1);
  dc.DrawLine(45, yTick2, xOrig, yTick2);
  dc.DrawLine(45, yTick3, xOrig, yTick3);
  dc.DrawLine(45, yTick4, xOrig, yTick4);

  _yTickLabel0->SetPosition(wxPoint(0, yTick0 - 9));
  _yTickLabel1->SetPosition(wxPoint(0, yTick1 - 9));
  _yTickLabel2->SetPosition(wxPoint(0, yTick2 - 9));
  _yTickLabel3->SetPosition(wxPoint(0, yTick3 - 9));
  _yTickLabel4->SetPosition(wxPoint(0, yTick4 - 9));

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
}

// function for drawing limits
void CryptoGraphic::drawLimits(wxDC &dc, wxSize size)
{
  wxCoord yTick1 = valueToPixel(_limitDown, size.y);
  wxCoord yTick3 = valueToPixel(_limitUp, size.y);

  wxCoord xUp1 = xBorderLeft;
  wxCoord yUp1 = yTick1;
  wxCoord xUp2 = size.x - xBorderRight;
  wxCoord yUp2 = yTick1;
  wxCoord xDown1 = xBorderLeft;
  wxCoord yDown = yTick3;
  wxCoord xDown2 = size.x - xBorderRight;
  wxCoord yDown2 = yTick3;
  dc.DrawLine(xUp1, yUp1, xUp2, yUp2);
  dc.DrawLine(xDown1, yDown, xDown2, yDown2);
}

// function for drawing graphic
void CryptoGraphic::drawGraphic(wxDC &dc, wxSize size)
{
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
}

// function for update vector of graphic values
void CryptoGraphic::updateVectorValues()
{
  y_val.emplace_back(_value);
  if (y_val.size() > xTime + 1)
  {
    y_val.pop_front();
  }
}

// function for create ticks
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

// function for update ticks
void CryptoGraphic::updateTicks()
{
  _yTickLabel0->SetLabel(wxString::Format(wxT("%d"), minValue));
  _yTickLabel1->SetLabel(wxString::Format(wxT("%d"), _limitDown));
  _yTickLabel2->SetLabel(wxString::Format(wxT("%d"), (int)_base));
  _yTickLabel3->SetLabel(wxString::Format(wxT("%d"), _limitUp));
  _yTickLabel4->SetLabel(wxString::Format(wxT("%d"), maxValue));

  // the right value represent the last value. So, while the graphic doesn't achieve the rigth part, seconds will be increasing.
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
}

// render graphic
void CryptoGraphic::render(wxDC &dc)
{
  wxSize size = this->GetSize();

  // Logics of update graphic. (Graphic can be updated in size without problems).
  if (oldSecs != secs)
  {
    updateTicks();
    updateVectorValues();
    _cryptoGuiPanel->updateOutputData();
    _updateGraphics = true;
    oldSecs = secs;
  }

  // Draw axis
  wxPen pen1(wxT("BLACK"), 2, wxPENSTYLE_SOLID);
  dc.SetPen(pen1);
  drawAxis(dc, size);

  // Draw ticks
  drawTics(dc, size);

  // Draw Limits
  wxPen pen2(wxT("RED"), 2, wxPENSTYLE_DOT_DASH);
  dc.SetPen(pen2);
  drawLimits(dc, size);

  // Draw line of value
  wxPen pen3(wxT("GREEN"), 3, wxPENSTYLE_DOT_DASH);
  dc.SetPen(pen3);
  drawGraphic(dc, size);
}

// helper function --> transform real value to pixel value in y axis
int CryptoGraphic::valueToPixel(int value, int sizey)
{
  if ((maxValue - minValue) != 0)
  {
    return (sizey - yBorderUp - yBorderDown) * (maxValue - value) / (maxValue - minValue) + yBorderDown;
  }
  else
  {
    return (sizey - yBorderUp - yBorderDown);
  }
}