# SI-Fish 🐟

A 3D animated fish model built from scratch using OpenGL and GLUT. The fish is assembled entirely from custom geometric primitives - no utility libraries like `gluSphere` - and supports JPEG texture mapping, Phong lighting, and two animations (jump and figure-8 movement).

This project was developed as part of a computer graphics (Image Synthesis) course.

---

## Features

- **Custom 3D primitives** - Sphere, Cylinder, Torus, and Truncated Pyramid, all hand-computed with vertex buffers, index arrays, and normal vectors
- **JPEG texture loading** - skin and fin textures loaded via `libjpeg` and mapped with OpenGL
- **Phong lighting** - two configurable light sources (point light + spotlight) with ambient, diffuse, and specular components
- **Animations** - jump (gravity-simulated) and figure-8 path following
- **Interactive controls** - mouse rotation, scroll-wheel zoom, keyboard shortcuts, and a right-click menu

---

## Project Structure

```
SI-Fish/
├── cube.cpp                    # Main file: scene setup, draw loop, input handling
├── Point.h / Point.cpp         # Simple 3D point/vector struct
├── PrimitiveSphere.h/.cpp      # Sphere primitive (meridians × parallels)
├── PrimitiveCylindre.h/.cpp    # Cylinder primitive with disk caps
├── PrimitiveTorus.h/.cpp       # Torus primitive
├── PrimitiveTrunquedPyramid.h/.cpp  # Truncated pyramid (frustum) primitive
├── CMakeLists.txt
└── ressources/
    └── textures/
        ├── texSkin.jpg         # Fish body texture (1300×1300)
        └── texFin2.jpeg        # Fin texture (1536×1024)
```

---

## Dependencies

| Library | Purpose |
|---|---|
| **OpenGL** | Core rendering API |
| **GLUT / FreeGLUT** | Window management, input callbacks, and display loop |
| **GLU** | OpenGL utility (matrix helpers) |
| **libjpeg** | JPEG texture loading |
| **CMake ≥ 3.10** | Build system |
| **C++11** | Language standard |

### Installing dependencies on Ubuntu / WSL

```bash
sudo apt update
sudo apt install build-essential cmake \
    libgl1-mesa-dev libglu1-mesa-dev \
    freeglut3-dev libjpeg-dev
```

### Installing dependencies on macOS (Homebrew)

```bash
brew install cmake freeglut jpeg
```

OpenGL and GLUT are included natively on macOS via the system frameworks - the code already handles this with the `#ifdef __APPLE__` guard in `cube.cpp`.

---

## Build & Run

```bash
# Clone the repo
git clone <repo-url>
cd SI-Fish

# Create a build directory
mkdir build && cd build

# Configure and compile
cmake ..
make

# Run (from the build directory, so relative texture paths resolve correctly)
./CubeGL
```

---

## Controls

| Input | Action |
|---|---|
| **Left-click + drag** | Rotate the scene |
| **Scroll wheel** | Zoom in / out |
| **Arrow keys** | Rotate the scene (keyboard) |
| `z` / `Z` | Zoom in / out |
| `Space` | Trigger jump animation |
| **Right-click** | Open menu |

### Right-click menu

| Option | Effect |
|---|---|
| Light0 | Toggle main point light |
| Light1 | Toggle secondary spotlight |
| Mode plein | Solid fill rendering |
| Mode maille de fer | Wireframe rendering |
| Mode point | Point cloud rendering |
| 8 Animation | Toggle figure-8 swimming animation |
| Quitter | Exit |

---

## Notes

- Texture files must be **exactly** the dimensions expected by `loadJpegImage()` in `cube.cpp` (`1300×1300` for skin, `1536×1024` for fin). The loader will exit with an error otherwise.
- The `RESOLUTION` constant at the top of `cube.cpp` controls geometric detail - higher values increase polygon count across all primitives.
- The project was originally developed and tested under **WSL2 (Ubuntu)** with a standard Mesa OpenGL stack.
