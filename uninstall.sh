#!/usr/bin/env bash

# Developer: Sreeraj
# GitHub: https://github.com/s-r-e-e-r-a-j

set -e

APP_NAME="iris"
BIN_DIR="/usr/local/bin"

if [ -f "$BIN_DIR/$APP_NAME" ]; then
    echo "Removing $APP_NAME from $BIN_DIR..."
    sudo rm -f "$BIN_DIR/$APP_NAME"
    echo "$APP_NAME uninstalled successfully!"
else
    echo "$APP_NAME is not installed in $BIN_DIR."
fi
