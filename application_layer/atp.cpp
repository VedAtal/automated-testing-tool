/*
 * atp.cpp:
 ***********************************************************************
 * Program to execute Accepted Testing Procedures (ATPs).
 ***********************************************************************
 */


#include <iostream>
#include <string>

#include "atp.hpp"
#include "../hardware_drivers/gpio.hpp"
#include "../hardware_drivers/spi.hpp"
#include "../board_controllers/dio.hpp"
#include "../board_controllers/psu.hpp"
#include "../board_controllers/dmm.hpp"
#include "zif.hpp"

int ATPHandler::runCurrentTest(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest) {
    return 0; // currently disabled

    if (currentTest.testType == "Continuity") return continuity(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Open Circuit") return openCircuit(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Diode Test Forward") return diodeTestForward(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Diode Test Reverse") return diodeTestReverse(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Set Voltage") return setVoltage(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Voltage") return voltage(gpio, spi, dio, psu, dmm, zif, currentTest);    
    else if (currentTest.testType == "Remove Voltage") return removeVoltage(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Common Ground") return commonGround(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Remove DMM") return removeDMM(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "User") return user(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Wait") return wait(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Set PWM") return setPWM(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Light Plate PWM") return lightPlatePWM(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Remove PWM") return removePWM(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Resistance") return resistance(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Frequency") return frequency(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "CAN Read User") return CANReadUser(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "CAN Update Read") return CANUpdateRead(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Input DC Voltage Measure") return inputDCVoltageMeasure(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Input DC Current Measure") return inputDCCurrentMeasure(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Duty Cycle") return dutyCycle(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Positive Square Wave Amplitude") return positiveSquareWaveAmplitude(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Power and Ground Seperation") return powerAndGroundSeperation(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Power On") return powerOn(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Power Off") return powerOff(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "CAN Encoder") return CANEncoder(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "User Input") return userInput(gpio, spi, dio, psu, dmm, zif, currentTest);
    else if (currentTest.testType == "Power Interrupt") return powerInterrupt(gpio, spi, dio, psu, dmm, zif, currentTest);
    else return -2;

    return 0;
};

int ATPHandler::setVoltage(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest) {
    for (int i = 0; i < currentTest.stimPin.size(); i++) {
        std::string currentStimPin = currentTest.stimPin.at(i);
        double currentStimVolt = std::stod(currentTest.stimVolt.at(i));
        ATPHandler::currentDIOPins = zif.getDIOFromZIF(currentStimPin);
        ATPHandler::currentDIOPowerPin = zif.getDIOPowerFromZIF(currentStimPin);
        ATPHandler::currentDAC = zif.getDACFromZIF(currentStimPin);

        psu.applyVoltage(spi, gpio, ATPHandler::currentDAC, currentStimVolt, PSUController::DAC_CS);

        dio.enablePin(spi, gpio, currentDIOPins.at(2));
    }
    return 0;
}

int ATPHandler::removeVoltage(GPIODriver& gpio, SPIDriver& spi, DIOController& dio, PSUController& psu, DMMController& dmm, ZIFMapper& zif, ITRParser::Test currentTest) {
    for (int i = 0; i < currentTest.stimPin.size(); i++) {
        std::string currentStimPin = currentTest.stimPin.at(i);
        ATPHandler::currentDIOPins = zif.getDIOFromZIF(currentStimPin);
        ATPHandler::currentDIOPowerPin = zif.getDIOPowerFromZIF(currentStimPin);
        ATPHandler::currentDAC = zif.getDACFromZIF(currentStimPin);

        psu.applyVoltage(spi, gpio, ATPHandler::currentDAC, 0.0, PSUController::DAC_CS);

        dio.disablePin(spi, gpio, currentDIOPins.at(2));
    }
    return 0;
}

// ......