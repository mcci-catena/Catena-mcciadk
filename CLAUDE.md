# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Catena-mcciadk is the MCCI Arduino Development Kit (ADK), a port of the MCCI XDK portability toolkit for Arduino and deeply-embedded environments. It provides portable C/C++ utility macros and functions. Current version is in `VERSION.txt`.

## Build and Test

This is an Arduino library -- there is no standalone build system. It builds via the Arduino IDE/CLI as part of projects that depend on it.

**CI (GitHub Actions)** compiles header-inclusion tests against three targets:
- MCCI SAMD (Catena 4450)
- MCCI STM32L0 (Catena 4551)
- ESP32 (Heltec WiFi LoRa 32)

To replicate CI locally with `arduino-cli`:

1. Install board packages (one-time setup):
   ```
   arduino-cli config set board_manager.additional_urls \
     https://github.com/mcci-catena/arduino-boards/raw/master/BoardManagerFiles/package_mcci_index.json \
     https://adafruit.github.io/arduino-board-index/package_adafruit_index.json \
     https://dl.espressif.com/dl/package_esp32_index.json
   arduino-cli core update-index
   arduino-cli core install mcci:samd mcci:stm32 esp32:esp32
   ```

2. Create a test sketch for each header (`mcciadk_baselib.h`, `mcciadk_env.h`, `mcciadk_guid.h`):
   ```
   mkdir -p /tmp/headertest_mcciadk_baselib
   echo -e '#include <mcciadk_baselib.h>\nvoid setup() {}\nvoid loop() {}' \
     > /tmp/headertest_mcciadk_baselib/headertest_mcciadk_baselib.ino
   ```

3. Compile against each target:
   ```
   arduino-cli compile --fqbn mcci:samd:mcci_catena_4450 /tmp/headertest_mcciadk_baselib
   arduino-cli compile --fqbn "mcci:stm32:mcci_catena_4551:lorawan_region=us915,opt=osstd,xserial=generic,sysclk=pll32m" /tmp/headertest_mcciadk_baselib
   arduino-cli compile --fqbn esp32:esp32:heltec_wifi_lora_32 /tmp/headertest_mcciadk_baselib
   ```

There are no unit tests beyond compile-time header verification.

## Code Conventions

### Naming
- Macro prefix: `MCCIADK_` (uppercase with underscores)
- Function prefix: `McciAdkLib_` (PascalCase)
- Source files: `mcciadklib_<functionname>.c` (all lowercase)
- Header guards: `#ifndef _FILENAME_H_`

### File Headers
Every source file has a structured header comment block with Module, Function, Copyright notice, Author, and revision history sections. Use `/* */` comment style for these blocks. Section separators use `/**********************/` banners.

### Style
- Opening braces on their own line
- Function parameters each on their own line, indented with tabs
- Use `MCCIADK_UNREFERENCED_PARAMETER()` and `MCCIADK_API_PARAMETER()` to suppress warnings on intentionally unused parameters
- `MCCIADK_BEGIN_DECLS` / `MCCIADK_END_DECLS` wrap C function declarations for C++ compatibility

### Architecture

Three public headers in `src/`:
- **`mcciadk_env.h`** -- environment/portability macros, version macros, compile-time utilities (`MCCIADK_CONTAINER_OF`, `MCCIADK_LENOF`, `MCCIADK_C_ASSERT`, string/concat macros)
- **`mcciadk_guid.h`** -- GUID/UUID declaration and initialization macros
- **`mcciadk_baselib.h`** -- library functions (includes `mcciadk_env.h`): string-to-number conversion, custom snprintf (avoids stdio dependency), hex dump formatting, case-insensitive compare, multi-string indexing, safe string copy

Implementation files live in `src/lib/`, one function per file.

## Copyright and License

MIT license. Copyright MCCI Corporation. Use existing file headers as templates.
