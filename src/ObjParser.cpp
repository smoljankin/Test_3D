#include "ObjParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

bool ObjParser::load(const string& filename, Model& model) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Cannot open file\n";
        return false;
    }

    vector<Vertex> vertices;
    vector<Normale> normals;

    string line;

    while (getline(file, line)) {
        istringstream ss(line);
        string type;
        ss >> type;

        if (type == "v") {
            Vertex v;
            ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
        else if (type == "vn") {
            Normale n;
            ss >> n.x >> n.y >> n.z;
            normals.push_back(n);
        }
        else if (type == "f") {
            string t1, t2, t3;
            ss >> t1 >> t2 >> t3;

            Face f;

            parseFaceVertex(t1, vertices, normals, f.v1, f.vn1);
            parseFaceVertex(t2, vertices, normals, f.v2, f.vn2);
            parseFaceVertex(t3, vertices, normals, f.v3, f.vn3);

            model.faces.push_back(f);
        }
    }

    return true;
}

void ObjParser::parseFaceVertex(
    const string& token,
    const vector<Vertex>& vertices,
    const vector<Normale>& normals,
    Vertex& outV,
    Normale& outN)
{
    int vIndex = -1;
    int nIndex = -1;

    stringstream ss(token);
    string part;

    getline(ss, part, '/');
    vIndex = stoi(part) - 1;

    if (getline(ss, part, '/')) {
        if (!part.empty()) {
            if (getline(ss, part, '/')) {
                nIndex = stoi(part) - 1;
            }
        }
        else {
            if (getline(ss, part, '/')) {
                nIndex = stoi(part) - 1;
            }
        }
    }

    if (vIndex >= 0 && vIndex < (int)vertices.size())
        outV = vertices[vIndex];

    if (nIndex >= 0 && nIndex < (int)normals.size())
        outN = normals[nIndex];
    else
        outN = { 0, 0, 0 };
}