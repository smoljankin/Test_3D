#include <iostream>
#include "ObjParser.h"

using namespace std;

int main()
{
    Model model;

    if (ObjParser::load("OBJ/triangle.obj", model)) {
        cout << "Faces: " << model.faces.size() << endl;
    }

    int x;
    cin >> x;
    return 0;
}