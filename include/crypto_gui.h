#ifndef CRYPTO_GUI_H_
#define CRYPTO_GUI_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/statline.h>
#endif

#include <future>
#include <optional>
#include "crypto_logic.h"
#include "simulate_data.h"
#include <unordered_map>

class CryptoLogic; // forward declaration
class CryptoGraphic; // forward declaration

static CryptoGraphic * _cryptoGraphic;

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

  //std::unique_ptr<ChatLogic> _chatLogic;
  std::unique_ptr<CryptoLogic> _cryptoLogic; 
  double _actual_value;

public:
  // constructor / destructor
  CryptoGraphic(wxWindow *parent, wxWindowID id);
  ~CryptoGraphic();

  // getter / setter
  CryptoLogic *GetCryptoLogicHandle() { return _cryptoLogic.get(); }
  void setActualValue(double value);
  int valueToPixel(int value, int sizey);

  // events
  void paintEvent(wxPaintEvent &evt);
  void OnPaint(wxPaintEvent &evt);
  void paintNow();
  void render(wxDC &dc);


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

  std::shared_ptr<CryptoLogic> _cryptoLogic; //El puntero de la lógica está repetido......está también en CryptoGraphic. Cuidado
  std::shared_ptr<SimulateData> dataSimulatedPtr;

  
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
  CryptoGuiPanel(wxPanel *parent, bool isFromUser, std::shared_ptr<CryptoLogic> cryptoLogic);
  // ~CryptoGuiPanel();

  void OnCreateHistoricalData(wxCommandEvent &event);
  void OnStartSimulatedData(wxCommandEvent& event);
  void OnStopSimulatedData(wxCommandEvent& event);
  void OnStartHistoricalData(wxCommandEvent& event);
  void OnStopHistoricalData(wxCommandEvent& event);
  void OnStartRealData(wxCommandEvent& event);
  void OnStopRealData(wxCommandEvent& event);

  template <class T> void StartStrategy(std::string dataThrName, std::string strategyThrName, wxButton *start_btn, wxButton *stop_btn);
  void KillThreads(std::vector<std::string> threadsToKill, wxButton *start_btn,wxButton *stop_btn);

     
};



#endif