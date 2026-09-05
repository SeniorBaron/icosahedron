# OpenGL Icosahedron

A minimalistic OpenGL project that renders an animation of a rotating 3D icosahedron. Built as a learning exercise to explore the core concepts of modern graphics programming.

![Project Screenshot](demo/screenshot.png)

## Key Features

* **Procedural animation** using custom mathematical functions
* **Multi-layered movement** combining Bézier curves, smooth interpolation, and exponential functions

## Build Requirements

* Windows
* Visual Studio Build Tools
* GLFW CMake package
* GLM CMake package

## Build & Run

#### Clone

```powershell
git clone https://github.com/TheRealBaron/icosahedron
```

#### Configure CMake

```powershell
cmake -B build
```

If GLFW or GLM is installed in a non-default location, provide their installation paths through `CMAKE_PREFIX_PATH`:

```powershell
cmake -B build -DCMAKE_PREFIX_PATH="/path/to/glfw;/path/to/glm"
```

#### Build

```powershell
cmake --build build
```

#### Install

```powershell
cmake --install build --prefix install
```

#### Run

```powershell
cd install
.\icosahedron.exe
```

It is important to launch the executable from the same directory as the executable because the paths to the shaders are hardcoded and are relative to the executable's location.

## Project Goals

The main goal was to understand the setup and use of:

* OpenGL function loading with GLAD
* Compiling and using custom GLSL shaders
* Implementing a basic game loop with delta time

## License

This project is licensed under the **MIT License**. See [LICENSE.txt](LICENSE.txt) for the full license text.

## Third-Party Dependencies

This project includes or depends on third-party software that is distributed under its own licenses:

* **GLAD** - generated code; see the license and copyright notices included with the generated files.
* **GLM** - MIT License
* **GLFW** - zlib/libpng License
* **Windows API** — provided by Microsoft as part of Windows

These third-party components are **not covered by this project's MIT License**. Refer to their respective license terms for details.

