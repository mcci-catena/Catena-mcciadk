# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Catena-mcciadk is the MCCI Arduino Development Kit (ADK), a port of the MCCI XDK portability toolkit for Arduino and deeply-embedded environments. It provides portable C/C++ utility macros and functions. Current version is in `VERSION.txt`.

## Build and Test

This is an Arduino library -- there is no standalone build system. It builds via the Arduino IDE/CLI as part of projects that depend on it.

**CI (Travis CI)** compiles header-inclusion tests against three targets:
- MCCI SAMD (Catena 4450)
- MCCI STM32L0 (Catena 4551)
- ESP32 (Heltec WiFi LoRa 32)

To replicate CI locally, use `arduino --verify` with the appropriate board options (see `.travis.yml` for exact board strings and BSP URLs).

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
