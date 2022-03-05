#ifndef CRYPTO_GUI_H_
#define CRYPTO_GUI_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/statline.h>
#endif

#include <future>
#include <optional>
#include "simulate_data.h"
#include <unordered_map>
#include "strategy.h"

// std::condition_variable _cdtMQ;
// std::mutex _mtxMQ;

class CryptoGraphic; // forward declaration
class CryptoGuiPanel; // forward declaration
class Strategy; // forward declaration

//static CryptoGraphic * _cryptoGraphic;
static std::shared_ptr<CryptoGraphic> _cryptoGraphic;
//static CryptoGuiPanel * _cryptoGuiPanel; 
static std::shared_ptr<CryptoGuiPanel> _cryptoGuiPanel;
static std::shared_ptr<Strategy> _strategyPtr;

class CryptoBot : public wxApp
{
public:
  virtual bool OnInit();

};





// graphics for real time data
class CryptoGraphic : public wxPanel 
{
private:
  // control elements
  //wxPanel * _cryptoGraphicPanel;
  // wxBoxSizer *_dialogSizer;
  // wxBitmap _image;


  double _actual_value;
  double _actual_base;

  double _actual_commission = 0;
  double _actual_entry = 0;
  double _actual_rupture = 0;
  double _actual_recession = 0;

  int _limit_up=0, _limit_down=0;

  std::mutex _mtx;

  // std::shared_ptr<Strategy> _strategy;

public:
  // constructor / destructor
  CryptoGraphic(wxWindow *parent, wxWindowID id);
  ~CryptoGraphic();

  // getter / setter
  void setActualValue(double value);
  //void setLimits();
  void setLimits(bool open_position, double _entry, double _bottom_break, double _recession, double _top_break);
  void setStrategyHandle(std::shared_ptr<Strategy> strategy);
  void setStrategyData(double commission, double entry, double rupture, double recession);
  int valueToPixel(int value, int sizey);

  // events
  void OnPaint(wxPaintEvent &evt);
  void render(wxDC &dc);
  void drawAxis(wxDC &dc, wxSize size);
  void drawTics(wxDC &dc, wxSize size);
  void drawQuartiles(wxDC &dc, wxSize size);
  void drawGraphic(wxDC &dc, wxSize size);
  void updateVectorValues();
  void createTicks();
  void updateTicks();


  // proprietary functions
  // void AddDialogItem(wxString text, bool isFromUser = true);
  // void PrintChatbotResponse(std::string response);

  DECLARE_EVENT_TABLE()
};






class CryptoGui : public wxFrame
{
public:
  CryptoGui(const wxString &title, const wxPoint &pos, const wxSize &size);
  void OnPaint(wxPaintEvent & event);

private:
  void OnConfigureStrategy(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);

  // std::shared_ptr<SimulateData> _dataSimulatedPtr;

  

  
  wxDECLARE_EVENT_TABLE();

};









class CryptoGuiPanel : public wxPanel 
{
private:
  // control elements
  //wxStaticBitmap *_chatBotImg;

  wxStaticText *strategy_type;
  wxStaticText *exchange;
  wxStaticText *commission_value;
  wxStaticText *cryptocurrency_type;
  wxStaticText *investment_value;

  wxStaticText *position_bool;
  wxStaticText *last_order_value;
  wxStaticText *benefits_value;
  wxStaticText *interest_value;
  wxStaticText *number_of_orders_value;
  wxStaticText *benefits_acc_value;
  wxStaticText *interest_acc_value;

  wxPanel *graphics_results;

  // config data
  std::string _exchange;
  std::string _cryptoConcurrency;
  std::string _strategy;
  std::string _investment;

  std::shared_ptr<SimulateData> _simulateDataPtr; 

  bool _receive_true = true;


  //DECLARE_EVENT_TABLE()

public:
  // constructor / destructor
  CryptoGuiPanel(wxPanel *parent, bool isFromUser);
  // ~CryptoGuiPanel();

  void OnCreateHistoricalData(wxCommandEvent &event);
  void OnStartSimulatedData(wxCommandEvent& event);
  void OnStopSimulatedData(wxCommandEvent& event);
  void OnStartHistoricalData(wxCommandEvent& event);
  void OnStopHistoricalData(wxCommandEvent& event);
  void OnStartRealData(wxCommandEvent& event);
  void OnStopRealData(wxCommandEvent& event);
  void setStrategyHandle(std::shared_ptr<Strategy> strategy);

  void setPosition();
  void setOutputDataStrategy(bool _open_position, double order, double benefit, int nOrders, double benefits_acc, double investment_acc);

  std::string getExchange();
  std::string getCryptoConcurrency();
  std::string getStrategy();
  double getInvestment();

  bool receiveTrue();


  template <class T> std::shared_ptr<T> StartStrategy(std::string dataThrName, std::string strategyThrName, wxButton *stop_btn);
  void KillThreads(std::vector<std::string> threadsToKill, wxButton *stop_btn);

     
};



#endif