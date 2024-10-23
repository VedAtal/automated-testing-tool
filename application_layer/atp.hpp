/*
 * atp.hpp:
 ***********************************************************************
 * Program to execute Accepted Testing Procedures (ATPs).
 ***********************************************************************
 */


#include <vector>

#include "../hardware_drivers/gpio.hpp"
#include "../hardware_drivers/spi.hpp"
#include "../board_controllers/dio.hpp"
#include "../board_controllers/psu.hpp"
#include "../board_controllers/dmm.hpp"
#include "zif.hpp"
#include "itr.hpp"

#ifndef ATPHANDLER
#define ATPHANDLER

class ATPHandler {
    private:
        /** 
         * Stores the DIO pins being used for the ZIF that is under stimulus for the current test.
         * 0. CMA, measurement bus 1
         * 1. CMB, measurement bus 2
         * 2. Vout
         * 3. Ground 
         */
        std::vector<DIOController::DIOPinInfo> currentDIOPins;

        /** Stores the DIO power pin being used for the ZIF that is under stimulus for the current test. */
        DIOController::DIOPinInfo currentDIOPowerPin;

        /** Stores the DAC being used for the ZIF that is under stimulus for the current test. */
        int currentDAC;

        int continuity(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int openCircuit(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int diodeTestForward(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int diodeTestReverse(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int setVoltage(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int voltage(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int removeVoltage(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int commonGround(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int removeDMM(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int user(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int wait(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int setPWM(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int lightPlatePWM(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int removePWM(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int resistance(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int frequency(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int CANPeriodicWrite(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int CANReadUser(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int CANUpdateRead(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int ARINC429PeriodicWrite(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int ARINC429Read(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int ARINC429ReadUser(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int ARINC429ASCIIRead(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int inputDCVoltageMeasure(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int inputDCCurrentMeasure(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int dutyCycle(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int positiveSquareWaveAmplitude(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int powerAndGroundSeperation(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int powerOn(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int powerOff(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int CANEncoder(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int userInput(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

        int powerInterrupt(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);

    public:
        /**
         * Reads the current test and handles the corresponding ATP that needs to be executed.
         * @param gpio a GPIO driver.
         * @param spi a SPI driver.
         * @param dio a DIO board controller.
         * @param psu a PSU board controller.
         * @param dmm a DMM board controller.
         * @param zif the zif mapper.
         * @param currentTest the current ITR test.
         * @returns -1 if the test fails, or -2 if test type is unrecognized.
         */
        int runCurrentTest(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest);
};

#endif