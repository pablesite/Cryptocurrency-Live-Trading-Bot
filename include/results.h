#ifndef RESULTS_H_
#define RESULTS_H_

#include <wx/wx.h>

// middle part of the window containing the dialog between user and chatbot
class ResultsPanel : public wxScrolledWindow
{
private:
    // control elements
    wxBoxSizer *_dialogSizer;
    wxBitmap _image;

    //// STUDENT CODE //DONE
    ////

    /*** TASK 1. Declare an unique pointer named _chatLogic***/
    //   std::unique_ptr<ChatLogic> _chatLogic;

    ////
    //// EOF STUDENT CODE //DONE

public:
    // constructor / destructor
    ResultsPanel(wxWindow *parent, wxWindowID id);
    ~ResultsPanel();

    // getter / setter

    /*** TASK 1. Use of get() property of Unique Pointer to get address memory
   * ***/
    //   ChatLogic *GetChatLogicHandle() { return _chatLogic.get(); }

    // events
    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void render(wxDC &dc);

    // proprietary functions
    void AddDialogItem(wxString text, bool isFromUser = true);
    void PrintChatbotResponse(std::string response);

    DECLARE_EVENT_TABLE()
};

#endif