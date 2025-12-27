# ==============================================
# Vialis Hardware Makefile (Cross-Platform)
# ==============================================

# === Project configuration ===
PROJECT     = vialis-hardware
BAUD        = 115200
ENV         = esp12e

# === Tool configuration ===
PIO         = pio

# === OS detection ===
ifeq ($(OS),Windows_NT)
  RM = del /Q /S
  MKDIR = mkdir
  DETECT_PORT = $(shell powershell -Command "$$p=(Get-WmiObject Win32_SerialPort | Where-Object {$$_ -match 'USB'} | Select-Object -ExpandProperty DeviceID); Write-Host $$p")
  PORT ?= $(DETECT_PORT)
  SHELL := powershell.exe
  .SHELLFLAGS := -NoProfile -Command
else
  RM = rm -rf
  MKDIR = mkdir -p
  DETECT_PORT = $(shell ls /dev/ttyUSB* /dev/ttyACM* 2>/dev/null | head -n 1)
  PORT ?= $(DETECT_PORT)
endif

# === Targets ===
.PHONY: all build compile upload flash monitor clean test list info help

all: build

build: compile

compile:
	@echo "🔧 Building firmware for $(PROJECT)..."
	$(PIO) run -e $(ENV)
	@echo "✅ Build complete."

upload: flash

flash:
	@echo "🚀 Uploading firmware to ESP8266..."
	$(PIO) run -e $(ENV) --target upload
	@echo "✅ Upload complete."

monitor:
	@echo "🖥️  Opening serial monitor..."
	@echo "Note: Use Ctrl+C to exit"
	@echo "Trying: screen $(PORT) $(BAUD)"
	@screen $(PORT) $(BAUD) || \
	(echo "❌ screen not available. Try: minicom -D $(PORT) -b $(BAUD)" && exit 1)

clean:
	@echo "🧹 Cleaning build artifacts..."
	$(RM) .pio
	@echo "✅ Cleaned."

test:
	@echo "🧪 Running tests..."
	$(PIO) test -e $(ENV)

list:
	@echo "🔍 Available serial devices:"
	$(PIO) device list

info:
	@echo ""
	@echo "=== $(PROJECT) Build Information ==="
	@echo "Environment:     $(ENV)"
	@echo "Platform:        espressif8266"
	@echo "Board:           esp12e (ESP8266)"
	@echo "Framework:       Arduino"
	@echo "Baud Rate:       $(BAUD)"
	@echo "Detected Port:   $(PORT)"
	@echo ""

help:
	@echo ""
	@echo "=== $(PROJECT) Build System ==="
	@echo ""
	@echo "Targets:"
	@echo "  make build      → Build firmware (alias: compile)"
	@echo "  make upload     → Upload firmware to board (alias: flash)"
	@echo "  make monitor    → Open serial monitor (requires screen)"
	@echo "  make clean      → Remove build directory (.pio)"
	@echo "  make test       → Run unit tests"
	@echo "  make list       → Show available serial devices"
	@echo "  make info       → Show build configuration"
	@echo "  make help       → Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make build && make upload  → Build and upload"
	@echo "  make flash                 → Quick upload"
	@echo ""
