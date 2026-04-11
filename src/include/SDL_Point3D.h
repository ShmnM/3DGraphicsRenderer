#ifndef SDL_Point3D_H
#define SDL_Point3D_H
#include <SDL3/SDL_rect.h>
#include <cmath>

typedef struct SDL_Point3D : public SDL_FPoint {
    float z;
    SDL_Point3D* adjacency = nullptr;
    SDL_Point3D(){z = 1;};
    SDL_Point3D(float x, float y, float z);
    SDL_Point3D(float x, float y, float z, SDL_Point3D* next);
    SDL_FPoint toFpoint(float fovRad, int height, int width);
} SDL_Point3D;

#endif
