# 3D Graphics Renderer

A 3D renderer built in C++ with SDL3 using quaternion camera rotation and 
perspective projection.

## Demo

<video src="https://github.com/user-attachments/assets/08212da2-246a-43bf-b6db-a92416fbd86d" controls></video>

## Overview
This is a personal project built to understand how 3D graphics work at a 
fundamental level without a graphics engine. 

## Features
- Quaternion based camera rotation 
- Rotation matrix derived from quaternion components each frame
- Perspective projection with focal length calculated from field of view
- Camera movement using keys relative to the camera rotation
- Camera direction using mouse
- Z clipping to prevent artifacts behind the camera
- Colored face rendering with scan line interpolation for fill (temporary)

## Controls
WASD for camera movement 
Space and K for movement up and down
Q and E for roll left and right
Mouse to look around
Escape to quit

## How to Build
### Requirements
- C++ compiler preferably MinGW
- SDL3 library
    Download SDL3 from https://github.com/libsdl-org/SDL/releases
    Place the SDL3 library files in src/lib
    Place SDL3.dll in the root directory

### Windows (MinGW)
1. Clone the repository
2. Ensure SDL3.dll is in the same directory as the executable
3. Compile using the Makefile by executing:

make

4. Run `program.exe`

### Manual Compilation
Manual compilation requires SDL3 headers and libraries to be 
configured for your system so using the Makefile is recommended.

## Planned Features
- Z buffer implementation for correct depth ordering at all camera angles
- Painter's algorithm to draw faces correctly based on depth
- Adjacency system for SDL_Point3D to create shapes 
- Liang Barsky algorithm for line clipping
- Lighting and shading

## Built With
- C++
- SDL3
