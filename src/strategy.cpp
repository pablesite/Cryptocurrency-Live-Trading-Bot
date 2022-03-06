

#include "strategy.h"

// constructors
Strategy::Strategy(std::shared_ptr<Binance> data) : _dataBinance(move(data))
{
    std::cout << "Constructor of Strategy with real data from Binance " << std::endl;
    _type = TypesOfData::Binance;
}

Strategy::Strategy(std::shared_ptr<SimulateData> data) : _dataSimulated(move(data))
{
    std::cout << "Constructor of Strategy with data simulated " << std::endl;
    _type = TypesOfData::SimulateData;
}

Strategy::Strategy(std::shared_ptr<HistoricData> data) : _dataHistoric(move(data))
{
    std::cout << "Constructor of Strategy with historic data " << std::endl;
    _type = TypesOfData::HistoricData;
}

// handlers
void Strategy::SetCryptoGraphicHandle(std::shared_ptr<CryptoGraphic> cryptoGraphic)
{
    _cryptoGraphic = cryptoGraphic;
}

void Strategy::SetCryptoGuiPanelHandle(std::shared_ptr<CryptoGuiPanel> cryptoGuiPanel)
{
    _cryptoGuiPanel = cryptoGuiPanel;
}

// getters
double Strategy::getData(double lookBackPeriod)
{
    switch (_type)
    {
    case TypesOfData::Binance:
    {
        return _dataBinance->retrieveData(lookBackPeriod);
        break;
    }
    case TypesOfData::SimulateData:
    {
        return _dataSimulated->retrieveData(lookBackPeriod);
        break;
    }
    case TypesOfData::HistoricData:
    {
        return _dataHistoric->retrieveData(lookBackPeriod);
        break;
    }
    default:
    {
        std::cout << "Error: There is no type selected." << std::endl;
        return 0;
        break;
    }
    }
}

double Strategy::getBase()
{
    return _base;
}

// helpers functions (private)
 double Strategy::getIndex()
{
    return _value / _base - 1;
}

void Strategy::updateBase()
{
     std::unique_lock<std::mutex> lck(_mtx); //protect call to CryptoGraphic
    // update base value
    _base = _value;

    // update limits in cryptoGraphic
   
     _cryptoGraphic->setLimits(_base, _openPosition, _entry, _bottomBreak, _recession, _topBreak);
     lck.unlock();
}

