#!/usr/bin/env bash
set -euo pipefail

MODE="${1:-debug}"

case "$MODE" in
debug | release) ;;
*)
    echo "Usage: $0 [debug|release]"
    exit 1
    ;;
esac

ROOT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(dirname "$ROOT_DIR")"
cd "$ROOT_DIR"

BUILD_DIR="build/$MODE"

CONFIG=${MODE^}

GAME="RetroSiegeTD"

bash scripts/build.sh "$MODE"

for EXE in \
    "$BUILD_DIR/$GAME" \
    "$BUILD_DIR/$GAME.exe" \
    "$BUILD_DIR/$CONFIG/$GAME" \
    "$BUILD_DIR/$CONFIG/$GAME.exe"; do
    if [[ -f "$EXE" ]]; then
        exec "$EXE" "${@:2}"
    fi
done

echo "Error: executable not found."
exit 1
