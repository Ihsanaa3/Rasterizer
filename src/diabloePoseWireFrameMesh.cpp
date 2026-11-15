#include<tgaimage.h> 
#include<cmath> 
#include<fstream> 
#include<iostream> 
#include<vector> 
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
    std::vector<std::string> vectorsCoordsFromText;  
    std::vector<float> vectorCoords; 
    std::vector<std::string> faceIndicesFromText; 

    TGAImage framebuffer(width, height, TGAImage::RGB); 

    std::string diabloText; 

    std::ifstream diabloOBJ("C:/Coding/Rasterizer/res/objs/diablo3_pose.obj"); 

    while(std::getline(diabloOBJ, diabloText)){
        if(diabloText[0] == 'v' && diabloText[1] == ' '){ 
            vectorsCoordsFromText.push_back(diabloText); 
            std::cout << diabloText << std::endl; 
        }
        else if(diabloText[0] == 'f' && diabloText[1] == ' '){
            faceIndicesFromText.push_back(diabloText); 
            std::cout << diabloText << std::endl; 
        }
    }
    std::string s; 
    for(auto& v: vectorsCoordsFromText){
        for(int i = 0; i < v.length(); ++i){
            if(v[i] == 'v'){ 
                continue; 
            }else if(v[i] == ' '){
                if(!s.empty()){
                        std::cout << s << std::endl; 
                        vectorCoords.push_back(std::stof(s));  
                        s = ""; // Clear s for the next number
                    }
            }else{
                s += v[i]; 
            }
        }
        std::cout << s << std::endl; 
        vectorCoords.push_back(std::stof(s)); 
        s = ""; 
    }

    diabloOBJ.close(); 
    framebuffer.write_tga_file("framebuffer.tga"); 
    return 0; 
}