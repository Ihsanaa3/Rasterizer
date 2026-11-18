#include<tgaimage.h> 
#include<iostream> 
#include<algorithm>
#include"drawTools.h" 
#include<array>
#include<vector> 
#include"extraFunctions.h"

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

std::vector<std::array<int, 2>> getSortedTriangleCoords(int ax, int ay, int bx, int by, int cx, int cy){
    std::vector<std::array<int, 2>> coordsab = coordsInts(ax, ay, bx, by); 
    std::vector<std::array<int, 2>> coordsbc = coordsInts(cx, cy, bx, by); 
    std::vector<std::array<int, 2>> coordsac = coordsInts(ax, ay, cx, cy);  
    std::vector<std::array<int, 2>> coords; 

    for(auto& v: coordsab){coords.push_back(v); }
    for(auto& v: coordsbc){coords.push_back(v); }
    for(auto& v: coordsac){coords.push_back(v); }

    std::sort(coords.begin(), coords.end(), [](const auto& a, const auto& b) {return a[1] > b[1];});   

    return coords; 
}

void triangleFill(int ax, int ay, int bx, int by, int cx, int cy,  
    TGAImage& framebuffer, TGAColor col = white)
{ 
    std::vector<std::array<int, 2>> coords = getSortedTriangleCoords(ax, ay, bx, by, cx, cy); 
    std::vector<int> ys ={ay, by, cy}; 

    int max_y = *std::max_element(ys.begin(), ys.end());
    int min_y = *std::min_element(ys.begin(), ys.end());

    for(int i = max_y; i >= min_y; i--){
        int min_x = 1e9;
        int max_x = -1e9;
        bool found = false;

        for(auto& v: coords){
            if(v[1] == i){
                if(v[0] < min_x) min_x = v[0];
                if(v[0] > max_x) max_x = v[0];
                found = true;
            }
        }

        if(!found){
            continue; 
        }

        if(min_x == max_x){
            framebuffer.set(min_x, i, col); 
        } else {
            drt::drawLine4(min_x, i, max_x, i, framebuffer, col); 
        }
    }
}

int main(int argc, char** argv){
    constexpr int width = 900; 
    constexpr int height = 900; 
    TGAImage framebuffer(width, height, TGAImage::RGB); 
    drt::drawBorder(width, height, framebuffer); 
    
    for (int i = 0; i < 100; i++){
        triangleFill(
        rd::randInt(width), rd::randInt(height), rd::randInt(width), 
        rd::randInt(height), rd::randInt(width), rd::randInt(height), framebuffer, 
        {static_cast<uint8_t>(rd::randInt(255)),
                    static_cast<uint8_t>(rd::randInt(255)),
                    static_cast<uint8_t>(rd::randInt(255)),
                    static_cast<uint8_t>(rd::randInt(255))
                }); 
    }

    framebuffer.write_tga_file("framebuffer.tga"); 
    return 0; 

}