#pragma once

#include <filesystem>
#include <string>

namespace rrp{
    std::string getParentDir();  
    
    std::string getResourcesPath();  

    std::string getFragmentPath();  

    std::string getTexturePath();  

    std::string getVertexPath();  

    std::string getObjsPath(); 
}