#ifndef CRYPTO_GUI_H_
#define CRYPTO_GUI_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/statline.h>
#endif

#include <string>
#include <unordered_map>
#include <future>
#include "simulate_data.h"
#include "strategy.h"

// forward declaration
class CryptoGraphic;
class CryptoGuiPanel;
class Strategy;

// globals shared pointers
static std::shared_ptr<CryptoGraphic> _cryptoGraphic;
static std::shared_ptr<CryptoGuiPanel> _cryptoGuiPanel;
static std::shared_ptr<Strategy> _strategyPtr;

// globals protection variables
static std::mutex _mtx;
static std::condition_variable _cdtGraphic;

// globals graphics variables
static bool _paintGraphics = false;
static bool _updateGraphics = true;
static std::deque<wxCoord> y_val{};
static int secs = 0;

enum
{
  ID_CONFIGURE_STRATEGY = wxID_HIGHEST + 1,
  ID_CREATE_HISTORICAL_DATA,
  ID_SIMULATE_DATA,
  ID_SIMULATE_DATA_STOP,
  ID_HISTORICAL_DATA,
  ID_HISTORICAL_DATA_STOP,
  ID_REAL_DATA,
  ID_REAL_DATA_STOP
};

/*
Main class for CryptoBot
*/
class CryptoBot : public wxApp
{
public:
  virtual bool OnInit();
};

/*
Class for main Gui
*/
class CryptoGui : public wxFrame
{
public:
  // constructor
  CryptoGui(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
  // menu options
  void OnConfigureStrategy(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);

  wxDECLARE_EVENT_TABLE();
};

/*
Class for main Gui
*/
class CryptoGuiPanel : public wxPanel
{
public:
  // constructor / destructor
  CryptoGuiPanel(wxPanel *parent);
 
  // events
  void OnCreateHistoricalData(wxCommandEvent &event);
  void OnStartSimulatedData(wxCommandEvent &event);
  void OnStopSimulatedData(wxCommandEvent &event);
  void OnStartHistoricalData(wxCommandEvent &event);
  void OnStopHistoricalData(wxCommandEvent &event);
  void OnStartRealData(wxCommandEvent &event);
  void OnStopRealData(wxCommandEvent &event);

  // start and stop retrieve of data and the strategy of automatic trading
  template <class T>
  void StartStrategy(std::string dataThrName, std::string strategyThrName, wxButton *stopBtn);
  void KillThreads(std::vector<std::string> threadsToKill, wxButton *stopBtn);

  // handler function
  void setStrategyHandle(std::shared_ptr<Strategy> strategy);

  // propietary functions
  void setOutputDataStrategy(bool _openPosition, double order, double benefit, int nOrders, double benefitsAcc, double investmentAcc);
  void updateOutputData();

  // getter / setter
  std::string getExchange();
  std::string getCryptoConcurrency();
  std::string getStrategy();
  double getInvestment();

  // helper function
  std::string getFirstValue(std::string s);


private:
  // strategy values
  bool _openPosition = false;
  double _order = 0;
  double _benefit = 0;
  int _nOrders = 0;
  double _benefitsAcc = 0;
  double _investmentAcc = 0;

  // info variables
  wxStaticText *_strategyType;
  wxStaticText *_exchangeTxt;
  wxStaticText *_commissionValue;
  wxStaticText *_cryptocurrencyType;
  wxStaticText *_investmentValue;

  wxStaticText *_openPositionValue;
  wxStaticText *_lastOrderValue;
  wxStaticText *_benefitsValue;
  wxStaticText *_interestValue;
  wxStaticText *_numberOfOrdersValue;
  wxStaticText *_benefitsAccValue;
  wxStaticText *_interestAccValue;

  std::string _exchange;
  std::string _cryptoConcurrency;
  std::string _strategy;
  std::string _investment;
};

/*
Class to draw graphics
*/
class CryptoGraphic : public wxPanel
{
public:
  // constructor / destructor
  CryptoGraphic(wxWindow *parent, wxWindowID id);

  // setter
  void setActualValue(double value);
  void setLimits(double _base, bool openPosition, double entry, double bottomBreak, double recession, double topBreak);

  // events
  void OnPaint(wxPaintEvent &evt);

  // draw functions
  void drawAxis(wxDC &dc, wxSize size);
  void drawTics(wxDC &dc, wxSize size);
  void drawLimits(wxDC &dc, wxSize size);
  void drawGraphic(wxDC &dc, wxSize size);
  void updateVectorValues();
  void createTicks();
  void updateTicks();
  void render(wxDC &dc);

  // helper functions
  int valueToPixel(int value, int sizey);

private:
  // graphics variables
  double _value;
  double _base;
  int _limitUp = 0;
  int _limitDown = 0;
  int maxValue = 65000;
  int minValue = 0;
  int oldSecs = -1;
  int xTime = 60; // 1 min of representation

  // margins in graphic
  int xBorderLeft = 50;
  int xBorderRight = 30;
  int yBorderUp = 30;
  int yBorderDown = 10;

  // labels for ticks
  wxStaticText *_yTickLabel0;
  wxStaticText *_yTickLabel1;
  wxStaticText *_yTickLabel2;
  wxStaticText *_yTickLabel3;
  wxStaticText *_yTickLabel4;

  wxStaticText *_xTickLabel0;
  wxStaticText *_xTickLabel1;
  wxStaticText *_xTickLabel2;
  wxStaticText *_xTickLabel3;
  wxStaticText *_xTickLabel4;
};

#endif