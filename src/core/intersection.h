#pragma once

#include "core.h"

#include "constants.h"
#include "scene.h"
#include "geometry.h"
#include "material.h"

class Intersection
{
public:
    Intersection(Scene& _scene)
        :   scene(_scene),
        hitObject(false),
        material(NULL),
        depth(0),
        t(INFINITY) {}
    Intersection(const Intersection& sr)
        :   scene(sr.scene),
        hitObject(sr.hitObject),
        hitPoint(sr.hitPoint),
        normal(sr.normal),
        ray(sr.ray),
        material(sr.material),
        depth(sr.depth),
        t(sr.t) {}

public:
    Scene& scene;               //Reference on scene
    bool hitObject;             //Did ray hit object?
    Point hitPoint;             //Hitpoint in world coordinates
    Normal normal;              //Surface normal in hit point
    Ray ray;                    //Ray for computing specular highlights
    Material* material;        //Pointer to material of hitted object
    int depth;                  //Depth of recursion
    float t;                    //tmin
};