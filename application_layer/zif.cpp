/*
 * zif.cpp:
 ***********************************************************************
 * Wrapper class to map all ZIF pins to DIO pins to be used by the program.
 ***********************************************************************
 */


#include <string>
#include <vector>

#include "zif.hpp"
#include "../board_controllers/dio.hpp"

void ZIFMapper::initZIF() {
    // All ZIF pins and the four DIO pins asssociated with each one.
    //      Grouped into 4s, by the expander they belong to.
    makeZIFPin("P21-A1", 
        makeDIOPin(U1, A7, U3, A0), 
        makeDIOPin(U1, A7, U3, A1), 
        makeDIOPin(U1, A7, U3, A2), 
        makeDIOPin(U1, A7, U3, A3), 
        GPB_BOARD_1, GPB_BANK_1, DAC1);
    makeZIFPin("P21-A2", 
        makeDIOPin(U1, A7, U3, A4), 
        makeDIOPin(U1, A7, U3, A5), 
        makeDIOPin(U1, A7, U3, A6), 
        makeDIOPin(U1, A7, U3, A7), 
        GPB_BOARD_1, GPB_BANK_1, DAC1);
    makeZIFPin("P21-A3", 
        makeDIOPin(U1, A7, U3, B0), 
        makeDIOPin(U1, A7, U3, B1), 
        makeDIOPin(U1, A7, U3, B2), 
        makeDIOPin(U1, A7, U3, B3), 
        GPB_BOARD_1, GPB_BANK_1, DAC1);
    makeZIFPin("P21-A4", 
        makeDIOPin(U1, A7, U3, B4), 
        makeDIOPin(U1, A7, U3, B5), 
        makeDIOPin(U1, A7, U3, B6), 
        makeDIOPin(U1, A7, U3, B7), 
        GPB_BOARD_1, GPB_BANK_1, DAC1);

    makeZIFPin("P21-A5", 
        makeDIOPin(U1, A6, U4, A0), 
        makeDIOPin(U1, A6, U4, A1), 
        makeDIOPin(U1, A6, U4, A2), 
        makeDIOPin(U1, A6, U4, A3), 
        GPB_BOARD_1, GPB_BANK_1, DAC1);
    makeZIFPin("P21-B1", 
        makeDIOPin(U1, A6, U4, A4), 
        makeDIOPin(U1, A6, U4, A5), 
        makeDIOPin(U1, A6, U4, A6), 
        makeDIOPin(U1, A6, U4, A7), 
        GPB_BOARD_1, GPB_BANK_1, DAC1);
    makeZIFPin("P21-B2", 
        makeDIOPin(U1, A6, U4, B0), 
        makeDIOPin(U1, A6, U4, B1), 
        makeDIOPin(U1, A6, U4, B2), 
        makeDIOPin(U1, A6, U4, B3), 
        GPB_BOARD_1, GPB_BANK_1, DAC1);
    makeZIFPin("P21-B3", 
        makeDIOPin(U1, A6, U4, B4), 
        makeDIOPin(U1, A6, U4, B5), 
        makeDIOPin(U1, A6, U4, B6), 
        makeDIOPin(U1, A6, U4, B7), 
        GPB_BOARD_1, GPB_BANK_1, DAC1);

    //........

    
    // Insert all power rail pins for all GPB banks (indexed from 0-11). In the respective order:
    //    DAC
    std::vector<DIOController::DIOPinInfo> voltagePins;

    // Board 1, bank 1
    voltagePins.push_back(makeDIOPin(U1, A1, U9, B4));
    ZIFMapper::ZIFPowerPins.push_back(voltagePins);
    voltagePins.clear();

    // Board 1, bank 2
    voltagePins.push_back(makeDIOPin(U1, A1, U9, B5)); 
    ZIFMapper::ZIFPowerPins.push_back(voltagePins);
    voltagePins.clear();

    // Board 1, bank 3
    voltagePins.push_back(makeDIOPin(U1, A1, U9, B6)); 
    ZIFMapper::ZIFPowerPins.push_back(voltagePins);
    voltagePins.clear();

    // Board 2, bank 1
    voltagePins.push_back(makeDIOPin(U1, B5, U17, B4));
    ZIFMapper::ZIFPowerPins.push_back(voltagePins);
    voltagePins.clear();

    // Board 2, bank 2
    voltagePins.push_back(makeDIOPin(U1, B5, U17, B5)); 
    ZIFMapper::ZIFPowerPins.push_back(voltagePins);
    voltagePins.clear();

    // Board 2, bank 3
    voltagePins.push_back(makeDIOPin(U1, B5, U17, B6)); 
    ZIFMapper::ZIFPowerPins.push_back(voltagePins);
    voltagePins.clear();

    // Board 3, bank 1
    voltagePins.push_back(makeDIOPin(U2, A1, U25, B4));
    ZIFMapper::ZIFPowerPins.push_back(voltagePins);
    voltagePins.clear();

    // Board 3, bank 2
    voltagePins.push_back(makeDIOPin(U2, A1, U25, B5)); 
    ZIFMapper::ZIFPowerPins.push_back(voltagePins);
    voltagePins.clear();

    // Board 3, bank 3
    voltagePins.push_back(makeDIOPin(U2, A1, U25, B6)); 
    ZIFMapper::ZIFPowerPins.push_back(voltagePins);
    voltagePins.clear();

    // Board 4, bank 1
    voltagePins.push_back(makeDIOPin(U2, B5, U33, B4));
    ZIFMapper::ZIFPowerPins.push_back(voltagePins);
    voltagePins.clear();

    // Board 4, bank 2
    voltagePins.push_back(makeDIOPin(U2, B5, U33, B5)); 
    ZIFMapper::ZIFPowerPins.push_back(voltagePins);
    voltagePins.clear();

    // Board 4, bank 3
    voltagePins.push_back(makeDIOPin(U2, B5, U33, B6)); 
    ZIFMapper::ZIFPowerPins.push_back(voltagePins);
    voltagePins.clear();
};

