# RUNBOOK - Phishing Qt

## Arranque

Modo runtime por defecto:

```powershell
under_attack_phishing_qt.exe
```

Variantes de arranque:

```powershell
under_attack_phishing_qt.exe --live
under_attack_phishing_qt.exe --demo
under_attack_phishing_qt.exe --fullscreen
under_attack_phishing_qt.exe --windowed
under_attack_phishing_qt.exe --screen 1
under_attack_phishing_qt.exe --debug
```

## Navegación

- `1`: pantalla 1
- `2`: pantalla 2
- `Left Arrow`: pantalla anterior
- `Right Arrow`: pantalla siguiente
- `F9`: mostrar u ocultar la barra inferior de navegación
- `F10`: mostrar u ocultar el indicador `DEMO` / `LIVE`

## Manejo durante el show

- La barra inferior empieza oculta.
- El indicador `DEMO` / `LIVE` empieza oculto.
- La navegación está pensada para teclado.
- No hay pantalla de setup.
- Si se ejecuta sin argumentos, entra en modo runtime por defecto.

## Flujo operativo previsto

1. Elegir tipo de mensaje.
2. Elegir detalle técnico.
3. Elegir amenaza.
4. Elegir urgencia.
5. Enviar el mensaje construido a Android.
6. Esperar a que Android informe `link_tapped`.
7. Mostrar la pantalla de clímax.

## Conectividad con Android

- La app actúa como servidor WebSocket.
- Puerto: `8769`.
- `phishing_android` conecta como cliente.
- La integración esperada con Orchestrator incluye ADB reverse y lanzamiento remoto de la app Android.

## Deploy

### Requisitos

- Qt 6.7.3 para MSVC 2022 64-bit
- CMake 3.28+
- Visual Studio 2022 C++ toolchain
- Visual C++ Redistributable en la máquina destino

### Build manual

```powershell
cmake -S . -B build\msvc2022 -DCMAKE_BUILD_TYPE=Release
cmake --build build\msvc2022 --config Release
```

### Packaging

```powershell
.\package-release.ps1
.\package-release.ps1 -Force
```

- genera `dist\bajo-ataque-phishing-vNN.zip`
- el artefacto desplegable es el zip bajo `dist\`

## Consideraciones operativas

- El flujo final de escena todavía está en construcción.
- La pantalla de clímax no debe entrar en la navegación normal.
- La app debe mantenerse alineada con `phishing_android` en protocolo y tiempos de show.
