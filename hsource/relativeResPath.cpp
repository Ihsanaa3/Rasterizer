#include"relativeResPath.h" 

namespace fs = std::filesystem;

std::string rrp::getParentDir() {
    return fs::current_path().parent_path().string();
}

std::string rrp::getResourcesPath() {
    return getParentDir() + "/res/";
}

std::string rrp::getFragmentPath() {
    return getResourcesPath() + "/fragment/";
}

std::string rrp::getTexturePath() {
    return getResourcesPath() + "/texture/";
}

std::string rrp::getVertexPath() {
    return getResourcesPath() + "/vertex/";
}

std::string rrp::getObjsPath(){
    return getResourcesPath() + "/objs/";
}