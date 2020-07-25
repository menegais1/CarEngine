//
// Created by menegais1 on 25/07/2020.
//

#ifndef CARENGINE_MODELLOADER_H
#define CARENGINE_MODELLOADER_H


#include <vector>
#include "../Vectors/Vector3.h"

struct ObjectInfo {
    std::vector<dvec3> vertices;
    std::vector<dvec3> normals;
    std::vector<dvec3> uv;
    std::vector<int> triangles;
};


class ModelLoader {
public:
    static ObjectInfo loadObj(std::string filename);

private:
    static std::vector<int> readFaces(std::ifstream &file);

    static std::vector<dvec3> readVerticesNormals(std::ifstream &file);

    static std::vector<dvec3> readVertices(std::ifstream &file);

    static std::vector<dvec3> readTextureCoordinates(std::ifstream &file);
};


#endif //CARENGINE_MODELLOADER_H
