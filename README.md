# Learning Software Rasterization

This repository is a small C++ software-rasterizer project, built by implementing the drawing steps directly rather than handing them to a graphics API. It is inspired by the incremental, code-first approach of [TinyRenderer](https://github.com/ssloy/tinyrenderer): start with pixels and lines, then use those building blocks to draw geometry.

The project is a work in progress. At this stage, it can write TGA images, draw lines with Bresenham’s algorithm, and render the edges of a 3D model as a wireframe. It does not yet implement filled triangles, a depth buffer, lighting, or a complete 3D rendering pipeline.

## What the code does today

The current experiments are in `src/`:

- `startingPoint.cpp` creates a 640 × 640 image, sets a few pixels, and writes `framebuffer.tga`.
- `BresenhamsLine.cpp` draws lines using an integer error accumulator. It handles steep lines by swapping the axes and draws from left to right, then writes a TGA image. The sample currently draws many randomly generated lines and reports its run time.
- `diabloePoseWireFrameMesh.cpp` reads vertex (`v`) and face (`f`) records from an OBJ model, maps the vertex x/y coordinates into the image, and draws each face’s edges with the line routine. This produces a wireframe, not a shaded or filled model.

`include/tgaimage.h` and `hsource/tgaimage.cpp` provide the image and TGA-writing code. `include/extraFunctions.h` and `hsource/extraFunctions.cpp` contain random-number helpers used by the line experiment. There is also a rotation helper in `include/rotation.h` and `hsource/rotation.cpp` for generating rotated 2D vertices.

## The rendering steps so far

### 1. Make a framebuffer

A framebuffer is an image-sized array of color values. The code creates a `TGAImage`, sets pixels with `set(x, y, color)`, and writes the result to a TGA file. This keeps the output simple: the renderer produces an image file without needing a window or graphics hardware.

### 2. Turn a line into pixels

A line is continuous geometry, but the framebuffer is a grid. Bresenham’s algorithm chooses a discrete sequence of pixels that follows the line. It uses integer arithmetic to track the error between the ideal line and the selected pixels. For steep lines, the implementation swaps x and y so it can use the same stepping logic, then swaps them back when plotting.

### 3. Draw a model as connected edges

The wireframe experiment reads vertex positions and face indices from an OBJ file. OBJ face indices are one-based, so they are adjusted before looking up the corresponding vertices. The x and y coordinates are mapped from the model’s expected range into framebuffer coordinates, and each triangle’s three edges are rasterized with the line routine.

This is a deliberately small first step toward 3D rendering. The current model path is hard-coded in the source, and the OBJ parsing and coordinate mapping make assumptions about the input. The code does not yet use vertex z values to decide which surfaces are visible, so hidden edges are drawn too.

## Build and run

The Makefile currently compiles the support sources into object files. From a MinGW/MSYS shell, run:

```sh
mingw32-make
```

The source files under `src/` each contain their own `main`, so build and run one experiment at a time rather than linking all of them into one executable. The wireframe experiment also currently opens the model using a hard-coded Windows path in `src/diabloePoseWireFrameMesh.cpp`; update that path to the location of `res/objs/diablo3_pose.obj` on your machine before running it. Output images are written as TGA files in the program’s working directory.

## A useful way to explore

Follow the code in small steps, as in TinyRenderer:

1. Start with `startingPoint.cpp` and inspect the TGA image it produces.
2. In `BresenhamsLine.cpp`, compare the integer line routine with the earlier commented-out approaches. Try changing the endpoints, color, and number of lines.
3. Follow the OBJ experiment from loading vertices and face indices through coordinate mapping to calls to `drawLine`.
4. Change one part at a time and inspect the generated image to see how the pixels change.

## Possible next steps

A natural progression from the current code would be to make the OBJ path configurable, separate line drawing and model loading into reusable functions, fill triangles, and then add a z-buffer so nearer surfaces hide farther ones. After that, vertex transforms and simple shading could extend the renderer toward the stages explored in TinyRenderer.

The goal is to understand each step by implementing it and looking at the pixels it produces. This repository is an early stage of that process, not a finished general-purpose renderer.
