

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

// helpers functions (private)
double Strategy::getIndex()
{
    return _value / _base - 1;
}

void Strategy::updateLimits()
{
    // set limits in cryptoGraphic
    _cryptoGraphic->setLimits(_base, _openPosition, _entry, _bottomBreak, _recession, _topBreak);
}

void Strategy::updateOutputDataStrategy()
{
    // update output data from strategy to CryptoGuiPanel
    _cryptoGuiPanel->setOutputDataStrategy(_openPosition, _order, _benefit, _nOrders, _benefitsAcc, _investmentAcc);
}

// main --> thread
void Strategy::cryptoBot()
{
    std::cout << "CryptoBot starting " << std::endl;

    // set strategy handle to CryptoGuiPanel
    _cryptoGuiPanel->setStrategyHandle(shared_from_this());

    // get config data
    _exchange = _cryptoGuiPanel->getExchange();
    _cryptoConcurrency = _cryptoGuiPanel->getCryptoConcurrency();
    _strategy = _cryptoGuiPanel->getStrategy();
    _investment = _cryptoGuiPanel->getInvestment();

    // initialize output strategy data
    _value = 0;
    _base = 0;
    _openPosition = false;
    _order = 0;
    _benefit = 0;
    _nOrders = 0;
    _benefitsAcc = 0;
    _investmentAcc = 0;
    _computedData = 0;

    // initialize CryptoGuiPanel, base value and CryptoGraphic
    _base = getData(_lookBackPeriod);
    updateOutputDataStrategy();
    updateLimits();

    while (true)
    {
        // retrieve data
        _value = getData(_lookBackPeriod);

        // send data to CryptoGraphic
        _cryptoGraphic->setActualValue(_value);

        // how many data has been processed
        _computedData += 1;

        if (_openPosition == false)
        {
            // debug in console
            // std::cout << std::setprecision(4) << std::fixed << "To buy " << _value << " => " << (1 + _bottomBreak) * _base << " < " << _base << " > " << (1 + _entry) * _base << " N: " << computedData << std::endl;

            // to update base if the trend is negative
            if (getIndex() < _bottomBreak)
            {
                // update base and update limits
                _base = _value;
                updateLimits();

                // debug in console
                std::cout << "Update the base: Descending " << _value << " " << std::endl;
            }

            // to make an order if the trend is positive
            if (getIndex() > _entry)
            {
                // manage position
                _openPosition = true;

                // update base and update limits
                _base = _value;
                updateLimits();

                // perform an order (simulation) FOR THE FUTURE: perform real orders using api from Binance
                _order = _investment / (_value * (1 + _commission));
                _investmentAcc += _investment;

                // set output data strategy to CryptoGuiPanel
                updateOutputDataStrategy();

                // debug in console
                std::cout << "Buying my position " << _order << " bitcoint. Actual value: " << _value << "." << std::endl;
            }
        }
        else
        {
            // debug in console
            // std::cout << std::setprecision(4) << std::fixed << "To sell " << _value << " => " << (1 + _recession) * _base << " < " << _base << " > " << (1 + _topBreak) * _base << " N: " << computedData << std::endl;

            // update base while the value is rissing
            if (getIndex() > _topBreak)
            {
                // update base and update limits
                _base = _value;
                updateLimits();

                // debug in console
                std::cout << "Update the base: Rising " << _value << std::endl;
            }

            // perform sell if trend is negative
            if (getIndex() < _recession)
            {
                // manage position
                _openPosition = false;

                // update base and update limits
                _base = _value;
                updateLimits();

                // sell the order
                _benefit = (_order * _value * (1 - _commission)) - _investment; // simulate the sell
                _benefitsAcc += _benefit;

                _nOrders += 1;

                // set output data strategy to CryptoGuiPanel
                updateOutputDataStrategy();

                // debug in console
                std::cout << "Selling my position: " << _order << " bitcoints. Actual value: " << _value << ". Benefits = " << _benefit << " $." << std::endl;
                std::cout << "Total Benefits: " << _benefitsAcc << "$. " << _benefitsAcc / _investment * 100 << "%. " << _computedData << std::endl
                          << std::endl
                          << std::endl;
            }
        }
    }
}
