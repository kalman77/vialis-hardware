# Vialis Hardware

This repository contains the hardware source code and configuration for **Vialis Hardware**. The project is structured as a PlatformIO C++ application.

## Repository Structure

- `core/` - Core application logic and system components.
- `docs/` - Project documentation.
- `include/` - Project header files.
- `lib/` - External or custom libraries.
- `scripts/` - Utility scripts.
- `src/` - Main source code files.
- `test/` - Unit tests and testing utilities.
- `utils/` - Helper utilities.
- `main.cpp` - Entry point for the application.
- `platformio.ini` - PlatformIO configuration file.
- `Makefile` - Make instructions for building/flashing.

## Getting Started

### Prerequisites
- [PlatformIO](https://platformio.org/) Core (CLI) or IDE extension.

### Building the Project
To build the project, run:
```bash
pio run
```
Alternatively, you can use the provided `Makefile` (if implemented for these targets).

### Uploading to the Board
To upload the firmware to your hardware device:
```bash
pio run --target upload
```