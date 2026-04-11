#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include <list>
#include "Camera.h"
#include "SDL_Point3D.h"

const int WINDOW_HEIGHT = 1080;
const int WINDOW_WIDTH = 1920;
const float sensitivity = 0.1f;

void draw3DPoints(SDL_Renderer* myRenderer, SDL_Point3D* myPoints, int numPoints, Camera camera, int red = 255, int green = 0, int blue = 0, int alpha = 255){ 

    SDL_Point3D points[numPoints]; 
    SDL_Point3D finalPoints[numPoints];
    SDL_FPoint pointsToDraw[numPoints];
    int renderedPoints = 0;
    for(int i = 0; i < numPoints; i++){ 
        points[i].x = myPoints[i].x - camera.x;
        points[i].y = myPoints[i].y - camera.y; 
        points[i].z = myPoints[i].z - camera.z;
        finalPoints[i].x = 
            camera.M[0]*points[i].x + 
            camera.M[1]*points[i].y + 
            camera.M[2]*points[i].z;
        finalPoints[i].y =  
            camera.M[4]*points[i].x + 
            camera.M[5]*points[i].y + 
            camera.M[6]*points[i].z; 
        finalPoints[i].z =  
            camera.M[8]*points[i].x + 
            camera.M[9]*points[i].y + 
            camera.M[10]*points[i].z;
        if(finalPoints[i].z > 0.01){ //z clipping
            pointsToDraw[renderedPoints] = finalPoints[i].toFpoint(camera.fovRad, WINDOW_HEIGHT, WINDOW_WIDTH);
            renderedPoints++;
        }
    }
    
        
    

    SDL_SetRenderDrawColor(myRenderer, red, green, blue, alpha);
    for (int i = 0; i < renderedPoints - 1; i++) {
        SDL_RenderLine(myRenderer, pointsToDraw[i].x, pointsToDraw[i].y, pointsToDraw[i+1].x,   pointsToDraw[i+1].y);
    }
    SDL_RenderLine(myRenderer, pointsToDraw[renderedPoints - 1].x, pointsToDraw[renderedPoints - 1].y, pointsToDraw[0].x, pointsToDraw[0].y);
}


int main(int argv, char** args){
    //input initialize
    
    const bool* state = SDL_GetKeyboardState(NULL);
    srand (time(NULL));
    bool quit = false;
    SDL_Event e;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    

    //window initialization 
    std::string title = "test";
    char *displayTitle = &title[0];
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (SDL_CreateWindowAndRenderer(displayTitle, WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) == 0) {
        printf("Window and renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    SDL_SetWindowRelativeMouseMode(window, true);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Point3D PointArray[] = {
    {1,  1,  1},
    {2, 1,  1},
    {2,  2, 1},
    {1, 2, 1},
    {1,  1,  2},
    {2, 1,  2},
    {2,  2, 2},
    {1, 2, 2}
    };
    int faces[6][4] = {
    {0, 1, 2, 3}, // front
    {4, 5, 6, 7}, // back
    {0, 3, 7, 4}, // left
    {1, 2, 6, 5}, // right
    {0, 1, 5, 4}, // bottom
    {3, 2, 6, 7}  // top
    };
    Camera camera(0,0,0);
    while (!quit) {
        if (state[SDL_SCANCODE_ESCAPE]) { 
            quit = true;
        }
        if (state[SDL_SCANCODE_A]){        
            camera.x -= camera.M[0] * 0.10;
            camera.y -= camera.M[1] * 0.10;
            camera.z -= camera.M[2] * 0.10;
        }
        if (state[SDL_SCANCODE_D]){
            camera.x += camera.M[0] * 0.10;
            camera.y += camera.M[1] * 0.10;
            camera.z += camera.M[2] * 0.10;
        }
        if (state[SDL_SCANCODE_SPACE]){
            camera.x += camera.M[4] * 0.10;
            camera.y += camera.M[5] * 0.10;
            camera.z += camera.M[6] * 0.10;
        }  
        if (state[SDL_SCANCODE_K]){
            camera.x -= camera.M[4] * 0.10;
            camera.y -= camera.M[5] * 0.10;
            camera.z -= camera.M[6] * 0.10;
        }
        if (state[SDL_SCANCODE_W]){
            camera.x += camera.M[8] * 0.10;
            camera.y += camera.M[9] * 0.10;
            camera.z += camera.M[10] * 0.10;
        }
        if (state[SDL_SCANCODE_S]){
            camera.x -= camera.M[8] * 0.10;
            camera.y -= camera.M[9] * 0.10;
            camera.z -= camera.M[10] * 0.10;
        }
        if (state[SDL_SCANCODE_Q]){
            camera.rotate(0,0,1);
        }
        if (state[SDL_SCANCODE_E]){
            camera.rotate(0,0,-1);
        }
        //close and minimize button
        while (SDL_PollEvent(&e) != 0) { 
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_WINDOW_MINIMIZED) {
                SDL_MinimizeWindow(window);
            }
            else if (e.type == SDL_EVENT_MOUSE_MOTION) {
                camera.rotate(e.motion.yrel * sensitivity, e.motion.xrel * sensitivity, 0);
            }
        }
    

    

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        int r = 0;
        int g = 255;
        int b = 0;
        int a = 255;
        for(int i = 0; i < 6; i++){
            SDL_Point3D facePoints[4];
            for(int j = 0; j < 4; j++){
                facePoints[j] = PointArray[faces[i][j]];
            }
            if(r == 255){r = 0; b = 255;}
            else if(b == 255){b = 0; g = 255;}
            else if(g == 255){g = 0; r = 128; b = 128;}
            else if(b == 128){b = 0; g = 128;}
            else if(r == 128){r = 0; b = 128;}
            else if(g == 128){g = 0; b = 0; r = 255;}
            SDL_Point3D fillShape[2];
            float incrementx1 = (facePoints[3].x - facePoints[0].x)/500;
            float incrementy1 = (facePoints[3].y - facePoints[0].y)/500;
            float incrementz1 = (facePoints[3].z - facePoints[0].z)/500;
            float incrementx2 = (facePoints[2].x - facePoints[1].x)/500;
            float incrementy2 = (facePoints[2].y - facePoints[1].y)/500;
            float incrementz2 = (facePoints[2].z - facePoints[1].z)/500;
            for(int i = 0; i < 500; i++){
                fillShape[0].x = facePoints[0].x + incrementx1*i;
                fillShape[0].y = facePoints[0].y + incrementy1*i;
                fillShape[0].z = facePoints[0].z + incrementz1*i;
                fillShape[1].x = facePoints[1].x + incrementx2*i;
                fillShape[1].y = facePoints[1].y + incrementy2*i;
                fillShape[1].z = facePoints[1].z + incrementz2*i;
                draw3DPoints(renderer, fillShape, 2, camera, r, g, b, a);
            }
            draw3DPoints(renderer, facePoints, 4, camera, r, g, b, a);
            
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
        
        


    }

    //clear resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}