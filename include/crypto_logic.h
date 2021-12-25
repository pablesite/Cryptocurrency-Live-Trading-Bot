#ifndef CRYPTO_LOGIC_H_
#define CRYPTO_LOGIC_H_

#include "crypto_gui.h"

// forward declarations
class CryptoGraphic;

class CryptoLogic
{
public:
    CryptoLogic();
    void startSimulation();
    void setDataFromStrategy(double value);
    void SetCryptoGraphicHandle(CryptoGraphic *cryptoGraphic);

private:
    double _actual_value;
    CryptoGraphic *_cryptoGraphic;

    // ptr of panel...
    //Sería ideal poder tener aquí el puntero del panel para poder meterle el dato directamente...
    //Revisar el método SetPanelDialogHandle de chatlogic.h

};

#endif