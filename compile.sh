#!/bin/bash

g++ main.cpp hardware_drivers/gpio.cpp hardware_drivers/spi.cpp board_controllers/dio.cpp board_controllers/psu.cpp board_controllers/dmm.cpp application_layer/itr.cpp application_layer/atp.cpp application_layer/zif.cpp -o cpats -lwiringPi

echo Program Compiled!