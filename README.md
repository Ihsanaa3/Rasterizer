# Learning Rasterizers and Vector Graphics

Welcome! This repository is a place to explore how vector graphics are turned into the pixels we see on a screen. That process is called rasterization.

## The big idea

A vector image describes shapes mathematically: lines, curves, and filled regions. A raster image is a grid of pixels, each holding a color. A rasterizer bridges the two by deciding which pixels are covered by each shape and what color those pixels should receive.

This distinction makes vector graphics useful for logos, diagrams, and illustrations: their descriptions can be scaled without storing a separate image for every size. Raster images, such as photographs, store the pixel grid directly.

## A simplified rendering pipeline

1. Describe geometry — represent paths with points, line segments, and curves.
2. Transform coordinates — apply translation, rotation, scaling, or other transforms.
3. Determine coverage — find which parts of the pixel grid are touched by each shape.
4. Shade and composite — choose colors and combine overlapping shapes, often using transparency.
5. Display the pixels — send the resulting image to a screen or save it to a file.

Real graphics systems add details such as clipping, strokes, gradients, and color management, but this pipeline is a useful starting point.

## Why edges look jagged

A geometric edge can pass through the middle of a pixel. If a renderer labels every pixel simply “inside” or “outside,” diagonal lines and curves can look like stair steps. This is aliasing.

Anti-aliasing reduces the effect by estimating how much of a pixel is covered by a shape and blending the shape’s color with the background. A pixel that is 25% covered, for example, contributes less of the shape’s color than a fully covered pixel.

## A few topics to explore

- Line rasterization: algorithms such as Bresenham’s choose a sequence of pixels that approximates a line.
- Curve flattening: Bézier curves can be approximated by short line segments before rasterization.
- Fill rules: the even-odd and non-zero winding rules determine which regions of a path are filled, including paths with holes.
- Alpha compositing: transparency lets layers blend; the order in which layers are drawn can matter.
- Sampling: pixels represent samples of a continuous image, so the sampling strategy affects sharpness and detail.

## Try an experiment

Draw a diagonal line or a small circle at several scales. Compare a hard inside/outside pixel test with a coverage-based approach. Then change the shape’s position by a fraction of a pixel and observe how the result changes. These experiments make sampling and anti-aliasing easier to understand.

## Learning goals

As you explore the code, try to answer these questions:

- How is a shape represented before it becomes pixels?
- How does the renderer decide whether a pixel is inside a shape?
- What happens when two shapes overlap?
- How could the renderer make edges smoother without losing the underlying geometry?

The best way to learn graphics is to build a small renderer, inspect its pixels, and change one part of the pipeline at a time. Have fun experimenting!
