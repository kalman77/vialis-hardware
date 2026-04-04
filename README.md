# Vialis Hardware

Vialis Hardware is an ESP8266-based firmware project for controlling LED behavior and device interaction over Wi-Fi, with local input support and a web-based control surface.

The firmware is built with PlatformIO and Arduino, and organizes networking, hardware drivers, and feature modules into a clean, modular structure.

## Features

- **ESP8266 firmware** targeting the `esp12e` board profile.
- **Wi-Fi connectivity** via `WifiManager`.
- **Web server control plane** for local/remote configuration and control.
- **Realtime integration hooks** through a websocket manager interface.
- **LED control subsystem** (`LedController`) for rendering and brightness changes.
- **Animation engine** (`AnimationManager`) for dynamic LED effects.
- **Brightness control** (`BrightnessController`) abstraction.
- **Joystick input handling** for local/manual interaction.
- **Structured logging** via a utility logger.
- **Cross-platform build workflow** through PlatformIO and a convenience `Makefile`.

## Tech Stack

- **Language:** C++
- **Framework:** Arduino
- **Platform:** PlatformIO
- **Target MCU/Board:** ESP8266 (`esp12e` environment)

### PlatformIO Dependencies

Defined in `platformio.ini`:

- `adafruit/Adafruit NeoPixel` (`^1.15.2`)
- `bblanchon/ArduinoJson` (`^7.4.2`)
- `gilmaimon/ArduinoWebsockets` (`^0.5.4`)

## Project Structure

- `src/` - Primary firmware entrypoint and application wiring (`src/main.cpp`).
- `core/` - Core services (e.g., Wi-Fi/web server/websocket managers).
- `hardware/` - Hardware-facing controllers and peripherals (e.g., LEDs, joystick).
- `features/` - End-user behavior modules (e.g., animations, brightness logic).
- `include/` - Shared headers and project-wide interfaces/config headers.
- `lib/` - Additional local libraries.
- `utils/` - Utility helpers such as logging.
- `scripts/` - Development/automation helper scripts.
- `test/` - Unit/integration test scaffolding.
- `docs/` - Additional project documentation.
- `platformio.ini` - PlatformIO environment, board, and dependency configuration.
- `Makefile` - Cross-platform wrapper targets for common development flows.

> Note: a root-level `main.cpp` is present, but `src/main.cpp` is the standard PlatformIO application entrypoint and appears to be the active one.

## Architecture Overview

At startup, the firmware initializes serial logging, connects to Wi-Fi, starts web services, and initializes hardware controllers. In the main loop, it continuously services network components and feature updates.

From `src/main.cpp`, the core runtime wiring is:

1. Initialize singleton/service objects:
   - `WifiManager`
   - `LedController`
   - `AnimationManager`
   - `BrightnessController`
   - `WebsocketManager`
   - `WebServerManager`
   - `Joystick`
2. `setup()` responsibilities:
   - Start serial logging
   - Connect Wi-Fi using `state.ssid` and `state.pswd`
   - Start web server and websocket manager
   - Initialize LEDs and joystick
3. `loop()` responsibilities:
   - Run Wi-Fi maintenance loop
   - Run web server loop
   - Poll joystick
   - Advance animations

This separation keeps transport/control logic (Wi-Fi, HTTP/WebSocket) distinct from hardware control and visual behavior.

## Getting Started

### Prerequisites

- [PlatformIO Core](https://platformio.org/install) (or PlatformIO IDE extension)
- Python environment compatible with PlatformIO
- ESP8266-compatible board (configured as `esp12e`)
- USB serial connection for flashing and monitoring

### Clone

```bash
git clone https://github.com/kalman77/vialis-hardware.git
cd vialis-hardware
```

### Build

Using PlatformIO directly:

```bash
pio run -e esp12e
```

Or via Makefile:

```bash
make build
```

### Upload Firmware

PlatformIO:

```bash
pio run -e esp12e --target upload
```

Makefile wrapper:

```bash
make upload
```

### Serial Monitor

```bash
pio device monitor -b 115200
```

or:

```bash
make monitor
```

### Run Tests

```bash
pio test -e esp12e
```

or:

```bash
make test
```

## Configuration

### PlatformIO Environment

The default environment is defined as:

```ini
[env:esp12e]
platform = espressif8266
board = esp12e
framework = arduino
```

### Runtime Configuration

The firmware references runtime credentials/state (`state.ssid`, `state.pswd`) from project headers/source (e.g., `state.hpp` / config layer). Ensure your local configuration is set before flashing.

If secrets are stored in source during development, prefer local-only files and avoid committing credentials.

## Makefile Targets

Available convenience targets include:

- `make build` / `make compile` - Build firmware
- `make upload` / `make flash` - Upload firmware
- `make monitor` - Open serial monitor
- `make clean` - Remove `.pio` artifacts
- `make test` - Run tests
- `make list` - List serial devices
- `make info` - Print environment details
- `make help` - Show target help

## Development Notes

- Keep feature logic in `features/`, and hardware abstractions in `hardware/`.
- Use `core/` for transport/runtime orchestration.
- Prefer interface-based integration (e.g., realtime abstractions) to keep modules decoupled.
- Maintain a single canonical firmware entrypoint in `src/main.cpp` to avoid drift.

## Troubleshooting

- **Build fails on missing libraries**
  - Run `pio pkg install` or rebuild to allow PlatformIO to resolve dependencies.
- **Upload port not found**
  - Run `pio device list` (or `make list`) and set an explicit upload port in `platformio.ini` if needed.
- **No serial output**
  - Verify monitor baud rate and board connection.
- **Wi-Fi not connecting**
  - Verify `state.ssid` / `state.pswd` values and network availability.

## Roadmap Ideas

- Add a dedicated configuration guide in `docs/` for credentials and environment setup.
- Document web server and websocket API endpoints.
- Add architecture diagrams for module interactions.
- Expand tests for feature and hardware abstraction layers.

## License

No license file is currently present in this repository. Add a `LICENSE` file if you intend to define distribution and usage terms.