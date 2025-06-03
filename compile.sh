#!/bin/bash
dirs=(dmenu dwm slock slstatus st)

for dir in "${dirs[@]}"; do
    if [ -d "$dir" ]; then
        echo -e "\n==> Building $dir..."
        cd "$dir"
        make clean
        if make; then
            echo "[OK] $dir compiled successfully."
            echo "==> Installing $dir (sudo required)..."
            if sudo make install; then
                echo "[OK] $dir installed successfully."
            else
                echo "[FAIL] $dir failed to install."
            fi
        else
            echo "[FAIL] $dir failed to compile."
        fi
        cd ..
    else
        echo "[SKIP] $dir directory not found."
    fi
done
