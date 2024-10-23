/*
 * main.cpp:
 *	Created in 2024 by Ved Atal
 ***********************************************************************
 * Program to Control main logic for testing system.
 ***********************************************************************
 */


#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <iostream>

#include "hardware_drivers/gpio.hpp"
#include "hardware_drivers/spi.hpp"
#include "board_controllers/dio.hpp"
#include "board_controllers/psu.hpp"
#include "board_controllers/dmm.hpp"
#include "application_layer/itr.hpp"
#include "application_layer/atp.hpp"
#include "application_layer/zif.hpp"

class TestProgram {
    private:
        GPIODriver gpio;
        SPIDriver spi;
        DIOController dio;
        PSUController psu;
        DMMController dmm;
        ITRParser itr;
        ATPHandler atp;
        ZIFMapper zif;
    public:
        /**
         * Main program--executes all logic.
         */
        void run() {
            // Final configuration and confirmation before execution.
            if (preExecutionChecks() == false) {
                return;
            };

            // Loops through ITR row by row and executes the tests.
            int row = 1;
            while (itr.ITRCompleted() == false) {
                if (itr.readNextTest() == -1) {
                    std::cout << "Something went wrong while parsing next test instruction. Exiting Program.\n";
                    return;
                }

                // Skip title rows.
                if (row > 3) {
                    int result = atp.runCurrentTest(gpio, spi, dio, psu, dmm, zif, itr.currentTest);
                    if (result == -2) {
                        std::cout << "Test #" << itr.currentTest.testNumber << " has unrecognized test type: " << itr.currentTest.testType << ". Exiting Program.\n";
                        return;
                    } else if (result == -1) {
                        std::cout << "Test #" << itr.currentTest.testNumber << ", " << itr.currentTest.testType << " - RESULT: FAIL" << "\n";
                    } else {
                        std::cout << "Test #" << itr.currentTest.testNumber << ", " << itr.currentTest.testType << " - RESULT: PASS" << "\n";
                    }
                }

                row++;
            }


            std::cout << "Program finished successfully.\n";
        };


        /** 
         * Ensures all bootups are successful, ITR is loaded, and user input is provided.
         */
        bool preExecutionChecks() {
            // Some safety and configuration steps prior to running tests.
            if (systemBootupChecks() == false) {
                std::cout << "Program failed to bootup properly. Exiting Program.\n";
                return false;
            } else {
                std::cout << "Program bootup successful.\n";
            }

            if (configureITRChecks() == false) {
                std::cout << "Program failed to load ITR. Exiting Program.\n";
                return false;
            } else {
                std::cout << "ITR load successful.\n\n";
            }

            std::string userInput;
            std::cout << "Program ready to run. Start ITR [Y/n]?\n";
            std::cin >> userInput;
            if (userInput == "n") {
                std::cout << "User aborted Program. Exiting Program.\n";
                return false;
            } else if (userInput == "Y") {
                std::cout << "User input accepted. Starting Program.\n";
            } else {
                std::cout << "User input invalid. Enter 'Y' or 'n'. Exiting Program.\n";
                return false;
            }

            return true;
        };


        /**
         * Ensures all necessary systems properly initialize before running program.
         * @returns false if validation failed.
         */
        bool systemBootupChecks() {
            bool passedChecks = true;

            // Stage 1: Setup hardware library.
            if (wiringPiSetup() == -1) {
                std::cout << "RaspberryPi hardware library--WiringPi setup failed.\n";
                passedChecks = false;
            } else {
                std::cout << "RaspberryPi hardware library--WiringPi setup successful.\n";
            }

            // Stage 2: Setup drivers.
            if (passedChecks) {
                if (gpio.initGPIO() == -1) {
                    std::cout << "RaspberryPi GPIO Driver setup failed.\n";
                    passedChecks = false;
                } else {
                    std::cout << "RaspberryPi GPIO Driver setup successful.\n";
                }

                if (spi.initSPI() == -1) {
                    std::cout << "RaspberryPi SPI Driver setup failed.\n";
                    passedChecks = false;
                } else {
                    std::cout << "RaspberryPi SPI Driver setup successful.\n";
                }
            }

            // Stage 3: Setup boards.
            if (passedChecks) {
                if (dio.initDIO(spi, gpio) == -1) {
                    std::cout << "DIO Board setup failed.\n";
                    passedChecks = false;
                } else {
                    std::cout << "DIO Board setup successful.\n";
                }

                if (psu.initPSU(spi, gpio) == -1) {
                    std::cout << "PSU Board setup failed.\n";
                    passedChecks = false;
                } else {
                    std::cout << "PSU Board setup sucessful.\n";
                }

                if (dmm.initDMM(spi, gpio) == -1) {
                    std::cout << "DMM Board setup failed.\n";
                    passedChecks = false;
                } else {
                    std::cout << "DMM Board setup sucessful.\n";
                }
            }

            // Map all ZIF pins to DIO pins.
            zif.initZIF();
            std::cout << "ZIF pins map sucessful.\n";

            return passedChecks;
        }


        /**
         * Ensures ITR is properly configured to be parsed from.
         * @return false if validation failed.
         */
        bool configureITRChecks() {
            std::string ITRPath;
            std::cout << "Enter ITR file path: \n";
            std::cin >> ITRPath;
            if (itr.initITRParser(ITRPath) == -1) {
                std::cout << "\nRaspberryPi ITR parser setup failed.\n";
                return false;
            }
            return true;
        }
};


int main(void) {
    TestProgram test;
    test.run();

    return 0;
}