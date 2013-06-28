#include "integrator.h"
#include <cstdlib>

Integrator::Integrator(Scene* scene)
	: scene(scene) {}

Integrator::Integrator(const Integrator& tr)
	: scene(tr.scene) {}

Integrator::~Integrator()
{}