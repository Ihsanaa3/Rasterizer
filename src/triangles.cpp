#include<tgaimage.h> 
#include"drawTools.h" 

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255}; 

void triangleWireFrame(int ax, int ay, int bx, int by, int cx, int cy,
    TGAImage& framebuffer, TGAColor col = white){
        drt::drawLine4(ax, ay, bx, by ,framebuffer, col); 
        drt::drawLine4(cx, cy, bx, by ,framebuffer, col); 
        drt::drawLine4(ax, ay, cx, cy ,framebuffer, col); 
    }

int main(int argc, char** argv){
    constexpr int width = 640; 
    constexpr int height = 640; 
    TGAImage framebuffer(width, height, TGAImage::RGB); 

    int ax =  70, ay =  30;
    int bx = 120, by = 370;
    int cx = 620, cy = 530;

    framebuffer.set(ax, ay, white); 
    framebuffer.set(bx, by, white); 
    framebuffer.set(cx, cy, white); 
    
    triangleWireFrame(ax, ay, bx, by, cx, cy, framebuffer, red); 

    framebuffer.write_tga_file("framebuffer.tga"); 
    return 0; 

}