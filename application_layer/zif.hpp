/*
 * zif.hpp:
 ***********************************************************************
 * Wrapper class to map all ZIF pins to DIO pins to be used by the program.
 ***********************************************************************
 */


#include <string>
#include <unordered_map>
#include <vector>

#include "../board_controllers/dio.hpp"

#ifndef ZIFMAPPER
#define ZIFMAPPER

// Primary expanders.
#define U1 0
#define U2 1
//Secondary expanders.
#define U3 2
#define U4 3
#define U5 4
#define U6 5
#define U7 6
#define U8 7
#define U9 8
#define U10 9
#define U11 10
#define U12 11
#define U13 12
#define U14 13
#define U15 14
#define U16 15
#define U17 16
#define U18 17
#define U19 18
#define U20 19
#define U21 20
#define U22 21
#define U23 22
#define U24 23
#define U25 24
#define U26 25
#define U27 26
#define U28 27
#define U29 28
#define U30 29
#define U31 30
#define U32 31
#define U33 32
#define U34 33

// Expander pins to value.
#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7
#define B0 8
#define B1 9
#define B2 10
#define B3 11
#define B4 12
#define B5 13
#define B6 14
#define B7 15

// GPB Boards
#define GPB_BOARD_1 0
#define GPB_BOARD_2 1
#define GPB_BOARD_3 2
#define GPB_BOARD_4 3

// GPB Board Banks
#define GPB_BANK_1 0
#define GPB_BANK_2 1
#define GPB_BANK_3 3

// DAC output connection.
#define DAC1 0
#define DAC2 1
#define DAC3 2
#define DAC4 3
#define DAC5 4
#define DAC6 5
#define DAC7 6
#define DAC8 7
#define DAC9 8
#define DAC10 9
#define DAC11 10
#define DAC12 11

class ZIFMapper {
    private:
        /** Stores all ZIF pins by their name and the corresponding DIO pins. */
        std::unordered_map<std::string, std::vector<DIOController::DIOPinInfo>> ZIFPins;

        /** Stores all ZIF pins info by their name and the corresponding DIO pins. */
        std::unordered_map<std::string, std::vector<int>> ZIFPinsInfo;
        
        /** Maps from GPB board and bank to the corresponding DIO pins that connect to power rails. */
        std::vector<std::vector<DIOController::DIOPinInfo>> ZIFPowerPins;

        /** 
         * Takes DIO pin parameters and returns a DIOPin object to be used for a ZIF pin.
         * @param primaryExpander indicates the primary expander the secondary expander is on.
         * @param primaryPin indicates the pin with the CS of the secondary expander.
         * @param secondaryExpander indicates the secondary expander which the DIO pin resides on.
         * @param seondaryPin indicates the pin on the secondary expander which the DIO pin resides on.
         */
        DIOController::DIOPinInfo makeDIOPin(int primaryExpander, int primaryPin, int secondaryExpander, int secondaryPin);

        /**
         * Takes ZIF pin parameters to make a ZIF pin and add it to the ZIF pin map. 
         * @param zifPin the name of the ZIF pin.
         * @param measure1 the DIO pin used for measurement.
         * @param measure2 the other DIO pin used for measurement.
         * @param vout the pin that connects to voltage supply.
         * @param ground the pin that connects to ground.
         * @param gpbBoard the GPB Board that the pin is on.
         * @param gpbBank the GPB bank that the pin is on.
         * @param dac the DAC output rail.
         */
        void makeZIFPin(std::string zifPin, DIOController::DIOPinInfo measure1, DIOController::DIOPinInfo measure2, 
            DIOController::DIOPinInfo vout, DIOController::DIOPinInfo ground, int gpbBoard, int gpbBank, int dac);

    public:
        /**
         * Populates the map with ZIF to DIO connections.
         */
        void initZIF();

        /**
         * Returns a list of DIO pins associated with a ZIF pin given a ZIF pin name.
         * @param zifPin the name of the ZIF pin.
         * @returns vector of the DIO pins or an empty vector if ZIF pin not found.
         */
        std::vector<DIOController::DIOPinInfo> getDIOFromZIF(std::string zifPin);

        /**
         * Returns the DIO pin that power the associated ZIF pin given a ZIF pin name.
         * @param zifPin the name of the ZIF pin.
         * @returns the DIO power pins or an empty DIO struct if ZIF pin not found.
         */
        DIOController::DIOPinInfo getDIOPowerFromZIF(std::string zifPin);

        /**
         * Returns the DAC that power the associated ZIF pin given a ZIF pin name.
         * @param zifPin the name of the ZIF pin.
         * @returns the DAC or -1 if ZIF pin not found.
         */
        int getDACFromZIF(std::string zifPin);
};

#endif