#include <iostream>
#include "ObjParser.h"

using namespace std;

int main()
{
    Model model;
    string path = "OBJ/triangle.obj";
    
    if (ObjParser::load(path, model)) {
        cout << "Faces: " << model.faces.size() << endl;
    }

    cin.get();
    return 0;
}