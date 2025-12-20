# ==============================================
# esp_led_controller Makefile (Cross-Platform)
# ==============================================

# === Project configuration ===
BOARD       = esp8266:esp8266:nodemcuv2
BAUD        = 921600
BUILD_DIR   = build
PROJECT     = esp_led_controller

# === Directories ===
SRC_DIRS    = src src/core src/hardware src/features src/utils
INCLUDE_DIRS = include $(SRC_DIRS)
SRC_FILES   = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
INCLUDE_FLAGS = $(foreach dir,$(INCLUDE_DIRS),-I$(dir))

# === Tool configuration ===
ARDUINO_CLI = arduino-cli

# === OS detection ===
ifeq ($(OS),Windows_NT)
  RM = del /Q
  MKDIR = mkdir
  DETECT_PORT = $(shell powershell -Command "$$p=(Get-WmiObject Win32_SerialPort | Where-Object {$$_ -match 'USB'} | Select-Object -ExpandProperty DeviceID); Write-Host $$p")
  PORT ?= $(DETECT_PORT)
  SHELL := powershell.exe
  .SHELLFLAGS := -NoProfile -Command
else
  RM = rm -rf
  MKDIR = mkdir -p
  DETECT_PORT = $(shell ls /dev/ttyUSB* 2>/dev/null | head -n 1)
  PORT ?= $(DETECT_PORT)
endif

# === Targets ===
all: compile

compile:
	@echo "🔧 Compiling firmware for $(BOARD)..."
	$(ARDUINO_CLI) compile --fqbn $(BOARD) \
	--build-path $(BUILD_DIR) . \
	--build-property build.extra_flags="$(INCLUDE_FLAGS)"
	@echo "✅ Build complete."

upload:
	@echo "🚀 Uploading to board on port $(PORT)..."
	$(ARDUINO_CLI) upload -p $(PORT) --fqbn $(BOARD) --input-dir $(BUILD_DIR) --verify --upload-speed $(BAUD)
	@echo "✅ Upload complete."

monitor:
	@echo "🖥️  Opening serial monitor on $(PORT) @$(BAUD)..."
	$(ARDUINO_CLI) monitor -p $(PORT) -c baudrate=$(BAUD)

clean:
	@echo "🧹 Cleaning build artifacts..."
	$(RM) $(BUILD_DIR)
	@echo "✅ Cleaned."

list:
	@echo "🔍 Available boards:"
	$(ARDUINO_CLI) board list

help:
	@echo ""
	@echo "=== esp_led_controller Build System ==="
	@echo ""
	@echo "Targets:"
	@echo "  make compile    → Build firmware"
	@echo "  make upload     → Upload firmware to board"
	@echo "  make monitor    → Open serial monitor"
	@echo "  make clean      → Remove build directory"
	@echo "  make list       → Show available serial ports"
	@echo "  make help       → Show this help message"
	@echo ""
