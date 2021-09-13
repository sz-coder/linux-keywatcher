#!/bin/bash -euf

source vars.sh

if [ -f "$SERVICE_DEST_PATH" ]; then
	printf "Found .service file.\n"

	printf "Stopping service ..."
	sudo systemctl stop "$SERVICE_NAME"
	printf "done\n"

	printf "Unloading from systemd ... "
	sudo systemctl disable "$SERVICE_NAME"
	printf "done\n"

	sudo rm -f "$SERVICE_DEST_PATH"
fi

if [ -f "$BIN_DEST_PATH" ]; then
	sudo rm -f "$BIN_DEST_PATH"
fi

printf "SUCCESSFULLY UNINSTALLED\n"
