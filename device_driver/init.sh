#!/bin/sh

make
sudo insmod dev_file.ko
sudo mknod /dev/dev_file c 60 0
sudo chmod 666 /dev/dev_file
