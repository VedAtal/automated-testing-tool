/*
 * itr_parser.hpp:
 ***********************************************************************
 * Program to parse ITR files and feed instructions.
 ***********************************************************************
 */


#include <fstream>
#include <string>
#include <list>
#include <vector>

#ifndef ITRPARSER
#define ITRPARSER

class ITRParser {
    private:
        /** ITR file reader for parsing the data. */
        std::ifstream ITR;

        /** Inidctaes if the whole file has been read. */
        bool isITRCompleted;

        /** Number of columns in ITRs. */
        const int ITR_COLUMN_COUNT = 31;

    public:
        /** Stores information about the current test being executed. */
        struct Test {
            std::string testNumber;
            std::string oidTest;
            std::string testPosition;
            std::string testType;
            std::vector<std::string> stimPin;
            std::vector<std::string> measPin;
            std::vector<std::string> stimVolt;
            std::vector<std::string> appUnits;
            std::string stimCon;
            std::string address;
            std::string lBound;
            std::string uBound;
            std::string measUnits;
            std::string instruction;
            std::string prompt;
            std::string abortIfFail;
            std::string passPromptDelay;
            int stimCount;
        } currentTest;


        /**
         * Initializes the ITR file so it can be read from.
         * @param ITRPath the name of the ITR file.
         * @returns -1 if initialization failed.
         */
        int initITRParser(std::string ITRPath);

        /**
         * Reads, parses, and then stores the information for next test.
         * @returns -1 if parsing failed.
         */
        int readNextTest();

        /** 
         * Indicates if the whole ITR file has been read. 
         * @returns true is file has been completely read.
         */
        bool ITRCompleted();

};

#endif