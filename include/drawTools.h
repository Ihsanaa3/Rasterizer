#include<tgaimage.h> 

// constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
// constexpr TGAColor green   = {  0, 255,   0, 255};
// constexpr TGAColor red     = {  0,   0, 255, 255};
// constexpr TGAColor blue    = {255, 128,  64, 255};
// constexpr TGAColor yellow  = {  0, 200, 255, 255}; 

namespace drt{
    void drawLine4(int ax, int ay, int bx, int by, TGAImage &framebuffer, TGAColor col); 
    void drawBorder(int width, int height, TGAImage& frambuffer, TGAColor col = {255, 255, 255, 255}); 
}