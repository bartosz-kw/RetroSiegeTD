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

ROOT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

BUILD_DIR="build/$MODE"

CONFIG=${MODE^}

cmake -S . -B "$BUILD_DIR" \
    -DCMAKE_BUILD_TYPE="$CONFIG" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build "$BUILD_DIR" --config "$CONFIG" --parallel

if [[ "$MODE" == "debug" ]]; then
    cp "$BUILD_DIR/compile_commands.json" ./compile_commands.json
fi

echo "Build completed: $MODE"
