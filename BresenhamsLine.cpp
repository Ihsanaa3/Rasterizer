#include<tgaimage.h> 
#include<iostream> 
#include<cmath> 

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255}; 

int diagonalDistance(int width, int height){
    return std::ceil(std::sqrt(width * width + height * height)); 
}

void drawLine(int ax, int ay, int bx, int by, int width, int height,
        TGAImage &framebuffer, TGAColor col = {255, 255, 255, 255})
    {
    int noIntervals = diagonalDistance(width, height); 
    for(float t = 0; t < 1.0f; t += (1.0f / noIntervals)){
        int x = std::round(ax + t * (bx - ax)); 
        int y = std::round(ay + t * (by - ay)); 

        framebuffer.set(x, y, col); 
    }
}

int main(int argc, char** argv){
    constexpr int width = 640; 
    constexpr int height = 640; 
    TGAImage framebuffer(width, height, TGAImage::RGB); 

    int ax =  70, ay =  30;
    int bx = 120, by = 370;
    int cx = 620, cy = 530;

    // framebuffer.set(ax, ay, white); 
    // framebuffer.set(bx, by, white); 
    // framebuffer.set(cx, cy, white); 
    drawLine(ax, ay, bx, by, width, height, framebuffer, red); 
    drawLine(ax, ay, cx, cy, width, height, framebuffer, blue);     
    drawLine(cx, cy, bx, by, width, height, framebuffer, green); 

    framebuffer.write_tga_file("framebuffer.tga"); 
    return 0; 

}
