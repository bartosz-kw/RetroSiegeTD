# RetroSiegeTD

RetroSiegeTD is a retro-styled, simplistic tower defense game which includes:
4 unique towers,
20 waves of enemies,
pixel graphics and a basic soundtrack.

## Dependencies

| Dependency | Purpose | Required |
| --- | --- | --- |
| [C++20-compatible compiler](https://en.cppreference.com/w/cpp/compiler_support) | Compiles the game | Yes |
| [CMake 4.2 or newer](https://cmake.org/) | Generates the build system (`CMakeLists.txt` specifies `cmake_minimum_required(VERSION 4.2)`) | Yes |
| [raylib](https://www.raylib.com/) | Windowing, input, rendering, textures, and audio | Yes |
| Bash | Runs the provided build and launch scripts | For the scripts |

### raylib setup

The project links against `raylib` in `CMakeLists.txt`:

```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
```

The project does not fetch or build raylib itself. Make raylib available to your compiler and linker (including its headers and library) before configuring the project. The exact installation command depends on your operating system and package manager.

## Build and run

From the repository root:

```bash
# Debug build
bash scripts/build.sh debug

# Release build
bash scripts/build.sh release

# Build and launch the debug executable
bash scripts/run.sh debug

# Build and launch the release executable
bash scripts/run.sh release
```

The scripts configure CMake in `build/debug` or `build/release` and build the `RetroSiegeTD` executable.
The run script builds the selected configuration before launching it.

Run the executable from the repository root.
Resource paths are relative to the working directory and currently use paths under `src/resources/`.

### Controls

| Input | Action |
| --- | --- |
| Left mouse button | Select/click GUI elements; select a map tile and place the currently selected tower |
| Right mouse button | Cancel the currently selected tower-placement mode |
| `1` | Select Ninja tower for placement |
| `2` | Select Knight tower for placement |
| `3` | Select Market tower for placement |
| `4` | Select Sniper tower for placement |
| `P` | Return to the menu while a game is running |
| `F11` | Toggle fullscreen |

### Debug-only inputs

These shortcuts are compiled out of Release builds:

| Input | Action |
| --- | --- |
| `F1` | Start the game |
| `M` | Add 3,000 money |
| `F3` | Toggle the debug view |
| `F4` | Spawn a Summoner enemy |
| `F5` | Spawn a Skeleton King enemy |

## Project layout

```text
.
├── CMakeLists.txt
├── scripts/
│   ├── build.sh
│   └── run.sh
├── src/
│   ├── core/          # Main game lifecycle and update/draw loop
│   ├── context/       # Viewport and coordinate conversion
│   ├── enums/         # Game and gameplay enumerations
│   ├── gui/           # Menus, HUD, tower panel, and end-game UI
│   ├── managers/      # Game systems (enemies, towers, waves, GUI, audio, etc.)
│   ├── namespaces/    # Shared game data, settings, sprites, and loading
│   ├── resources/     # Maps, sprites, fonts, and audio
│   ├── structs/       # Gameplay and UI data structures
│   ├── utility/       # Math, color, and debug helpers
│   └── main.cpp
└── licences/          # Third-party asset/library licences
```

The game loop and high-level initialization are in `src/core/game.cpp`. Gameplay systems are separated into managers under `src/managers/`, while GUI components live under `src/gui/`. Map, sprite, font, and audio assets are stored in `src/resources/`.

## Code style

The repository includes a `.clang-format` configuration. Use `clang-format` with that file when formatting C++ code.

Format a file with:

```bash
clang-format -i path/to/file.cpp path/to/file.hpp
```

Follow the existing naming and organization conventions when adding code: keep declarations in headers, implementations in `.cpp` files, and place new systems in the corresponding `src/` subdirectory.

## Assets and licences

The `src/resources/` directory contains the game's maps, sprites, fonts, and OGG audio files. Third-party licence files are collected in `licences/`. Preserve the relevant licence and attribution files when redistributing assets or removing vendored libraries.
