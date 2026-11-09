#!/usr/bin/env sh
# ==============================================================================
# Fast Downloader for CN Lab Experiments
# Compatible with Ubuntu, Debian, Fedora, Arch, and POSIX shells (sh, bash, zsh)
# ==============================================================================

set -e

# Target directory
TARGET_DIR="${HOME}/Downloads"
mkdir -p "${TARGET_DIR}"

echo ""
echo "=========================================="
echo " Starting Download to: ${TARGET_DIR}"
echo "=========================================="

# ------------------------------------------------------------------------------
# Configuration: GitHub repository raw URL and files to download
# ------------------------------------------------------------------------------
BASE_URL="https://raw.githubusercontent.com/Ashile99/cn-files/main"
FILES="${*:-chatc.c chats.c filc.c fils.c matc.c mats.c sample.txt timc.c tims1.c trac.c tras.c}"

# Helper function to download files using curl or wget
fetch_file() {
    url="$1"
    destination="$2"
    filename="$3"

    echo ""
    echo "==> Downloading: ${filename}..."

    if command -v curl >/dev/null 2>&1; then
        if ! curl -fSL --connect-timeout 5 --progress-bar "${url}" -o "${destination}"; then
            echo "Error: Failed to download ${filename} via curl." >&2
            exit 1
        fi
    elif command -v wget >/dev/null 2>&1; then
        if ! wget -q --show-progress -O "${destination}" "${url}"; then
            echo "Error: Failed to download ${filename} via wget." >&2
            exit 1
        fi
    else
        echo "Error: Neither 'curl' nor 'wget' is installed on this system." >&2
        echo "Please install one (e.g. sudo apt install curl / sudo pacman -S curl / sudo dnf install curl) and try again." >&2
        exit 1
    fi
}

# Download each file
for file in ${FILES}; do
    fetch_file "${BASE_URL}/${file}" "${TARGET_DIR}/${file}" "${file}"
done

# Verify files exist and print final summary
echo ""
echo "=========================================="
echo " [✓] Download Completed Successfully!"
echo " Files saved to: ${TARGET_DIR}"
for file in ${FILES}; do
    echo "   - ${file} ($(ls -lh "${TARGET_DIR}/${file}" 2>/dev/null | awk '{print $5}' || echo 'saved'))"
done
echo "=========================================="
echo ""
