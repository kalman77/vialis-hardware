# Vialis Hardware

ESP8266 firmware for Wi-Fi-connected LED control with local joystick input, web controls, and modular animation/brightness features.

---

## Quick Start

```bash
git clone https://github.com/kalman77/vialis-hardware.git
cd vialis-hardware
pio run -e esp12e
pio run -e esp12e --target upload
pio device monitor -b 115200
```

Or with Makefile:

```bash
make build
make upload
make monitor
```

---

## What This Project Does

Vialis Hardware runs on an ESP8266 (`esp12e`) and provides:

- LED rendering and effects
- Brightness control logic
- Joystick-based local interaction
- Wi-Fi connectivity
- HTTP web server control surface
- Realtime/websocket integration hooks
- Structured runtime logging

The codebase is organized to separate:
- **core runtime/networking**
- **hardware abstraction**
- **feature behavior**

---

## Features

- **ESP8266 firmware** targeting PlatformIO `env:esp12e`
- **Wi-Fi management** (`WifiManager`)
- **Web server control layer** (`WebServerManager`)
- **Realtime integration support** (`WebsocketManager`, realtime interface)
- **LED control subsystem** (`LedController`)
- **Animation engine** (`AnimationManager`)
- **Brightness controller** (`BrightnessController`)
- **Joystick input** (`Joystick`)
- **Cross-platform local tooling** via `Makefile`

---

## Tech Stack

- **Language:** C++
- **Framework:** Arduino
- **Build System:** PlatformIO
- **MCU/Board:** ESP8266 (`esp12e`)

### PlatformIO Dependencies

From `platformio.ini`:

- `adafruit/Adafruit NeoPixel@^1.15.2`
- `bblanchon/ArduinoJson@^7.4.2`
- `gilmaimon/ArduinoWebsockets@^0.5.4`

---

## Repository Layout

- `src/` - Main firmware entrypoint and runtime wiring (`src/main.cpp`)
- `core/` - Wi-Fi, web server, websocket, and orchestration services
- `hardware/` - Device-facing modules (LEDs, joystick, etc.)
- `features/` - Animations, brightness, and behavior logic
- `include/` - Shared headers, interfaces, configuration headers
- `lib/` - Local libraries
- `utils/` - Utility helpers (e.g., logger)
- `scripts/` - Dev/automation scripts
- `test/` - Test scaffolding
- `docs/` - Project documentation
- `platformio.ini` - Build target + dependency config
- `Makefile` - Convenience targets for build/upload/monitor/test

> Note: a root `main.cpp` exists, but `src/main.cpp` is the standard PlatformIO entrypoint and appears to be the active one.

---

## Architecture Overview

From `src/main.cpp`, startup and runtime flow:

1. Construct managers/controllers:
   - `WifiManager`
   - `LedController`
   - `AnimationManager`
   - `BrightnessController`
   - `WebsocketManager`
   - `WebServerManager`
   - `Joystick`
2. `setup()`:
   - start serial logging
   - connect Wi-Fi using `state.ssid` / `state.pswd`
   - start web server and websocket manager
   - initialize LED + joystick hardware
3. `loop()`:
   - service Wi-Fi loop
   - service web server loop
   - poll joystick
   - advance animations

This keeps networking/control concerns cleanly separated from hardware and feature logic.

---

## Hardware / Wiring

> Update this section with your exact board and pin assignments.

### Supported Target

- ESP8266 board profile: `esp12e`

### Suggested Pin Mapping Template

| Signal / Peripheral | GPIO Pin | Notes |
|---|---:|---|
| LED Data | `TODO` | NeoPixel/WS2812 data line |
| Joystick X | `TODO` | Analog/digital input |
| Joystick Y | `TODO` | Analog/digital input |
| Joystick Button | `TODO` | Optional pull-up/down |
| Status LED (optional) | `TODO` | Debug/status indicator |

### Power & Safety Notes

- Use a stable power source sized for LED current draw.
- Ensure **common ground** between ESP8266 and LED strip/power supply.
- Consider a resistor on LED data line and bulk capacitor on LED power rails for stability.
- Do not power large LED loads directly from the ESP8266 regulator.

---

## Build, Flash, Monitor

### PlatformIO

Build:

```bash
pio run -e esp12e
```

Upload:

```bash
pio run -e esp12e --target upload
```

Test:

```bash
pio test -e esp12e
```

Monitor:

```bash
pio device monitor -b 115200
```

### Makefile Shortcuts

- `make build` / `make compile` - Build firmware
- `make upload` / `make flash` - Upload firmware
- `make monitor` - Open serial monitor
- `make clean` - Remove `.pio` artifacts
- `make test` - Run tests
- `make list` - List serial devices
- `make info` - Show environment/build info
- `make help` - Show all targets

---

## Configuration

### PlatformIO Environment

```ini
[env:esp12e]
platform = espressif8266
board = esp12e
framework = arduino
```

### Runtime Credentials / State

Wi-Fi credentials are read from the project state/config layer (`state.ssid`, `state.pswd` references in `main.cpp`).

Recommended practice:
- keep secrets in local-only config
- never commit real credentials
- document local setup in `docs/` (if not already)

---

## Web/API Notes

The firmware initializes web and realtime components (`WebServerManager`, `WebsocketManager`), but endpoint-level API documentation is not yet centralized.

Recommended next step:
- add `docs/api.md` with HTTP routes, websocket events, and payload schema examples.

---

## Contributing

1. Create a feature branch
2. Keep changes scoped by module (`core/`, `hardware/`, `features/`)
3. Build and run tests locally
4. Open a PR with:
   - summary of behavior change
   - test evidence
   - hardware validation notes (if relevant)

### Local Quality Checklist

- [ ] Builds successfully with `pio run -e esp12e`
- [ ] Upload succeeds on target board
- [ ] Serial logs are readable and useful
- [ ] No credentials/secrets committed
- [ ] README/docs updated when behavior changes

---

## Troubleshooting

- **Missing dependencies during build**
  - Re-run build; PlatformIO should resolve deps automatically.
- **Board not detected**
  - Use `pio device list` / `make list`, then set explicit upload port.
- **No serial output**
  - Verify monitor baud and USB serial port.
- **Wi-Fi connection failure**
  - Verify SSID/password config and signal/network availability.

---

## Roadmap

- Add complete wiring documentation with real pin assignments
- Document HTTP + websocket APIs
- Add architecture diagram in `docs/`
- Expand automated tests for feature modules and hardware abstractions
- Add CI for build/test on push

---

## License

No `LICENSE` file is currently present. Add one to define usage/distribution terms.
