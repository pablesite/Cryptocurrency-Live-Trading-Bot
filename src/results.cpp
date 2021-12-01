#include "results.h"

#include <string>
#include <wx/colour.h>
#include <wx/filename.h>
#include <wx/image.h>


std::string dataPath = "../";
std::string imgBasePath = dataPath + "images/";


ResultsPanel::ResultsPanel(wxWindow *parent, wxWindowID id)
    : wxScrolledWindow(parent, id) {
  // sizer will take care of determining the needed scroll size
  _dialogSizer = new wxBoxSizer(wxVERTICAL);
  this->SetSizer(_dialogSizer);

  // allow for PNG images to be handled
  wxInitAllImageHandlers();

  //// STUDENT CODE
  ////

  // create chat logic instance
//   /*** TASK 1. create new unique smart pointer in stack ***/
//   _chatLogic = std::make_unique<ChatLogic>();

//   // pass pointer to chatbot dialog so answers can be displayed in GUI
//   _chatLogic->SetPanelDialogHandle(this);

//   // load answer graph from file
//   _chatLogic->LoadAnswerGraphFromFile(dataPath + "src/answergraph.txt");

  ////
  //// EOF STUDENT CODE
}

ResultsPanel::~ResultsPanel() {
  //// STUDENT CODE
  ////

  /*** TASK 1. _chatLogic is SmartPointer, so it is not necessary deallocate
   * manually.***/
  // delete _chatLogic;

  ////
  //// EOF STUDENT CODE
}

void ResultsPanel::AddDialogItem(wxString text, bool isFromUser) {
  // add a single dialog element to the sizer
//   ChatBotPanelDialogItem *item =
//       new ChatBotPanelDialogItem(this, text, isFromUser);
//   _dialogSizer->Add(
//       item, 0, wxALL | (isFromUser == true ? wxALIGN_LEFT : wxALIGN_RIGHT), 8);
//   _dialogSizer->Layout();

  // make scrollbar show up
  this->FitInside(); // ask the sizer about the needed size
  this->SetScrollRate(5, 5);
  this->Layout();

  // scroll to bottom to show newest element
  int dx, dy;
  this->GetScrollPixelsPerUnit(&dx, &dy);
  int sy = dy * this->GetScrollLines(wxVERTICAL);
  this->DoScroll(0, sy);
}

void ResultsPanel::PrintChatbotResponse(std::string response) {
  // convert string into wxString and add dialog element
  wxString botText(response.c_str(), wxConvUTF8);
  AddDialogItem(botText, false);
}

void ResultsPanel::paintEvent(wxPaintEvent &evt) {
  wxPaintDC dc(this);
  render(dc);
}

void ResultsPanel::paintNow() {
  wxClientDC dc(this);
  render(dc);
}

void ResultsPanel::render(wxDC &dc) {
  wxImage image;
  image.LoadFile(imgBasePath + "bitcoint.jpg");

  wxSize sz = this->GetSize();
  wxImage imgSmall =
      image.Rescale(sz.GetWidth(), sz.GetHeight(), wxIMAGE_QUALITY_HIGH);

  _image = wxBitmap(imgSmall);
  dc.DrawBitmap(_image, 0, 0, false);
}