# Cybershow Skeleton

Reusable Qt Widgets skeleton for new Cybershow applications.

This project intentionally contains no app-specific functionality. It provides the common runtime shell:

- two placeholder screens
- shared Cybershow look and feel
- bottom navigation, hidden by default
- `F9` toggles the bottom navigation row
- `F10` toggles the `DEMO` / `LIVE` badge
- number keys and arrows navigate between screens
- no Setup screen

## Launch Modes

No arguments means live mode.

```powershell
skeleton.exe
skeleton.exe --live
skeleton.exe --demo
skeleton.exe --fullscreen
skeleton.exe --windowed
skeleton.exe --screen 1
```

Supported launch modes:

- `--live`
- `--demo`

Supported display flags:

- `--fullscreen`
- `--windowed`
- `--screen <n>`
- `--debug`

## Requirements

- Qt 6.7.3 for MSVC 2022 64-bit
- CMake 3.28+
- Visual Studio 2022 C++ toolchain
- Windows target machine with the Visual C++ Redistributable

`CMakeLists.txt` currently points to:

```cmake
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.3/msvc2022_64")
```

Change that path if Qt is installed somewhere else.

## Build And Run

Configure and build manually:

```powershell
cmake -S . -B build\msvc2022 -DCMAKE_BUILD_TYPE=Release
cmake --build build\msvc2022 --config Release
```

Run the built executable:

```powershell
.\build\msvc2022\Release\skeleton.exe
.\build\msvc2022\Release\skeleton.exe --demo --windowed
.\build\msvc2022\Release\skeleton.exe --live --fullscreen
```

During runtime:

- `1` and `2` switch screens
- `Left Arrow` and `Right Arrow` move between screens
- `F9` shows or hides the bottom navigation row
- `F10` shows or hides the `DEMO` / `LIVE` badge

## Template Rules

When copying this project to create a new app:

1. Clone the skeleton into a new directory:

```powershell
.\clone-skeleton.ps1 ..\new-app-name
```

The target path may be relative or absolute. It must be provided, must not already exist, and must be outside this skeleton directory. The script copies source/template files and excludes local IDE, build, staging, dist, log, and git metadata.

2. Rename the project and executable in `CMakeLists.txt`.
3. Replace the two placeholder screens in `SkeletonWindow.cpp`.
4. Keep the launch contract unless the whole Cybershow standard changes.
5. Keep `F9`, `F10`, number keys, and arrow navigation consistent with the other apps.
6. Keep read-only display widgets non-focusable so keyboard navigation remains reliable.

## Release Packaging

Use the same deploy flow as the other Cybershow apps:

```powershell
.\package-release.ps1
.\package-release.ps1 -Force
```

The script builds Release, stages the executable and required Qt runtime files, creates `dist\bajo-ataque-phising-vNN.zip`, updates `releases.json`, and creates a matching git tag when the project is inside a git repository.

The deployable artifact is the zip under `dist\`. It contains `skeleton.exe`, required Qt DLLs, the Windows platform plugin, this README, and `RUNBOOK.md`.
