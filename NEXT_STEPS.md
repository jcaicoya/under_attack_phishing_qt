# NEXT_STEPS — Phishing-Qt

## Done
- [x] Cloned from shared Qt Widgets skeleton
- [x] Renamed from `phising` to `phishing_qt` (directory, `.idea/.name`)
- [x] `CLAUDE.md` updated and moved to `.claude/CLAUDE.md`
- [x] `NEXT_STEPS.md` created
- [x] Add WebSocket server (port 8769) + UDP beacon (port 8770)
- [x] End-to-end connection test with `phishing_android` — successful

## Pending

1. Build screen 1 — Tipo (3 message type options: Banco / Multa de tráfico / Correos)
2. Build screen 2 — Detalle técnico (3 options depending on chosen type)
3. Build screen 3 — Amenaza (3 options depending on chosen type)
4. Build screen 4 — Urgencia (3 options depending on chosen type)
5. Build screen 5 — Climax (triggered by `link_tapped` signal, not in nav)
6. Wire protocol: on `link_tapped` received → navigate to screen 5
7. Add to Orchestrator (stdout protocol, `--configure` / `--design` / `--show` modes)
