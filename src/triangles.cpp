#include<tgaimage.h> 
#include<iostream> 
#include"drawTools.h" 
#include<array>
#include<vector> 

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

std::vector<std::array<int, 2>> coordsInts(int ax, int ay, int bx, int by){
    std::vector<std::array<int, 2>> coords; 
    bool steep = std::abs(ax-bx) < std::abs(ay-by);
    if (steep) {
        std::swap(ax, ay);
        std::swap(bx, by);
    } 
    if (ax>bx) {
        std::swap(ax, bx);
        std::swap(ay, by);
    }
    int y = ay;
    int ierror = 0;
    for (int x=ax; x<=bx; x++) {
        if (steep) // if transposed, de−transpose
            coords.push_back({y, x}); 
        else
            coords.push_back({x, y});
        ierror += 2 * std::abs(by-ay);
        y += (by > ay ? 1 : -1) * (ierror > bx - ax);
        ierror -= 2 * (bx-ax)   * (ierror > bx - ax);
    }

    return coords; 
}

void triangleFill(int ax, int ay, int bx, int by, int cx, int cy,
    TGAImage& framebuffer, TGAColor col = white)
{
    std::vector<std::array<int, 2>> coordsab = coordsInts(ax, ay, bx, by); 
    std::vector<std::array<int, 2>> coordsbc = coordsInts(cx, cy, bx, by); 
    std::vector<std::array<int, 2>> coordsac = coordsInts(ax, ay, cx, cy);  
    
    for (auto& v: coordsab){
        std::cout << v[0] << " " << v[1] << std::endl; 
    }
    std::cout <<" nl" << std::endl; 
    for (auto& v: coordsac){
        std::cout << v[0] << " " << v[1] << std::endl; 
    }
    std::cout <<" nl" << std::endl; 
    for (auto& v: coordsbc){
        std::cout << v[0] << " " << v[1] << std::endl; 
    }
}

int main(int argc, char** argv){
    constexpr int width = 320; 
    constexpr int height = 320; 
    TGAImage framebuffer(width, height, TGAImage::RGB); 
    drt::drawBorder(width, height, framebuffer); 
    
    triangleFill(  7, 45, 35, 100, 45,  60, framebuffer, red);
    triangleWireFrame(120, 35, 90,   5, 45, 110, framebuffer, white);
    triangleWireFrame(115, 83, 80,  90, 85, 120, framebuffer, green); 

    framebuffer.write_tga_file("framebuffer.tga"); 
    return 0; 

}