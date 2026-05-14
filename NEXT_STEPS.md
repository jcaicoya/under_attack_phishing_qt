# NEXT_STEPS — Phising-Qt

## Done
- [x] Cloned from shared Qt Widgets skeleton
- [x] Renamed from `phising` to `phising-qt` (directory, `.idea/.name`)
- [x] `CLAUDE.md` updated and moved to `.claude/CLAUDE.md`
- [x] `NEXT_STEPS.md` created

## Pending

1. Add WebSocket server (port 8769, accept connection from `phising-android`)
2. Build screen 1 — Tipo (3 message type options: Banco / Multa de tráfico / Correos)
3. Build screen 2 — Detalle técnico (3 options depending on chosen type)
4. Build screen 3 — Amenaza (3 options depending on chosen type)
5. Build screen 4 — Urgencia (3 options depending on chosen type)
6. Build screen 5 — Climax (triggered by `link_tapped` signal, not in nav)
7. Wire protocol: on `link_tapped` received → navigate to screen 5
8. End-to-end test with `phising-android`
9. Add to Orchestrator (stdout protocol, `--configure` / `--design` / `--show` modes)
