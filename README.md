****************************************************
Ved Atal - 2024
****************************************************

Software is divided into 3 layers.
Hardware Drivers
 * Control the underlying hardware of the RPi.
 * GPIO - deals with general purpose I/O.
 * SPI - deals with the SPI pins on the RPi, used for communication.
 * Drivers are made by WiringPi library and this program abtracts over that in a wrapper class for some additioanl functionality.

Board Controllers
 * DIO - this board handles the 512 I/O pins from the 34x MCP expanders.
 * DMM - this board handles reading inputs through the 1x LTC ADC on it.
    * Only board that was not individually tested and verified. Check note on dmm.cpp on line 34-35.
    * This board (specifically the ADC) might need additional testing to get working, more info on note mentioned above + datasheet of the IC.
 * PSU - this baord handles distributing variable power through the 2x AD DAC.

Application Layer
 * Files in this do not directly pertain to any physical system, but control other necessary functions of the application.
 * ATP - This is the final step that puts everything together, it actually executes the flow for each individual test type/instruction.
 * ITR - This parses the ITR provided line by line for the program to execute.
 * ZIF - This maps all ZIF pins that are in the ITRs to their corresponding DIO pins.


General Notes.
WiringPi
 * It is included in the project directory and should work. If it doesn't work:
   * Necessary to go to WiringPi github and follow installation steps to install their library for the drivers to work.

compile.sh
 * Run this bash script to compile the program, it's stored in here becuase it a long command and this makes it easy to run.

****************************************************