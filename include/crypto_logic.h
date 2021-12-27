#ifndef CRYPTO_LOGIC_H_
#define CRYPTO_LOGIC_H_

#include "crypto_gui.h"

// forward declarations
class CryptoGraphic;

class CryptoLogic : std::enable_shared_from_this<CryptoLogic>
{
public:
    CryptoLogic();
    void startSimulation();
    void setDataFromStrategy(double value);
    //void SetCryptoGraphicHandle(std::shared_ptr<CryptoGraphic> cryptoGraphic);
    void SetCryptoGraphicHandle(CryptoGraphic * cryptoGraphic);
    void sendToLogic(double value);

private:
    double _actual_value;
    //std::shared_ptr<CryptoGraphic> _cryptoGraphic;
    CryptoGraphic * _cryptoGraphic;
    //Strategy * _strategy;

    // ptr of panel...
    //Sería ideal poder tener aquí el puntero del panel para poder meterle el dato directamente...
    //Revisar el método SetPanelDialogHandle de chatlogic.h

};

#endif