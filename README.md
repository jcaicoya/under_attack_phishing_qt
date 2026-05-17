# Phishing Qt

Consola de operador para la escena de phishing del show **Bajo Ataque**. La persona presentadora guía al público en la construcción progresiva de un SMS de phishing convincente y envía cada versión a `phishing_android`.

## Qué es

Esta app forma pareja con `phishing_android`. Su papel es construir el mensaje de phishing por capas, enviarlo al dispositivo Android y reaccionar cuando el enlace falso es pulsado.

## Flujo funcional

1. El operador elige el tipo de mensaje.
2. Define detalle técnico.
3. Define amenaza.
4. Define urgencia.
5. Envía la versión construida del mensaje a Android.
6. Si Android informa `link_tapped`, la app pasa a la pantalla de clímax.

## Pantallas

### Pantallas 1–4: builder

| # | Pantalla | Función |
|---|---|---|
| 1 | Tipo | Banco / Multa de tráfico / Correos |
| 2 | Detalle | detalle técnico del mensaje |
| 3 | Amenaza | consecuencia o amenaza |
| 4 | Urgencia | presión temporal |

Todas comparten la misma estructura:

- tipo activo
- tres opciones seleccionables
- panel del mensaje construido
- botón de envío

### Pantalla 5: clímax

- se activa al recibir `link_tapped`
- no debe estar en la navegación normal
- momento final y teatral de la escena

## Arquitectura y comunicación

- Aplicación Qt para Windows.
- Servidor WebSocket en `8769`.
- `phishing_android` actúa como cliente.
- Se apoya en ADB reverse y en integración futura con Orchestrator.

Protocolo:

| Dirección | Evento | Mensaje |
|---|---|---|
| Qt -> Android | enviar mensaje | `{"type": "message", "body": "...", "link": "..."}` |
| Android -> Qt | enlace pulsado | `{"type": "link_tapped"}` |

## Reglas funcionales

- Las pantallas 1–4 deben mantener un layout visual consistente.
- El panel del mensaje debe mostrar siempre el mensaje acumulado.
- Si cambia el tipo, se deben resetear las capas posteriores.
- La pantalla 5 solo se alcanza por evento de protocolo, no por navegación directa.

## Tecnología

| Capa | Tecnología |
|---|---|
| Plataforma | Windows |
| Framework | Qt Widgets |
| Lenguaje | C++ |
| Comunicación | WebSocket + UDP beacon |
| Build | CMake |

## Estado actual

- Proyecto clonado desde el skeleton compartido.
- Renombrado a `phishing_qt`.
- Servidor WebSocket en `8769` añadido.
- Beacon UDP en `8770` añadido.
- Conexión end-to-end con `phishing_android` validada.
- La UI builder y la pantalla de clímax siguen pendientes de implementación completa.
