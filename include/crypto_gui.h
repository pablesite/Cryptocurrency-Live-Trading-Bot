#ifndef CRYPTO_GUI_H_
#define CRYPTO_GUI_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/statline.h>
#endif

#include <future>
#include "crypto_logic.h"

class CryptoBot : public wxApp
{
public:
  virtual bool OnInit();
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
  
  wxDECLARE_EVENT_TABLE();

  std::unique_ptr<CryptoLogic> _cryptoLogic;
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

public:
  // constructor / destructor
  CryptoGuiPanel(wxPanel *parent, bool isFromUser);
};

#endif