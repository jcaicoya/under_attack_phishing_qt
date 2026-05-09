# CLAUDE.md - Cybershow Skeleton

Working context for Claude, Codex, Gemini, or another coding agent modifying this skeleton or using it as the base for a new Cybershow Qt app.

Do not duplicate the README here. The README is the developer handoff for building, running, launch modes, and packaging. This file is for implementation rules and project intent.

## Purpose

This is the minimal reusable Qt Widgets runtime shell for Cybershow apps.

It should stay generic:

- no app-specific network logic
- no Setup screen
- no demo event simulation unless a copied app adds it
- no production content beyond placeholder screens
- no dependencies on sibling projects

## Current Contract

- Executable target: `skeleton`
- Deployed executable: `skeleton.exe`
- Deploy zip prefix: `bajo-ataque-phising`
- No arguments mean live mode.
- Supported modes are only `--live` and `--demo`.
- Runtime screens are operator-controlled.
- Bottom navigation starts hidden and toggles with `F9`.
- Mode badge starts hidden and toggles with `F10`.
- Screen navigation uses number keys and left/right arrows.
- Setup/configure flow is intentionally absent.

## Source Map

- `src/main.cpp`: launch parsing, app setup, screen-aware window placement, stdout status lifecycle.
- `src/SkeletonWindow.*`: two-screen runtime shell, keyboard navigation, bottom nav, mode badge.
- `src/ScreenPage.*`: reusable page chrome.
- `src/cybershow/common/CyberAppMode.*`: launch mode parser.
- `src/cybershow/common/CyberOperationalLog.*`: operational log writer.
- `src/cybershow/common/CyberOrchestratorProtocol.h`: `CYBERSHOW_*` stdout lines.
- `src/cybershow/ui/*`: theme, background, and navigation widgets.

## Rules For Future Apps

When copying this project to start a new app:

1. Prefer `clone-skeleton.ps1 <new-directory-path>` for the initial copy.
2. Rename the CMake project, target, executable, app name, log file, and zip prefix.
3. Keep the shared launch contract unless the Cybershow family standard changes.
4. Replace placeholder pages in `SkeletonWindow::buildUi()` or split them into app-specific screen builders.
5. Keep read-only display widgets `Qt::NoFocus`.
6. Keep `F9`, `F10`, number keys, and arrows consistent across apps.
7. Keep screen-aware startup sizing and shared theme scaling.
8. Keep stdout protocol lines stable for orchestration.
9. Keep operator-facing text in Spanish for real show apps unless a specific app requires otherwise.

## Things Not To Reintroduce

- Setup screen.
- `--configure`.
- automatic demo screen cycling.
- letter-based navigation shortcuts.
- focusable read-only dashboards.
- app-specific standards markdown copied from older refactors.

## Validation Expectations

The user is responsible for compiling, running, packaging, and deployment tests.

For code changes, make the change and stop with a clear note that it is ready for the user's build/test pass. Do not run the app unless explicitly asked.
