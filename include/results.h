#ifndef RESULTS_H_
#define RESULTS_H_

// #include <wx/wx.h>

// // middle part of the window containing the dialog between user and chatbot
// class ResultsPanel : public wxScrolledWindow
// {
// private:
//     // control elements
//     wxBoxSizer *_dialogSizer;
//     wxBitmap _image;

//     //// STUDENT CODE //DONE
//     ////

//     /*** TASK 1. Declare an unique pointer named _chatLogic***/
//     //   std::unique_ptr<ChatLogic> _chatLogic;

//     ////
//     //// EOF STUDENT CODE //DONE

// public:
//     // constructor / destructor
//     ResultsPanel(wxWindow *parent, wxWindowID id);
//     ~ResultsPanel();

//     // getter / setter

//     /*** TASK 1. Use of get() property of Unique Pointer to get address memory
//    * ***/
//     //   ChatLogic *GetChatLogicHandle() { return _chatLogic.get(); }

//     // events
//     void paintEvent(wxPaintEvent &evt);
//     void paintNow();
//     void render(wxDC &dc);

//     // proprietary functions
//     void AddDialogItem(wxString text, bool isFromUser = true);
//     void PrintChatbotResponse(std::string response);

//     DECLARE_EVENT_TABLE()
// };
#include <iostream>
#include <future>

#include "message_queue.h"
#include "simulate_data.h"
#include "binance.h"
#include "strategy.h"
#include "historic_data.h"


#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};
enum
{
    ID_Hello = 1
};
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello,   MyFrame::OnHello)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    

        // Request what do you want to do?
    // 1 - Simulate the strategy
    //      1 - Simulated data
    //      2 - Historical data
    //      2 - Real time data
    // 2 - Create new data series


    MyFrame *frame = new MyFrame( "Hello World", wxPoint(50, 50), wxSize(450, 340) );
    frame->Show( true );

    int value;
    std::cout << "\nWelcome to the Cryptoconcurrency Live Trading Bot. Here you can either simulate a strategy or create new data series. \n";

    std::cout << "\nPlease, select between the following options: \n1: Simulate a strategy. \n2: Create new data series: \n";
    std::cout << "\nWhich one you prefer? : ";
    std::cin >> value;

    // switch (value)
    // {
    // case 1:
    // {
    //     std::cout << "\nPlease, select between the following options: \n1: Simulate with data simulated. \n2: Simulate with an historical data. \n3: Simulate with real time data. \n";
    //     std::cout << "\nWhich one you prefer? : ";
    //     std::cin >> value;
    //     switch (value)
    //     {
    //     case 1:
    //     {
    //         //DATA SIMULATED
    //         std::shared_ptr<SimulateData> dataSimulatedPtr = std::make_shared<SimulateData>();
    //         std::thread dataSimulated = std::thread(&SimulateData::fetchData, dataSimulatedPtr);

    //         // STRATEGY            
    //         std::shared_ptr<Strategy> strategyDataSimulatedPtr = std::make_shared<Strategy>(dataSimulatedPtr);
    //         std::thread strategyDataSimulatedBot = std::thread(&Strategy::cryptoBot, strategyDataSimulatedPtr);

    //         dataSimulated.join();
    //         strategyDataSimulatedBot.join();

    //         break;
    //     }
    //     case 2:
    //     {
    //         // HISTORICAL DATA (IN FILE)
    //         std::shared_ptr<HistoricData> historicDataPtr = std::make_shared<HistoricData>();
    //         std::thread historicData = std::thread(&HistoricData::fetchData, historicDataPtr);

    //         // STRATEGY
    //         std::shared_ptr<Strategy> strategyHistoricPtr = std::make_shared<Strategy>(historicDataPtr);
    //         std::thread strategyHistoricBot = std::thread(&Strategy::cryptoBot, strategyHistoricPtr);

    //         historicData.join();
    //         strategyHistoricBot.join();

    //         break;
    //     }
    //     case 3:
    //     {
    //         // REAL DATA IN REAL TIME
    //         std::shared_ptr<Binance> binancePtr = std::make_shared<Binance>();
    //         std::thread binanceData = std::thread(&Binance::fetchData, binancePtr);

    //         // STRATEGY
    //         std::shared_ptr<Strategy> strategyBinancePtr = std::make_shared<Strategy>(binancePtr);
    //         std::thread strategyBinanceBot = std::thread(&Strategy::cryptoBot, strategyBinancePtr);

    //         binanceData.join();
    //         strategyBinanceBot.join();

    //         break;
    //     }
    //     default:
    //         std::cout << "\nSorry. Selected option is not valid. \n";
    //     }

    //     break;
    // }

    // case 2:
    // {
    //     std::cout << "\nCreating new data series with real data: " << value << "\n";

    //     // REAL DATA IN REAL TIME
    //     std::shared_ptr<Binance> binancePtr = std::make_shared<Binance>();
    //     std::thread binanceData = std::thread(&Binance::fetchData, binancePtr);
    //     // 2. CREATE NEW DATA SERIES
    //     std::shared_ptr<HistoricData> dataFilePtr = std::make_shared<HistoricData>();
    //     std::thread writeHistoricData = std::thread(&HistoricData::createHistoricData, dataFilePtr, binancePtr);

    //     writeHistoricData.join();
    //     binanceData.join();
    //     break;
    // }

    // default:
    //     std::cout << "\n Sorry. Selected option is not valid. \n";
    // }

    

    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
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
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );

    std::cout << "Into constructor of MyFrame" << std::endl;
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
                  "About Hello World", wxOK | wxICON_INFORMATION );
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}


#endif