/*
 * itr_parser.cpp:
 ***********************************************************************
 * Program to parse ITR files and feed instructions.
 ***********************************************************************
 */


#include <fstream>
#include <iostream>
#include <string>

#include "itr.hpp"

int ITRParser::initITRParser(std::string ITRPath) {
    // Opens ITR file specified and verifies if it worked.
    ITRParser::ITR.open(ITRPath);
    if (!ITR.is_open()) {
        return -1;
    }
    ITRParser::isITRCompleted = false;
    return 0;
};

int ITRParser::readNextTest() {
    for (int col = 0; col < ITR_COLUMN_COUNT; col++) {
        char res[250];
        ITRParser::ITR.getline(res, 250, ',');
        ITRParser::isITRCompleted = ITRParser::ITR.peek() == EOF;

        if (col > 16) continue;
        
        switch (col)
        {
            case 0: // Test #
                ITRParser::currentTest.testNumber = res;
                break;

            case 1: // OID Test
                ITRParser::currentTest.oidTest = res;
                break;

            case 2: // Test Position
                ITRParser::currentTest.testPosition = res;
                break;

            case 3: // Test Type
                ITRParser::currentTest.testType = res;
                break;

            case 4: // Stim Pin
                // Handler for when multiple inputs exist. Same logic for the next 4 cell input fields.
                ITRParser::currentTest.stimPin.clear();
                if (res[0] == '\"') { // Quotation indicates a mutli-line entry in a cell.
                    int stimCounter = 0;
                    int index = 1;
                    std::string stimPinName = "";
                    while (res[index] != '\"') { // Loop until end quotation is found.
                        if (res[index] == '\n') { // Each new line is a new input entry.
                            stimCounter++;
                            ITRParser::currentTest.stimPin.push_back(stimPinName);
                            stimPinName = "";
                        } else {
                            stimPinName += res[index];
                        }
                        index++;
                    }
                    stimCounter++;
                    ITRParser::currentTest.stimPin.push_back(stimPinName);
                    ITRParser::currentTest.stimCount = stimCounter;
                } else {
                    ITRParser::currentTest.stimPin.push_back(res);
                    ITRParser::currentTest.stimCount = 1;
                }
                break;

            case 5: // Meas Pin
                ITRParser::currentTest.measPin.clear();
                if (res[0] == '\"') {
                    int index = 1;
                    std::string measPinName = "";
                    while (res[index] != '\"') {
                        if (res[index] == '\n') {
                            ITRParser::currentTest.measPin.push_back(measPinName);
                            measPinName = "";
                        } else {
                            measPinName += res[index];
                        }
                        index++;
                    }
                    ITRParser::currentTest.measPin.push_back(measPinName);
                } else {
                    ITRParser::currentTest.measPin.push_back(res);
                }
                break;

            case 6: // Stim Volt
                ITRParser::currentTest.stimVolt.clear();
                if (res[0] == '\"') {
                    int index = 1;
                    std::string stimVoltName = "";
                    while (res[index] != '\"') {
                        if (res[index] == '\n') {
                            ITRParser::currentTest.stimVolt.push_back(stimVoltName);
                            stimVoltName = "";
                        } else {
                            stimVoltName += res[index];
                        }
                        index++;
                    }
                    ITRParser::currentTest.stimVolt.push_back(stimVoltName);
                } else {
                    ITRParser::currentTest.stimVolt.push_back(res);
                }
                break;

            case 7: // App Units
                ITRParser::currentTest.appUnits.clear();
                if (res[0] == '\"') {
                    int index = 1;
                    std::string appUnitsName = "";
                    while (res[index] != '\"') {
                        if (res[index] == '\n') {
                            ITRParser::currentTest.appUnits.push_back(appUnitsName);
                            appUnitsName = "";
                        } else {
                            appUnitsName += res[index];
                        }
                        index++;
                    }
                    ITRParser::currentTest.appUnits.push_back(appUnitsName);
                } else {
                    ITRParser::currentTest.appUnits.push_back(res);
                }
                break;

            case 8: // Stim Con
                ITRParser::currentTest.stimCon = res;
                break;

            case 9: // Address
                ITRParser::currentTest.address = res;
                break;

            case 10: // L Bound
                ITRParser::currentTest.lBound = res;
                break;

            case 11: // U Bound
                ITRParser::currentTest.uBound = res;
                break;

            case 12: // Meas Unit
                ITRParser::currentTest.measUnits = res;
                break;

            case 13: // Instruction
                ITRParser::currentTest.instruction = res;
                break;

            case 14: // Prompt
                ITRParser::currentTest.prompt = res;
                break;

            case 15: // Abort If Fail
                ITRParser::currentTest.abortIfFail = res;
                break;

            case 16: // Pass Prompt Delay
                ITRParser::currentTest.passPromptDelay = res;
                break;

            default: // All others columns
                break;
        }
    }
    // Single increment at the end, to dicard new line character after each column.
    ITRParser::ITR.get();
    return 0;
};

bool ITRParser::ITRCompleted() {
    return ITRParser::isITRCompleted;
}