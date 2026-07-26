# BGL Shooter Tech Demo

A modernized, high-performance **C++23** Quake II BSP and MD2 rendering engine tech demo targeting Linux (amd64 / Ubuntu).

> [!NOTE]
> **Historical Retro Codebase (~20 Years Old):**  
> Originally developed around 2004–2006 for Windows, this project is a historical 3D tech demo powered by the **legacy OpenGL 1.x/2.x fixed-function pipeline** (`glBegin`/`glEnd`, `glMatrixMode`, fixed-function lightmap blending with `GL_MODULATE`, display lists, and classic texture environments).  
> The codebase has been fully modernized to build with **C++23**, **GLM**, **spdlog**, **Conan v2**, **CMake**, and run seamlessly on modern Linux desktops while preserving its authentic 2000s graphics rendering pipeline and retro aesthetics.

---

## Key Features & Modernization Architecture

- **Legacy OpenGL 1.x/2.x Fixed-Function Engine:** Preserves original Quake II BSP map rendering, multi-textured lightmaps (`GL_TEXTURE0` / `GL_TEXTURE1`), MD2 animated models, and PVS visibility clusters using fixed-function pipeline mechanics.
- **C++23 Standard:** Upgraded to the modern C++23 ISO standard with clean architecture across `src/core`, `src/gfx`, `src/math`, `src/physics`, `src/input`, and `src/audio`.
- **spdlog Logging:** Integrated `spdlog` for structured, timestamped console logging and error reporting.
- **GLM Math Integration:** Replaced custom legacy vector/matrix math with `glm::vec3` and GLM extension utilities.
- **Conan v2 & CMake:** Fully managed third-party dependencies (`FreeGLUT`, `GLEW`, `DevIL`, `FreeALUT`, `OpenAL`, `GLM`, `spdlog`) via Conan 2.x and CMake 3.20+.
- **Cross-Platform Compatibility:** Replaced Windows-specific legacy headers (`windows.h`, `timeGetTime`) with portable standard library and FreeGLUT primitives.

---

## System Requirements

- **OS:** Linux (Ubuntu / Debian x86_64)
- **Compiler:** GCC 13+ or Clang 16+ with C++23 support
- **Build Tools:** CMake 3.20+, Conan 2.x, Task runner (`task`), `clang-format`
- **Graphics & Audio:** OpenGL-compatible graphics driver, OpenAL / ALSA backend

---

## Building and Running

### 1. Install Conan Dependencies

```bash
task setup
```

### 2. Configure & Build Project

```bash
task configure
task build
```

### 3. Run Demo

```bash
task run
```

### Additional Commands

- **Format Codebase:** `task format`
- **Clean Build Directory:** `task clean`

---

## Configuration

Configuration settings are stored in English within `bin/configuration.ini`:

- `Windowed`: Set to `1` for windowed mode or `0` for fullscreen mode.
- `ResolutionX` / `ResolutionY`: Window or display resolution (`-1` selects optimal desktop resolution).
- `PositionX`, `PositionY`, `PositionZ`: Initial 3D camera spawn position.
- `RotationX`, `RotationY`, `RotationZ`: Initial camera orientation angles.
- `Audio`: Enable/disable background music and sound effects (`1` or `0`).
- `Skybox` / `AnimateWater`: Render toggles for environment and shader effects.

---

## License

This project is licensed under the MIT License - see the LICENSE file for details.
