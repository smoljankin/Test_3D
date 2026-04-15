#pragma once
#define SDL_MAIN_HANDLED 
#include <SDL.h>
#include "Model.h"

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();

    bool init();
    void drawModel(const Model& model);
    void run();

private:
    int width, height;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    void projectVertex(const Vertex& v, int& px, int& py,
        double scale, double offsetX, double offsetY);

    void drawLine(int x1, int y1, int x2, int y2);

    int  edgeX(int ax, int ay, int bx, int by, int y);

    void drawFilledTriangle(int x1, int y1,
        int x2, int y2,
        int x3, int y3);
};
