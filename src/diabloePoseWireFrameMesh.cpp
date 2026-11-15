#include<tgaimage.h> 
#include<cmath> 
#include<fstream> 
#include<iostream> 
#include"extraFunctions.h" 

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255}; 

constexpr int width = 640; 
constexpr int height = 640; 

void drawLine(int ax, int ay, int bx, int by, 
    TGAImage &framebuffer, TGAColor col)
{
    // Second approach, uses t as a function of x instead of x as a function of t 
    bool isSteep = std::abs(ax - bx) < std::abs(ay - by); 
    if(isSteep){ 
        // transposes steep lines so that it draws it for every y instead of x 
        std::swap(ax, ay); 
        std::swap(bx, by); 
    }
    if(ax > bx){
        // ensures that it is able to draw all lines from left to right 
        std::swap(ax, bx); 
        std::swap(ay, by); 
    }

    int y = ay; 
    float diff = static_cast<float>(by - ay) / static_cast<float>(bx - ax); 

    for(int x = ax; x <= bx; x++){
        y += std::round(diff); 
        if(!isSteep){
            framebuffer.set(x, y, col); 
        }else{
            framebuffer.set(y, x, col); 
        }
    }
}

int main(int argc, char** argv){

    TGAImage framebuffer(width, height, TGAImage::RGB); 

    std::string diabloText; 

    std::ifstream diabloOBJ("C:/Coding/Rasterizer/res/objs/diablo3_pose.obj"); 

    while(std::getline(diabloOBJ, diabloText)){
        std::cout << diabloText << std::endl; 
    }
    diabloOBJ.close(); 
    framebuffer.write_tga_file("framebuffer.tga"); 
    return 0; 
}