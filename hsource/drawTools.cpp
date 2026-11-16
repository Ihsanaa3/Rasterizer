#include"drawTools.h" 


void drt::drawLine4(int ax, int ay, int bx, int by, 
    TGAImage &framebuffer, TGAColor col)
{
    // Final approach, by using error calculations it become completely integer calculated 
    // this is brenshams algorithm  
    // technically slightly slower than approach 3 for reasons 
    bool steep = std::abs(ax-bx) < std::abs(ay-by);
    if (steep) { // if the line is steep, we transpose the image
        std::swap(ax, ay);
        std::swap(bx, by);
    }
    if (ax>bx) { // make it left−to−right
        std::swap(ax, bx);
        std::swap(ay, by);
    }
    int y = ay;
    int ierror = 0;
    for (int x=ax; x<=bx; x++) {
        if (steep) // if transposed, de−transpose
            framebuffer.set(y, x, col);
        else
            framebuffer.set(x, y, col);
        ierror += 2 * std::abs(by-ay);
        y += (by > ay ? 1 : -1) * (ierror > bx - ax);
        ierror -= 2 * (bx-ax)   * (ierror > bx - ax);
    }
}