#pragma once

class Film
{
public:
    Film();
    Film(const Film& plane);
    Film(int width, int height, float size, float gamma = 1.0, float invGamma = 1.0);
    ~Film();
public:
    int width;
    int height;
    float size;
    float gamma;
    float invGamma;
};