#include "SDL_Point3D.h"

SDL_Point3D::SDL_Point3D(float newX, float newY, float newZ) {
    x = newX;
    y = newY;
    z = newZ;
}

SDL_Point3D::SDL_Point3D(float newX, float newY, float newZ, SDL_Point3D* adjacency) {
    x = newX;
    y = newY;
    z = newZ;
    this->adjacency = adjacency; 
}

SDL_FPoint SDL_Point3D::toFpoint(float fov, int height, int width){
    float focal = (height/2.0)/(tan(fov/2.0));
    return SDL_FPoint{ (float)(((x/z)*focal) + (width/2.0)),(float)((height/2.0)-((y/z)*focal))};
}