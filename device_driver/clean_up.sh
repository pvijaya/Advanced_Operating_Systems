#!/bin/sh

make clean
sudo rmmod dev_file.ko
sudo rm -f /dev/dev_file
