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

constexpr int width = 980; 
constexpr int height = 980; 

void drawLine(int ax, int ay, int bx, int by, 
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

int main(int argc, char** argv){ 
    std::vector<std::string> vectorsCoordsFromText;  
    std::vector<float> vectorCoordsFloat; 
    std::vector<int> vectorCoordsInt; 

    std::vector<std::string> faceIndicesFromText; 
    std::vector<std::string> faceIndicesWithSlashes; 
    std::vector<int> faceIndicesInt; 
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
    diabloOBJ.close(); 

    std::string s; 
    for(auto& v: vectorsCoordsFromText){ 
        for(auto& vl: v){
            if(vl == 'v'){ 
                continue; 
            }else if(vl == ' '){
                if(!s.empty()){
                        std::cout << s << std::endl; 
                        vectorCoordsFloat.push_back(std::stof(s));  
                        s = ""; // Clear s for the next number
                    }
            }else{
                s += vl; 
            }
        }
        std::cout << s << std::endl; 
        vectorCoordsFloat.push_back(std::stof(s)); 
        s = ""; 
    } 
    for(auto& fs: faceIndicesFromText){
        for(auto& fl : fs){
            if(fl == 'f'){
                continue;
            }else if(fl == ' '){
                if(!s.empty()){
                    std::cout << s << std::endl; 
                    faceIndicesWithSlashes.push_back(s); 
                    s = ""; 
                }
            }else{
                s += fl; 
            }
        }
        std::cout << s << std::endl; 
        faceIndicesWithSlashes.push_back(s); 
        s = ""; 
    } 

    for(auto& f: faceIndicesWithSlashes){
        for(auto& fl: f){
            if(fl == '/'){
                std::cout << s << std::endl; 
                faceIndicesInt.push_back(std::stoi(s)); 
                s = ""; 
                break;
            }else{
                s += fl; 
            }
        }
    }

    int imod = 0;
    for(auto& v: vectorCoordsFloat){
        if(imod % 3 == 0){
            vectorCoordsInt.push_back(std::round(((v + 1) / 2) * width)); 
        }else if(imod % 3 == 1){
            vectorCoordsInt.push_back(std::round(((v + 1) / 2) * height)); 
        }
        imod += 1; 
    } 

    for (int i = 0; i < faceIndicesInt.size(); i += 3) {
        int idx0 = faceIndicesInt[i] - 1;
        int idx1 = faceIndicesInt[i + 1] - 1;
        int idx2 = faceIndicesInt[i + 2] - 1;

        // Look up the X and Y screen coordinates (* 2 for X, * 2 + 1 for Y)
        int x0 = vectorCoordsInt[idx0 * 2];
        int y0 = vectorCoordsInt[idx0 * 2 + 1];

        int x1 = vectorCoordsInt[idx1 * 2];
        int y1 = vectorCoordsInt[idx1 * 2 + 1];

        int x2 = vectorCoordsInt[idx2 * 2];
        int y2 = vectorCoordsInt[idx2 * 2 + 1];

        drawLine(x0, y0, x1, y1, framebuffer, red);
        drawLine(x1, y1, x2, y2, framebuffer, red);
        drawLine(x2, y2, x0, y0, framebuffer, red);
    } 

    for(int i = 0; i < vectorCoordsInt.size(); i += 2){
        framebuffer.set(vectorCoordsInt[i], vectorCoordsInt[i + 1], white); 
    }

    framebuffer.write_tga_file("diablo3PoseWireFrame.tga"); 
    return 0; 
}