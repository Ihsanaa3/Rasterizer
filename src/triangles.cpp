#include<tgaimage.h> 
#include"drawTools.h" 

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255}; 

void triangleWireFrame(int ax, int ay, int bx, int by, int cx, int cy,
    TGAImage& framebuffer, TGAColor col = white){
        framebuffer.set(ax, ay, white); 
        framebuffer.set(bx, by, white);
        framebuffer.set(cx, cy, white);
        drt::drawLine4(ax, ay, bx, by ,framebuffer, col); 
        drt::drawLine4(cx, cy, bx, by ,framebuffer, col); 
        drt::drawLine4(ax, ay, cx, cy ,framebuffer, col); 
    }

int main(int argc, char** argv){
    constexpr int width = 320; 
    constexpr int height = 320; 
    TGAImage framebuffer(width, height, TGAImage::RGB); 
    drt::drawBorder(width, height, framebuffer); 
    
    triangleWireFrame(  7, 45, 35, 100, 45,  60, framebuffer, red);
    triangleWireFrame(120, 35, 90,   5, 45, 110, framebuffer, white);
    triangleWireFrame(115, 83, 80,  90, 85, 120, framebuffer, green); 

    framebuffer.write_tga_file("framebuffer.tga"); 
    return 0; 

}