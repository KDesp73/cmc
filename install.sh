#!/bin/bash

exe="cmc"
exe_path="./build/$exe"

if [ -f "$exe_path" ]; then
	sudo cp $exe_path /usr/bin/$exe

    # Install man page
    sudo install -g 0 -o 0 -m 0644 $exe.man /usr/share/man/man8/$exe.8
    sudo gzip /usr/share/man/man8/$exe.8
    if [ $? -ne 0 ]; then
        echo "[ERRO] Failed to install man page"
        exit 1
    fi
    echo "[INFO] man page installed successfully"

    echo "[INFO] Installation completed successfully."
fi
