#include<tgaimage.h> 
#include"extraFunctions.h" 
#include<cmath> 
#include<chrono>

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255}; 

// int diagonalDistance(int width, int height){
//     //          USED FOR drawLine1 
//     return std::ceil(std::sqrt(width * width + height * height)); 
// }

// void drawLine1(int ax, int ay, int bx, int by, int width, int height,
//         TGAImage &framebuffer, TGAColor col = {255, 255, 255, 255})
// {
//     // First attempt, the simplest approach 
//     int noIntervals = diagonalDistance(width, height); 
//     for(float t = 0; t < 1.0f; t += (1.0f / noIntervals)){
//         int x = std::round(ax + t * (bx - ax)); 
//         int y = std::round(ay + t * (by - ay)); 

//         framebuffer.set(x, y, col); 
//     }
// } 

// void drawLine2(int ax, int ay, int bx, int by, 
//     TGAImage &framebuffer, TGAColor col)
// {
//     // Second approach, uses t as a function of x instead of x as a function of t 
//     bool isSteep = std::abs(ax - bx) < std::abs(ay - by); 
//     if(isSteep){ 
//         // transposes steep lines so that it draws it for every y instead of x 
//         std::swap(ax, ay); 
//         std::swap(bx, by); 
//     }
//     if(ax > bx){
//         // ensures that it is able to draw all lines from left to right 
//         std::swap(ax, bx); 
//         std::swap(ay, by); 
//     }
    
//     for(int x = ax; x <= bx; x++){
//         float t =  (x - ax) / static_cast<float>(bx - ax); 
//         int y = std::round(ay + t * (by - ay)); 
//         if(!isSteep){
//             framebuffer.set(x, y, col); 
//         }else{
//             framebuffer.set(y, x, col); 
//         }
//     }
// }

void drawLine3(int ax, int ay, int bx, int by, 
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
    // 1. Record the start time
    auto start = std::chrono::high_resolution_clock::now();
    
    rd::randseed(); 
    constexpr int width = 640; 
    constexpr int height = 640; 
    TGAImage framebuffer(width, height, TGAImage::RGB); 

    int ax =  70, ay =  30;
    int bx = 120, by = 370;
    int cx = 620, cy = 530;

    // framebuffer.set(ax, ay, white);                                 // points
    // framebuffer.set(bx, by, white); 
    // framebuffer.set(cx, cy, white); 

    // drawLine1(ax, ay, bx, by, width, height, framebuffer, red);     // first attempt 
    // drawLine1(ax, ay, cx, cy, width, height, framebuffer, blue);     
    // drawLine1(cx, cy, ax, ay, width, height, framebuffer, yellow);  
    // drawLine1(cx, cy, bx, by, width, height, framebuffer, green); 

    // drawLine2(ax, ay, bx, by, framebuffer, red);      // second attempt
    // drawLine2(ax, ay, cx, cy, framebuffer, blue);     
    // drawLine2(cx, cy, ax, ay, framebuffer, yellow);  
    // drawLine2(cx, cy, bx, by, framebuffer, green); 

    for (int i = 0; i < 1.6e6; ++i){
        drawLine3(rd::randInt(width), rd::randInt(height), 
                rd::randInt(width), rd::randInt(height), framebuffer, 
                {   static_cast<uint8_t>(rd::randInt(255)),
                    static_cast<uint8_t>(rd::randInt(255)),
                    static_cast<uint8_t>(rd::randInt(255)),
                    static_cast<uint8_t>(rd::randInt(255))
                }); 
        }

    // 2. Record the end time
    auto end = std::chrono::high_resolution_clock::now();

    // 3. Calculate the duration in milliseconds
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    // Or in seconds (as a floating-point number for decimal precision)
    std::chrono::duration<double> duration_sec = end - start;

    // 4. Output the results
    std::cout << "Execution time: " << duration_ms << " ms" << std::endl;
    std::cout << "Execution time: " << duration_sec.count() << " seconds" << std::endl;

    framebuffer.write_tga_file("framebuffer.tga");  
    return 0; 
}
