#pragma once
#include <string>
#include "Model.h"

class ObjParser {
public:
    static bool load(const std::string& filename, Model& model);

private:
    static void parseFaceVertex(
        const std::string& token,
        const std::vector<Vertex>& vertices,
        const std::vector<Normale>& normals,
        Vertex& outV,
        Normale& outN);
};