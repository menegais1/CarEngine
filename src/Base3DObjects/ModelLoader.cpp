//
// Created by menegais1 on 25/07/2020.
//

#include <fstream>
#include <iostream>
#include "ModelLoader.h"
#include "../Vectors/Vector3.h"


ObjectInfo ModelLoader::loadObj(std::string filename) {
    std::ifstream file(filename, std::ios::in);
    if (file.is_open()) std::cout << "open" << std::endl;
    else std::cout << "error" << std::endl;

    ObjectInfo info;
    std::vector<dvec3> normals;
    std::vector<dvec3> uv;

    info.vertices = readVertices(file);
    uv = readTextureCoordinates(file);
    normals = readVerticesNormals(file);
    std::vector<ObjectFace> faces = readFaces(file);

    for (int i = 0; i < faces.size(); ++i) {
        info.triangles.push_back(faces[i].vertices[0]);
        info.triangles.push_back(faces[i].vertices[1]);
        info.triangles.push_back(faces[i].vertices[2]);
        info.normals.push_back(normals[faces[i].normals[0]]);
        info.normals.push_back(normals[faces[i].normals[1]]);
        info.normals.push_back(normals[faces[i].normals[2]]);
        info.uv.push_back(uv[faces[i].uv[0]]);
        info.uv.push_back(uv[faces[i].uv[1]]);
        info.uv.push_back(uv[faces[i].uv[2]]);
    }
    return info;
}

std::vector<dvec3> ModelLoader::readVertices(std::ifstream &file) {
    std::string x, y, z;
    std::string s;

    std::vector<dvec3> vertices;
    while (true) {
        file >> s;
        if (s.length() == 0)break;
        if (s.at(0) == '#' || s.at(0) == '\n') {
            std::getline(file, s);
            continue;
        } else if (s != "v") {
            file.seekg(-s.size(), std::ios::cur);
            break;
        }
        file >> x;
        file >> y;
        file >> z;
        vertices.push_back(dvec3(std::stod(x), std::stod(y), std::stod(z)));
    }
    return vertices;
}

std::vector<dvec3> ModelLoader::readTextureCoordinates(std::ifstream &file) {
    std::string x, y, z;
    std::string s;
    std::vector<dvec3> uv;
    while (true) {
        file >> s;
        if (s.length() == 0)break;
        if (s.at(0) == '#' || s.at(0) == '\n') {
            std::getline(file, s);
            continue;
        } else if (s != "vt") {
            file.seekg(-s.size(), std::ios::cur);
            break;
        }
        file >> x;
        file >> y;
        uv.push_back(dvec3(std::stod(x), std::stod(y), 0));
    }
    return uv;
}

std::vector<dvec3> ModelLoader::readVerticesNormals(std::ifstream &file) {
    std::string x, y, z;
    std::string s;
    std::vector<dvec3> normals;
    while (true) {
        file >> s;
        if (s.length() == 0)break;
        if (s.at(0) == '#' || s.at(0) == '\n') {
            std::getline(file, s);
            continue;
        } else if (s != "vn") {
            file.seekg(-s.size(), std::ios::cur);
            break;
        }
        file >> x;
        file >> y;
        file >> z;
        normals.push_back(dvec3(std::stod(x), std::stod(y), std::stod(z)));
    }
    return normals;
}

std::vector<ObjectFace> ModelLoader::readFaces(std::ifstream &file) {
    std::string v0, v1, v2, vt0, vt1, vt2, vn0, vn1, vn2;
    std::string s;
    std::vector<ObjectFace> faces;
    while (!file.eof()) {
        std::getline(file, s, ' ');
        if (s.length() == 0)break;
        if (s.at(0) == '#' || s.at(0) == '\n') {
            std::getline(file, s);
            continue;
        } else if (s != "f") {
            file.seekg(-s.size(), std::ios::cur);
            break;
        }
        std::getline(file, v0, '/');
        std::getline(file, vt0, '/');
        std::getline(file, vn0, ' ');
        std::getline(file, v1, '/');
        std::getline(file, vt1, '/');
        std::getline(file, vn1, ' ');
        std::getline(file, v2, '/');
        std::getline(file, vt2, '/');
        std::getline(file, vn2, '\n');
        ivec3 vert = ivec3(std::stoi(v0) - 1, std::stoi(v1) - 1, std::stoi(v2) - 1);
        ivec3 texture = ivec3(std::stoi(vt0) - 1, std::stoi(vt1) - 1, std::stoi(vt2) - 1);
        ivec3 normals = ivec3(std::stoi(vn0) - 1, std::stoi(vn1) - 1, std::stoi(vn2) - 1);

        faces.push_back({vert, normals, texture});
    }
    return faces;
}
