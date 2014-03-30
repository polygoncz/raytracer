#pragma once

#ifndef XMLSCENEIMOPRTER_H
#define XMLSCENEIMOPRTER_H

#include <wx/xml/xml.h>
#include <wx/filefn.h>
#include <vector>
#include <exception>

#include "core/reference.h"
#include "core/primitive.h"
#include "core/light.h"
#include "ligths/ambient.h"
#include "cameras/perspective.h"
#include "agreggates/grid.h"
#include "agreggates/bruteforce.h"
#include "ligths/point.h"
#include "import/objimporter.h"
#include "materials/matte.h"

class Scene;
class Light;
class RGBColor;
class Agreggate;

class XmlSceneImporter
{
public:
	XmlSceneImporter(const char* path);
	~XmlSceneImporter();

	void LoadLights(vector<Light*>& lights);
	void LoadModels(vector<Reference<Primitive> >& models);
	RGBColor LoadBackground(void);
	Light* LoadAmbient(void);
	Film* LoadFilm(void);
	Camera* LoadCamera(Film* f);
	Agreggate* LoadAggregate(vector<Reference<Primitive> >& models);
	int LoadPerPixelSamples();
	int LoadNumberOfThreads();

private:
	wxXmlNode* FindNode(const wxXmlNode* parent, const char* name);
	RGBColor GetRGBFromNode(const wxXmlNode* node);

	template<typename T>
	T GetVectorTypeFromNode(const wxXmlNode* node);

	int GetIntAttrFromNode(const wxXmlNode* node, const char* attr, int def_val = 0);
	float GetFloatAttrFromNode(const wxXmlNode* node, const char* attr, float def_val = 0.f);
	Reference<Material> LoadMatte(const wxXmlNode* node);
	Reference<Material> LoadMaterial(const wxXmlNode* parent);
	Reference<Material> LoadPhong(const wxXmlNode* node);	

private:
	wxXmlDocument doc;
	wxXmlNode* root;
	wxString path;
};

#endif // !XMLSCENEIMOPRTER_H
