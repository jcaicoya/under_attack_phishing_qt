# CLAUDE.md — Phising-Qt

Working context for Claude or another coding agent modifying the Phising-Qt Cybershow app.

## Purpose

Operator control panel for the phishing scene of the Bajo Ataque cybershow. The presenter uses this app to guide the audience through building a convincing phishing SMS step by step. Each step sends the evolving message to the Android companion app (`phising-android`) running on the confederate's tablet.

No setup screen. No dependencies on sibling projects.

## Show Narrative

The phishing scene is the last attack of the show, after the password scene. The premise: every previous attack failed, so the hackers try to trick the target directly. The audience participates by choosing options that make a fake SMS progressively more convincing. At the end, the confederate taps the link — the attack succeeds, and the climax screen fires.

## Screen Spec

### Screens 1–4 (builder) — identical layout, bottom nav tabs

| # | Tab name | What the audience adds |
|---|---|---|
| 1 | Tipo | Message category: Banco / Multa de tráfico / Correos |
| 2 | Detalle | Technical detail (3 options, depend on type chosen in screen 1) |
| 3 | Amenaza | Threat (3 options, depend on type) |
| 4 | Urgencia | Time pressure (3 options, depend on type) |

Each screen shows:
- The active message type (chosen in screen 1, carried across all screens)
- Three selectable options for that step
- The built message panel — accumulates layer by layer as options are chosen
- A **Enviar** button — sends the current message to `phising-android` via WebSocket

### Screen 5 (climax) — triggered, not in nav

- Appears automatically when `phising-android` reports the link was tapped.
- Not reachable via normal navigation.
- Spectacular, theatrical. Hints at the consequence — does not show a fake login.
- This is the show's closing moment before the final video.

## Message Content

Three message types, each with three variants per builder layer:

| Layer | Banco | Multa de tráfico | Correos |
|---|---|---|---|
| Detalle | Account number, movement alert, card blocked | Reference code, fine amount, vehicle plate | Tracking number, delivery attempt, customs hold |
| Amenaza | Account suspended, fraud detected, card cancelled | Penalty doubles, legal proceedings, licence points | Package returned, storage fee, customs seizure |
| Urgencia | Within 24h, before midnight, in the next hour | 48h deadline, today only, immediate action | 3 days to collect, expires tomorrow, last notice |

*(Exact Spanish wording to be defined during implementation.)*

## Connection Architecture

- WebSocket **server** — listens on port **8769**.
- `phising-android` connects via ADB reverse tunnel (`adb reverse tcp:8769 tcp:8769`).
- Orchestrator manages tunnel setup and ADB app launch before the show.

## Qt ↔ Android Protocol

| Direction | Event | Message |
|---|---|---|
| Qt → Android | Send phishing message | `{"type": "message", "body": "...", "link": "..."}` |
| Android → Qt | Link tapped | `{"type": "link_tapped"}` |

On receiving `link_tapped`, Qt navigates to screen 5.

## Launch Modes

This app has no setup screen, so `--configure` falls through to runtime mode.

| Arg | Behaviour |
|---|---|
| `--design` | Starts at screen 1 |
| `--show` | Same as `--design`, used for real performance |
| `--configure` | Same as `--design` (no setup to show) |
| *(none)* | Same as `--design` |

## Build Contract

- Executable target: `phising`
- Deployed executable: `phising.exe`
- Deploy zip prefix: `bajo-ataque-phising`

## Source Map

- `src/main.cpp` — launch parsing, app setup, screen-aware placement, stdout lifecycle.
- `src/PhisingWindow.*` — main window, screen navigation, bottom nav, WebSocket server, screen 5 trigger.
- `src/ScreenPage.*` — reusable page chrome.
- `src/cybershow/common/CyberAppMode.*` — launch mode parser.
- `src/cybershow/common/CyberOperationalLog.*` — operational log writer.
- `src/cybershow/common/CyberOrchestratorProtocol.h` — `CYBERSHOW_*` stdout lines.
- `src/cybershow/ui/*` — theme, background, and navigation widgets.

## Implementation Rules

1. Screens 1–4 must be visually identical in layout — only content varies.
2. The built message panel always shows the full accumulated message, updated after each option is selected.
3. Selecting an option in screen 1 resets screens 2–4 (new type → new options).
4. Screen 5 is only reachable via the `link_tapped` WebSocket event — never via nav.
5. Keep `F9` (bottom nav toggle), `F10` (mode badge), number keys, and arrows consistent.
6. Keep read-only display widgets `Qt::NoFocus`.
7. Keep stdout protocol lines stable for Orchestrator.
8. All operator-facing text in Spanish.

## Things Not To Reintroduce

- Setup screen or `--configure` UI.
- Automatic demo screen cycling.
- Letter-based navigation shortcuts.
- Focusable read-only dashboards.

## Current State

Cloned from the shared Qt Widgets skeleton. Placeholder screens in `PhisingWindow`. No WebSocket server, no show logic implemented yet.

## Validation Expectations

The user is responsible for compiling, running, packaging, and deployment tests.
Stop after each code change with a note that it is ready for the user's build/test pass.
Do not run the app unless explicitly asked.
