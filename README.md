# Bliss

A C++ DirectX 11 + ImGui overlay chear for `Among Us`.

> [!NOTE]
> Originally developed in August 2025, this project remains fully functional as of July 2026 without requiring any updates.
> Well because I fetch every single class info during runtime via il2cpp api. I can assure you that the codebase does not die.

> [!IMPORTANT]  
> I've only implemented basic features, such as viewing roles. However, I've fully implemented the IL2CPP system, making it easy to add, edit, or remove any features you want. This is just a simple demonstration, and I'll continue updating the project as I add more features.

---

## Features

- DirectX 11 rendering hook
- Dear ImGui user interface
- MinHook integration
- IL2CPP function access
- Memory utilities
- Modular project structure
- CMake build system

---

## Project Structure

```
include/
    Bliss/
        Game.h
        Gui.h
        Hooks.h
        Memory.h
        Offsets.h
        ...

src/
    Entry.cpp
    Gui.cpp
    memory/
    util/

external/
    minhook/

CMakeLists.txt
```

---

## Requirements

- Windows
- CMake 3.18+
- DirectX SDK (Windows SDK)
- C++20 compiler

---

## Building

Clone the repository:

```bash
git clone https://github.com/emsar69/Bliss.git
cd Bliss
```

Generate the project:

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" .. # Or you can alternatively use ninja.
mingw32-make
```


The resulting DLL will be located in the build output directory.
Inject it using any injector you wish. I'd recommend Cheat Engine.

---

## Architecture

The project is organized into several independent modules:

| Module | Description |
|---------|-------------|
| Hooks | Runtime API hooks |
| Memory | Memory utilities and initialization |
| GUI | ImGui rendering |
| Devices | DirectX device management |
| Game | Game-specific abstractions |

This modular design makes the framework easy to extend and maintain.

---

## License
[GPL-3.0](LICENSE)