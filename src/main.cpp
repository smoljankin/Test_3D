#include <iostream>
#include "ObjParser.h"
#include "Renderer.h"

using namespace std;

int main()
{
    Model model;
    string path = "OBJ/triangle.obj";

    if (!ObjParser::load(path, model)) {
        cerr << "Failed to load model\n";
        return 1;
    }
    cout << "Faces loaded: " << model.faces.size() << endl;

    Renderer ren(700, 600);
    if (!ren.init()) {
        cerr << "SDL init failed\n";
        return 1;
    }

    ren.drawModel(model);
    ren.run();          // чекаємо закриття вікна

    return 0;
}