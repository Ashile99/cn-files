#!/usr/bin/env sh
# ==============================================================================
# Ultra-Fast Parallel Downloader for CN Lab Experiments
# Compatible with Ubuntu, Debian, Fedora, Arch, macOS, and POSIX shells (sh, bash, zsh)
# ==============================================================================

set -e

# Target directory
TARGET_DIR="${HOME}/Downloads"
mkdir -p "${TARGET_DIR}"

echo ""
echo "=========================================="
echo " Starting Fast Parallel Download"
echo " Destination: ${TARGET_DIR}"
echo "=========================================="

# ------------------------------------------------------------------------------
# Configuration
# ------------------------------------------------------------------------------
BASE_URL="https://raw.githubusercontent.com/Ashile99/cn-files/main"
FILES="${*:-chatc.c chats.c filc.c fils.c matc.c mats.c sample.txt timc.c tims1.c trac.c tras.c}"

# Check if curl supports native --parallel multiplexing (fastest HTTP/2)
if command -v curl >/dev/null 2>&1 && curl --parallel -h >/dev/null 2>&1; then
    args=""
    for file in ${FILES}; do
        args="${args} -o ${TARGET_DIR}/${file} ${BASE_URL}/${file}"
    done
    # shellcheck disable=SC2086
    curl -fsSL --parallel --parallel-immediate ${args}
elif command -v curl >/dev/null 2>&1; then
    # Concurrent background downloads via curl
    for file in ${FILES}; do
        curl -fsSL "${BASE_URL}/${file}" -o "${TARGET_DIR}/${file}" &
    done
    wait
elif command -v wget >/dev/null 2>&1; then
    # Concurrent background downloads via wget
    for file in ${FILES}; do
        wget -q -O "${TARGET_DIR}/${file}" "${BASE_URL}/${file}" &
    done
    wait
else
    echo "Error: Neither 'curl' nor 'wget' is installed on this system." >&2
    exit 1
fi

# Verify files exist and print final summary
echo ""
echo "=========================================="
echo " [✓] Download Completed in Parallel!"
echo " Files saved to: ${TARGET_DIR}"
for file in ${FILES}; do
    if [ -f "${TARGET_DIR}/${file}" ]; then
        size=$(wc -c < "${TARGET_DIR}/${file}" 2>/dev/null | tr -d ' ' || echo 'ok')
        echo "   - ${file} (${size} bytes)"
    else
        echo "   - ${file} (missing)"
    fi
done
echo "=========================================="
echo ""
