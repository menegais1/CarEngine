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
    std::string fileString;

    while (!file.eof()) {
        fileString.append(1, file.get());
    }
    FileString File = {fileString, 0, (int) fileString.length() - 1};

    ObjectInfo info;
    std::vector<dvec3> normals;
    std::vector<dvec3> uv;

    info.vertices = readVertices(File);
    info.uv = readTextureCoordinates(File);
    info.normals = readVerticesNormals(File);

    info.faces = readFaces(File);
    return info;
}

std::vector<dvec3> ModelLoader::readVertices(FileString &file) {
    std::string x, y, z;
    std::string s;
    std::vector<dvec3> vertices;
    while (true) {
        file.getLine(s, ' ');
        if (s.length() == 0)break;
        if (s.at(0) == '#' || s.at(0) == '\n') {
            file.getLine(s, '\n');
            continue;
        } else if (s != "v") {
            file.curPos -= s.length() + 1;
            break;
        }
        file.getLine(x, ' ');
        file.getLine(y, ' ');
        file.getLine(z, '\n');
        vertices.push_back(dvec3(std::stod(x), std::stod(y), std::stod(z)));
    }
    return vertices;
}

std::vector<dvec3> ModelLoader::readTextureCoordinates(FileString &file) {
    std::string x, y, z;
    std::string s;

    std::vector<dvec3> uv;
    while (true) {
        file.getLine(s, ' ');
        if (s.length() == 0)break;
        if (s.at(0) == '#' || s.at(0) == '\n') {
            file.getLine(s, '\n');
            continue;
        } else if (s != "vt") {
            file.curPos -= s.length() + 1;
            break;
        }
        file.getLine(x, ' ');
        file.getLine(y, '\n');
        uv.push_back(dvec3(std::stod(x), std::stod(y), 0));
    }

    return uv;
}

std::vector<dvec3> ModelLoader::readVerticesNormals(FileString &file) {
    std::string x, y, z;
    std::string s;
    std::vector<dvec3> normals;
    while (true) {
        file.getLine(s, ' ');
        if (s.length() == 0)break;
        if (s.at(0) == '#' || s.at(0) == '\n') {
            file.getLine(s, '\n');
            continue;
        } else if (s != "vn") {
            file.curPos -= s.length() + 1;
            break;
        }
        file.getLine(x, ' ');
        file.getLine(y, ' ');
        file.getLine(z, '\n');
        normals.push_back(dvec3(std::stod(x), std::stod(y), std::stod(z)));
    }
    return normals;
}

std::vector<ObjectFace> ModelLoader::readFaces(FileString &file) {
    std::string v0, v1, v2, vt0, vt1, vt2, vn0, vn1, vn2;
    std::string s;
    std::vector<ObjectFace> faces;
    while (!file.eof()) {
        file.getLine(s, ' ');
        if (s.length() == 0)break;
        if (s.at(0) == '#' || s.at(0) == '\n') {
            file.getLine(s, '\n');
            continue;
        } else if (s != "f") {
            file.curPos -= s.length() + 1;
            break;
        }
        file.getLine(v0, '/');
        file.getLine(vt0, '/');
        file.getLine(vn0, ' ');
        file.getLine(v1, '/');
        file.getLine(vt1, '/');
        file.getLine(vn1, ' ');
        file.getLine(v2, '/');
        file.getLine(vt2, '/');
        file.getLine(vn2, '\n');
        ivec3 vert = ivec3(std::stoi(v0) - 1, std::stoi(v1) - 1, std::stoi(v2) - 1);
        ivec3 texture = ivec3(std::stoi(vt0) - 1, std::stoi(vt1) - 1, std::stoi(vt2) - 1);
        ivec3 normals = ivec3(std::stoi(vn0) - 1, std::stoi(vn1) - 1, std::stoi(vn2) - 1);

        faces.push_back({vert, normals, texture});
    }
    return faces;
}