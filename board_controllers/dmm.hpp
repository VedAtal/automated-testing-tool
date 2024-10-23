/*
 * dmm.hpp:
 ***********************************************************************
 * Digital Multimeter measurement. Interfaces with:
 *      LTC2380-24, 24-bit SPI-based differential input ADC.
 *      https://www.analog.com/media/en/technical-documentation/data-sheets/238024fa.pdf
 ***********************************************************************
 */


#include "../hardware_drivers/gpio.hpp"
#include "../hardware_drivers/spi.hpp"

#ifndef DMMCONTROLLER
#define DMMCONTROLLER

class DMMController {
    private:
        /** The SDI pin on the ADC which can act as a CS. */
        const int DMM_CS = 25;

        /** The conversion start pin, which triggers a new conversion. */
        const int DMM_CNV = 29;

        /** These values need to be obtained from the electrical architecture of the DMM. */
        /** The multiplier for the voltage measurement. */
        const double VOLTAGE_MULTIPLY = 20.0;

        /** 2.3% consistent error offset. */
        const double VOLTAGE_ERROR_OFFSET = 1.023;

        /** The divisor for the current measurement. */
        const double CURRENT_DIVIDE = 7.995;

        /** The multiplier for the current measurement. */
        const double CURRENT_MULTIPLY = 10.0;

        /** An estimated nanosecond delay function. */
        void delayNanoseconds(int howLong);

    public:
        /**
         * Completes proper intialization procedure to ensure PSU board is in ready state.
         * Ensures DAC is reset.
         * @param spi a SPI diver.
         * @param gpio a GPIO driver.
         * @returns -1 if initialization failed.
         */
        int initDMM(SPIDriver& spi, GPIODriver& gpio);

        /** 
         * Read the current input on the ADC.
         * @param spi a SPI diver.
         * @param gpio a GPIO driver.
         * @param voltage indicates whether the reading is for voltage or current.
         * @returns the value read from the ADC.
         */
        int read(SPIDriver& spi, GPIODriver& gpio, bool voltage);
        
};

#endif