// Returns the list of DIO pins assoicated with the ZIF pin.
std::vector<DIOController::DIOPinInfo> ZIFMapper::getDIOFromZIF(std::string zifPin) {
    auto key = ZIFMapper::ZIFPins.find(zifPin);
    if (key != ZIFMapper::ZIFPins.end()) {
        return key->second;
    } else { // If the ZIF pin does not exist.
        return {};
    }
};

// Returns the DAC DIO pin that needs to be enabled to connect to power.
DIOController::DIOPinInfo ZIFMapper::getDIOPowerFromZIF(std::string zifPin) {
    auto key = ZIFMapper::ZIFPinsInfo.find(zifPin);
    if (key != ZIFMapper::ZIFPinsInfo.end()) {
        std::vector<int> infoList = key->second;
        int index = infoList.at(0)*3 + infoList.at(1); // Convert GPB board and bank to a 0-11 index.
        return ZIFMapper::ZIFPowerPins.at(index).at(0);
    } else { // If the ZIF pin does not exist.
        struct DIOController::DIOPinInfo dio = {
            .primaryExpander = 0, 
            .primaryPin = 0, 
            .secondaryExpander = 0, 
            .secondaryPin = 0
        };
        return dio;
    }
};

// Returns the DAC (output) which the pin is on.
int ZIFMapper::getDACFromZIF(std::string zifPin) {
    auto key = ZIFMapper::ZIFPinsInfo.find(zifPin);
    if (key != ZIFMapper::ZIFPinsInfo.end()) {
        std::vector<int> infoList = key->second;
        return infoList.at(2);
    } else { // If the ZIF pin does not exist.
        return -1;
    }
};

DIOController::DIOPinInfo ZIFMapper::makeDIOPin(int primaryExpander, int primaryPin, int secondaryExpander, int secondaryPin) {
    struct DIOController::DIOPinInfo dio = {
        .primaryExpander = primaryExpander, 
        .primaryPin = primaryPin, 
        .secondaryExpander = secondaryExpander, 
        .secondaryPin = secondaryPin
    };
    return dio;
};

void ZIFMapper::makeZIFPin(std::string zifPin, DIOController::DIOPinInfo measure1, DIOController::DIOPinInfo measure2, 
DIOController::DIOPinInfo vout, DIOController::DIOPinInfo ground, int gpbBoard, int gpbBank, int dac) {
    std::vector<DIOController::DIOPinInfo> dioPins;
    dioPins.push_back(measure1);
    dioPins.push_back(measure2);
    dioPins.push_back(vout);
    dioPins.push_back(ground);

    std::vector<int> pinInfo;
    pinInfo.push_back(gpbBoard);
    pinInfo.push_back(gpbBank);
    pinInfo.push_back(dac);

    ZIFMapper::ZIFPins[zifPin] = dioPins;
    ZIFMapper::ZIFPinsInfo[zifPin] = pinInfo;
};
