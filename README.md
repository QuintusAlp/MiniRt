# MiniRT

A simple raytracer implementation in C that renders 3D scenes with basic geometric objects, lighting, and realistic visual effects using mathematical ray-tracing algorithms.

## About

MiniRT is a 42 School project that introduces the fundamentals of computer graphics and ray tracing. The program reads scene descriptions from `.rt` files and generates photorealistic images by simulating light rays bouncing through a 3D environment. This implementation demonstrates core concepts in 3D mathematics, physics simulation, and graphics programming.

The raytracer supports multiple geometric primitives, different light sources, and realistic shading models to create compelling 3D rendered images.

## Key Features

- **Ray Tracing Engine**: Core ray-object intersection algorithms
- **3D Geometric Objects**: Spheres, planes, cylinders, and cones
- **Multiple Light Sources**: Ambient light, point lights, and directional lighting
- **Realistic Shading**: Phong shading model with ambient, diffuse, and specular components
- **Scene File Parsing**: Custom `.rt` file format for scene description
- **Mathematical Precision**: Vector operations and 3D transformations
- **Image Export**: PPM format output for rendered images
- **Real-time Preview**: Window display using MiniLibX graphics library
- **Interactive Controls**: Camera movement and scene navigation

## Usage

### Compilation
```bash
make
```

### Execution
```bash
./miniRT [scene_file.rt]
```

### Scene File Format
Create `.rt` files with the following elements:

```bash
# Resolution
R 1920 1080

# Ambient lighting
A 0.2 255,255,255

# Camera
c -50,0,20 0,0,0 70

# Light source
l -40,0,30 0.7 255,255,255

# Sphere
sp 0,0,20 20 255,0,0

# Plane
pl 0,0,0 0,1,0 255,255,255

# Cylinder
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
```

### Examples
```bash
./miniRT sscenes/pokeball.rt
'''

### Controls
- **ESC**: Exit the program

## Screen Captures

### pokeball
<img width="1893" alt="Capture d’écran 2025-06-12 à 22 34 46" src="https://github.com/user-attachments/assets/44099a7c-e0c6-4c25-9e04-aea77aa6689d" />

### atoms
<img width="1908" alt="Capture d’écran 2025-06-12 à 22 33 54" src="https://github.com/user-attachments/assets/678c490c-3079-4c77-8777-4cf7f9140c52" />

### pharaon
<img width="1912" alt="Capture d’écran 2025-06-12 à 22 34 19" src="https://github.com/user-attachments/assets/c9d48025-146b-4b23-a3f1-025d6b95c4ea" />

### Lighting Variations
<img width="1903" alt="Capture d’écran 2025-06-12 à 22 39 08" src="https://github.com/user-attachments/assets/0d8c97f8-cd3d-43f2-989f-bf56ef1f2190" />

## Technical Skills Demonstrated

- **3D Mathematics**: Vector operations, dot products, cross products, and matrix transformations
- **Ray Tracing Algorithms**: Ray-object intersection calculations and recursive ray bouncing
- **Computer Graphics**: Understanding of lighting models, shading, and color theory
- **Geometric Programming**: Implementation of 3D primitive objects and their mathematical representations
- **Physics Simulation**: Light behavior simulation and realistic material properties
- **File I/O Processing**: Custom scene file parsing and validation
- **Memory Management**: Efficient handling of complex 3D scene data structures
- **Mathematical Problem Solving**: Translation of mathematical concepts into working code
- **Graphics Programming**: Low-level pixel manipulation and image generation
- **Algorithm Optimization**: Performance optimization for computationally intensive ray calculations
- **Software Architecture**: Clean separation between scene parsing, ray tracing engine, and rendering output
