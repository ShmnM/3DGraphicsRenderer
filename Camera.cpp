#include "Camera.h"

void Camera::setRotationMatrix(float scalar, float quaternionA, float quaternionB, float quaternionC) {
    float am = -1 * quaternionA;
    float bm = -1 * quaternionB;
    float cm = -1 * quaternionC;
    M[0] = 1-2*bm*bm-2*cm*cm;
    M[1] = 2*am*bm - 2*cm*scalar;
    M[2] = 2*am*cm + 2*bm*scalar;

    M[4] = 2*am*bm + 2*cm*scalar;
    M[5] = 1 - 2*am*am - 2*cm*cm;
    M[6] = 2*bm*cm - 2*am*scalar;

    M[8] = 2*am*cm - 2*bm*scalar;
    M[9] = 2*bm*cm + 2*am*scalar;
    M[10] = 1 - 2*am*am - 2*bm*bm;
    

}

void Camera::rotate(float r, float p, float y){
    float cr = cos(r*(M_PI/180)/2);
    float sr = sin(r*(M_PI/180)/2);
    float cp = cos(p*(M_PI/180)/2);
    float sp = sin(p*(M_PI/180)/2);
    float cy = cos(y*(M_PI/180)/2);
    float sy = sin(y*(M_PI/180)/2);
    float deltaS = cr*cp*cy + sr*sp*sy;
    float deltaA = sr*cp*cy - cr*sp*sy;
    float deltaB = cr*sp*cy + sr*cp*sy;
    float deltaC = cr*cp*sy - sr*sp*cy;
    float newS = s*deltaS - a*deltaA - b*deltaB - c*deltaC;
    float newA = s*deltaA + a*deltaS + b*deltaC - c*deltaB;
    float newB = s*deltaB - a*deltaC + b*deltaS + c*deltaA;
    float newC = s*deltaC + a*deltaB - b*deltaA + c*deltaS;
    s = newS; a = newA; b = newB; c = newC;
    setRotationMatrix(s, a, b, c);
};