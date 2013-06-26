#pragma once

#include "core.h"
#include "wxgui/imagebuffer.h"
#include <vector>

#include "light.h"
#include "color.h"
#include "integrator.h"
#include "film.h"
#include "camera.h"

using namespace std;

class Scene
{
public:
    Scene();
    Scene(RenderThread* pixelArea);
    ~Scene();

    void build();
    void render();

private:
    void addObject(Primitive* obj);
    void addLight(Light* light);
    void displayPixel(int x, int y, RGBColor& color);

public:
    RGBColor background;
    Light* ambient;
    vector<Light*> lights;
    vector<Primitive*> objects;
    RenderThread* pixelArea;
    Film* film;
	Camera* cam;
private:
    Integrator* tracer;
};