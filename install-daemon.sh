#!/bin/bash -euf

./uninstall-daemon.sh &> /dev/null

source ./vars.sh

printf "Compiling ... "
rm -f keywatcher
gcc -Wall -Wpedantic main.c -o keywatcher
sudo mv keywatcher "$BIN_DEST_PATH"
printf "done\n"

sudo cp systemd.service "$SERVICE_DEST_PATH"

sudo systemctl start "$SERVICE_NAME"
sudo systemctl enable "$SERVICE_NAME"

printf "SUCCESSFULLY INSTALLED\n"
