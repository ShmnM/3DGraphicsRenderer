#ifndef CAMERA_H
#define CAMERA_H
#include <cmath>
class Camera{
    public:
        //quaternions to avoid gimbal lock
        float x, y, z, s = 1, a = 0, b = 0, c = 0, roll, pitch, yaw;
        float M[16] = { 1.0, 0, 0, 0, 
                        0, 1.0, 0, 0, 
                        0, 0, 1.0, 0, 
                        0, 0, 0, 1 };
        /*
        0  1  2  3
        4  5  6  7
        8  9  10 11
        12 13 14 15
        */
        double fov = 90; 
        float fovRad = fov*(M_PI/180);
        Camera(){};
        Camera(float xss, float yee, float zed){x = xss; y = yee; z = zed;};
        Camera(float xss, float yee, float zed, double r, double p, double y){x = xss; y = yee; z = zed; roll = r; pitch = p; yaw = y;};
        void translate(float xss, float yee, float zed){x += xss; y += yee; z += zed;};
        void setPosition(float xss, float yee, float zed){x = xss; y = yee; z = zed;};
        void rotate(float r, float p, float y);
        void setRotation(float r, float p, float y);
        void changeFov(double newFov){fov = newFov;};
        void setRotationMatrix(float scalar, float quaternionA, float quaternionB, float quaternionC);
};

#endif