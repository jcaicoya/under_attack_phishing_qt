# CLAUDE.md — Phishing Qt

Instrucciones de trabajo específicas para este subproyecto.

## Lectura obligatoria al empezar

Antes de trabajar aquí, lee y aplica también:

- `README.md`
- `RUNBOOK.md`
- `NEXT_STEPS.md`

## Qué contiene cada archivo

- `README.md`: qué es la app, flujo, pantallas, arquitectura y estado.
- `RUNBOOK.md`: arranque, operación, navegación, conectividad y deploy.
- `NEXT_STEPS.md`: pasos hechos y pendientes.
- `.claude/CLAUDE.md`: reglas de trabajo específicas de este directorio.

No dupliques información entre estos archivos. Cada dato debe vivir en un único sitio.

## Forma de trabajar en este directorio

- El usuario se encarga de compilar, probar, empaquetar, hacer commits y hacer push.
- Si cambias flujo escénico, protocolo, contrato de arranque o backlog, actualiza el archivo correspondiente.
- Si cambias el protocolo Qt/Android, mantén sincronizados `phishing_qt` y `phishing_android`.
- Tras cada commit, `README.md`, `RUNBOOK.md` y `NEXT_STEPS.md` deben seguir reflejando el estado real del proyecto.

## Reglas funcionales de esta app

- Las pantallas 1–4 deben compartir layout consistente.
- La pantalla 5 no debe ser navegable por tabs o atajos normales.
- El mensaje construido debe verse acumulado y actualizado en cada paso.
- Todo el texto visible al operador debe estar en español.

## Alcance de este archivo

Este archivo no debe repetir documentación general de la app ni instrucciones operativas de uso; eso pertenece a `README.md` o `RUNBOOK.md`.
