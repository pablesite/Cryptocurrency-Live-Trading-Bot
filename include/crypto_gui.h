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


class CryptoGraphic; // forward declaration
class CryptoGuiPanel; // forward declaration
class Strategy; // forward declaration

//static CryptoGraphic * _cryptoGraphic;
static std::shared_ptr<CryptoGraphic> _cryptoGraphic;
//static CryptoGuiPanel * _cryptoGuiPanel; 
static std::shared_ptr<CryptoGuiPanel> _cryptoGuiPanel;

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

  std::shared_ptr<Strategy> _strategy;

public:
  // constructor / destructor
  CryptoGraphic(wxWindow *parent, wxWindowID id);
  ~CryptoGraphic();

  // getter / setter
  void setActualValue(double value);
  void setLimits();
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
  void OnHello(wxCommandEvent &event);
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

  wxStaticText *position_bool;
  wxStaticText *last_order_cc_value;
  wxStaticText *last_order_$_value;
  wxStaticText *benefits_value;
  wxStaticText *benefits_acc_value;
  wxStaticText *interest_value;

  wxPanel *graphics_results;


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

  template <class T> void StartStrategy(std::string dataThrName, std::string strategyThrName, wxButton *stop_btn);
  void KillThreads(std::vector<std::string> threadsToKill, wxButton *stop_btn);

     
};



#endif