#include "Renderer.h"
#include <algorithm>
#include <cfloat>

Renderer::Renderer(int w, int h) : width(w), height(h) {}

Renderer::~Renderer() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window)   SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Renderer::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;
    window = SDL_CreateWindow("OBJ Viewer", 100, 100,
        width, height, 0);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED);
    return renderer != nullptr;
}

void Renderer::projectVertex(const Vertex& v,
    int& px, int& py,
    double scale,
    double offsetX, double offsetY)
{
    px = static_cast<int>(v.x * scale + offsetX);
    py = static_cast<int>(-v.y * scale + offsetY);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        SDL_RenderDrawPoint(renderer, x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

int Renderer::edgeX(int ax, int ay, int bx, int by, int y) {
    if (ay == by) return ax;
    return ax + (bx - ax) * (y - ay) / (by - ay);
}


void Renderer::drawFilledTriangle(int x1, int y1,
    int x2, int y2,
    int x3, int y3)
{
    if (y1 > y2) { std::swap(x1, x2); std::swap(y1, y2); }
    if (y1 > y3) { std::swap(x1, x3); std::swap(y1, y3); }
    if (y2 > y3) { std::swap(x2, x3); std::swap(y2, y3); }

    for (int y = y1; y <= y2; y++) {
        int xa = edgeX(x1, y1, x3, y3, y);
        int xb = edgeX(x1, y1, x2, y2, y);
        if (xa > xb) std::swap(xa, xb);
        drawLine(xa, y, xb, y);
        SDL_RenderPresent(renderer);
        SDL_Delay(15);
    }

    for (int y = y2; y <= y3; y++) {
        int xa = edgeX(x1, y1, x3, y3, y);
        int xb = edgeX(x2, y2, x3, y3, y);
        if (xa > xb) std::swap(xa, xb);
        drawLine(xa, y, xb, y);
        SDL_RenderPresent(renderer);
        SDL_Delay(15);
    }
}


void Renderer::drawModel(const Model& model) {
    if (model.faces.empty()) return;

    double minX = DBL_MAX, maxX = -DBL_MAX;
    double minY = DBL_MAX, maxY = -DBL_MAX;

    for (const auto& f : model.faces) {
        for (const Vertex* v : { &f.v1, &f.v2, &f.v3 }) {
            minX = std::min(minX, v->x);  maxX = std::max(maxX, v->x);
            minY = std::min(minY, v->y);  maxY = std::max(maxY, v->y);
        }
    }

    double rangeX = maxX - minX;
    double rangeY = maxY - minY;
    double range = std::max(rangeX, rangeY);
    if (range == 0) range = 1.0;

    double padding = 0.10;
    double scale = width * (1.0 - 2 * padding) / range;

    double modelCX = (minX + maxX) / 2.0;
    double modelCY = (minY + maxY) / 2.0;
    double offsetX = width / 2.0 - modelCX * scale;     
    double offsetY = height / 2.0 + modelCY * scale; 

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 220, 50, 50, 255); 

    for (const auto& face : model.faces) {
        int px1, py1, px2, py2, px3, py3;
        projectVertex(face.v1, px1, py1, scale, offsetX, offsetY);
        projectVertex(face.v2, px2, py2, scale, offsetX, offsetY);
        projectVertex(face.v3, px3, py3, scale, offsetX, offsetY);

        drawFilledTriangle(px1, py1, px2, py2, px3, py3);
    }
}


void Renderer::run() {
    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT) running = false;
    }
}