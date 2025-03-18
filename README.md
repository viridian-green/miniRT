miniRT: My First Ray Tracer with MiniLibX

Introduction
Rendering three-dimensional images can be achieved using two main techniques: Rasterization and Ray Tracing. Rasterization, favored by modern graphics engines due to its efficiency, quickly transforms 3D models into 2D images. In contrast, Ray Tracing follows the physics of light to produce highly realistic images at the cost of computational expense.

miniRT is a simple yet functional ray tracer written in C, designed to introduce the fundamental concepts of ray tracing. This project aims to demonstrate that implementing complex mathematical and physical formulas is possible without being a mathematician.

Features
Implements basic ray tracing principles such as primary rays and shading.
Uses the MiniLibX library for window management and rendering.
Supports planes, spheres, and cylinders with basic lighting.
Adheres to the 42 Norm and follows strict memory management practices.
Project Requirements
Written in C, following the 42 Norm guidelines.
Proper memory management to avoid leaks.
No unexpected crashes (segmentation faults, bus errors, etc.).
Uses a Makefile with standard rules (all, clean, fclean, re).
Compilation & Execution
To compile the project, use:
make
To run the ray tracer with a scene file:

./miniRT scenes/example.rt

Conclusion
This project serves as an introduction to ray tracing and its mathematical foundations. By completing miniRT, you’ll gain hands-on experience with rendering techniques, C programming, and memory management—all while creating visually impressive images.

