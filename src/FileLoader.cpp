//
// Created by menegais1 on 28/07/2020.
//

#include "FileLoader.h"

std::string FileLoader::getPath(std::string path) {
    #if CLION == 1
        return "../" + path;
    #endif
    #if CODEBLOCKS == 1
        return "CarEngine/" + path;
    #endif
    return "";
}
