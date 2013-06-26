#include "viewplane.h"

Film::Film(int width, int height, float size, float gamma, float invGamma)
    : width(width), height(height), size(size), gamma(gamma), invGamma(1.f / gamma)
{}

Film::Film(const Film& plane)
    : width(plane.width), height(plane.height), size(plane.size), gamma(plane.gamma), invGamma(plane.invGamma)
{}

Film::~Film()
{}