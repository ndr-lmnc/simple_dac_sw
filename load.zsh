#!/bin/zsh
# This script is used to flash the main.hex file to the LSD board
# It assumes that the LSD-master folder is in the Downloads folder

tty_device="/dev/tty.usbserial-DU0CQEAD"

source ~/Downloads/LSD-master/.venv/bin/activate
python3 ~/Downloads/LSD-master/lsd.py -p $tty_device -e -wp ./main.hex -v
deactivate
