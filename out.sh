#!/bin/bash

echo 165 >/sys/class/gpio/export
echo 160 >/sys/class/gpio/export
echo 164 >/sys/class/gpio/export
echo 159 >/sys/class/gpio/export

echo in >/sys/class/gpio/gpio165/direction
echo in >/sys/class/gpio/gpio160/direction
echo in >/sys/class/gpio/gpio164/direction
echo in >/sys/class/gpio/gpio159/direction
   
