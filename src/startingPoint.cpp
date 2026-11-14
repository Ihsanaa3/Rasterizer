#include<tgaimage.h> 

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255}; 

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

    framebuffer.write_tga_file("framebuffer.tga"); 
    return 0; 

}