// main --> thread
void Strategy::cryptoBot()
{
    std::cout << "CryptoBot starting " << std::endl;
    
    // set strategy handle to CryptoGuiPanel and CryptoGraphic
    _cryptoGuiPanel->setStrategyHandle(shared_from_this());
    //_cryptoGraphic->setStrategyHandle(shared_from_this()); //Esto sólo vale para llamar métodos de strategy desde cryptographic.

    // get config data
    std::unique_lock<std::mutex> lck(_mtx); //protect CryptoGuiPanel shrPtr
    _exchange = _cryptoGuiPanel->getExchange();
    _cryptoConcurrency = _cryptoGuiPanel->getCryptoConcurrency();
    _strategy = _cryptoGuiPanel->getStrategy();
    _investment = _cryptoGuiPanel->getInvestment();
    lck.unlock();

    // initialize output strategy data
    _openPosition = false;
    double order = 0;          
    double benefit = 0;       
    int nOrders = 0;           
    double benefitsAcc = 0;   
    double investmentAcc = 0;
    double computedData = 0;

    // initialize CryptoGuiPanel, base value and CryptoGraphic
    lck.lock(); //protect shared pointers and base variable
    _cryptoGuiPanel->setOutputDataStrategy(_openPosition, order, benefit, nOrders, benefitsAcc, investmentAcc);
    _base = getData(_lookBackPeriod);
    _cryptoGraphic->setLimits(_base, _openPosition, _entry, _bottomBreak, _recession, _topBreak);
    lck.unlock();

    while (true)
    {
        // std::this_thread::sleep_for(std::chrono::milliseconds(14));
        // retrieve data
        _value = getData(_lookBackPeriod);

        // send data to CryptoGraphic
        // std::unique_lock<std::mutex> lck(_mtx); //protect CryptoGraphic shrPtr
        // // // updateGraphics = _cryptoGraphic->getUpdateGraphics();
        // // // std::cout << "UPDATE GRAPHICS IN STRATEGY: " << updateGraphics << std::endl;

        // // // _cdtGraphic.wait(lck, [] { return updateGraphics; });
        // // // updateGraphics = false;
        // // // _cryptoGraphic->setUpdateGraphics(updateGraphics);
        _cryptoGraphic->setActualValue(_value);
        // aquí debería poner un wait a la gráfica para que enviara un nuevo dato sólo una vez esta haya termiando el refresh!
        // lck.unlock();

        //how many data has been processed
        computedData += 1;

        if (_openPosition == false)
        {
            // debug in console
            // std::unique_lock<std::mutex> lck(_mtx); 
            // std::cout << std::setprecision(4) << std::fixed << "To buy " << _value << " => " << (1 + _bottomBreak) * _base << " < " << _base << " > " << (1 + _entry) * _base << " N: " << computedData << std::endl;
            // lck.unlock();

            // to update base if the trend is negative
            if (getIndex() < _bottomBreak)
            {
                // debug in console
                std::unique_lock<std::mutex> lck(_mtx); 
                std::cout << "Update the base: Descending " << _value << " " << std::endl;
                lck.unlock();

                updateBase();
            }

            // to make an order if the trend is positive
            if (getIndex() > _entry)
            {
                std::unique_lock<std::mutex> lck(_mtx);
                // perform an order (simulation) FOR THE FUTURE: perform real orders using api from Binance
                order = _investment / (_value * (1 + _commission));
                investmentAcc += _investment;
            
                // manage position
                _openPosition = true;
                
                // debug in console
                std::cout << "Buying my position " << order << " bitcoint. Actual value: " << _value << "." << std::endl;
                lck.unlock();

                // update base
                updateBase();

                // set output data strategy to CryptoGuiPanel
                lck.lock(); // protect CryptoGuiPanel shrPtr
                _cryptoGuiPanel->setOutputDataStrategy(_openPosition, order, benefit, nOrders, benefitsAcc, investmentAcc);
                lck.unlock();
            }
        }
        else
        {
            // debug in console
            // std::unique_lock<std::mutex> lck(_mtx); 
            // std::cout << std::setprecision(4) << std::fixed << "To sell " << _value << " => " << (1 + _recession) * _base << " < " << _base << " > " << (1 + _topBreak) * _base << " N: " << computedData << std::endl;
            // lck.unlock();

            // update base while the value is rissing
            if (getIndex() > _topBreak)
            {
                // updateBase
                std::unique_lock<std::mutex> lck(_mtx); 
                std::cout << "Update the base: Rising " << _value << std::endl;
                lck.unlock();

                // updateBase
                updateBase();
            }

            // if last_entry > x or last_entry < x --> Sell
            if (getIndex() < _recession)
            {
                std::unique_lock<std::mutex> lck(_mtx);
                // sell the order
                benefit = (order * _value * (1 - _commission)) - _investment; // simulate the sell
                benefitsAcc += benefit;

                // manage position
                _openPosition = false;
                nOrders += 1;
                
                // debug in console
                std::cout << "Selling my position: " << order << " bitcoints. Actual value: " << _value << ". Benefits = " << benefit << " $." << std::endl;
                std::cout << "Total Benefits: " << benefitsAcc << "$. " << benefitsAcc / _investment * 100 << "%. " << computedData << std::endl << std::endl << std::endl;
                lck.unlock();
                
                // updateBase
                updateBase();

                // set output data strategy to CryptoGuiPanel
                lck.lock();
                _cryptoGuiPanel->setOutputDataStrategy(_openPosition, order, benefit, nOrders, benefitsAcc, investmentAcc);
                lck.unlock();
            }
        }

    }
}
