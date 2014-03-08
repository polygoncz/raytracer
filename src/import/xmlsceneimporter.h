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

	void loadLights(vector<Light*>& lights);
	void loadModels(vector<Reference<Primitive> >& models);
	RGBColor loadBackground(void);
	Light* loadAmbient(void);
	Film* loadFilm(void);
	Camera* loadCamera(Film* f);
	Agreggate* loadAggregate(vector<Reference<Primitive> >& models);

private:
	wxXmlNode* findNode(const wxXmlNode* parent, const char* name);
	RGBColor getRGBFromNode(const wxXmlNode* node);

	template<typename T>
	T getVectorTypeFromNode(const wxXmlNode* node);

	int getIntAttrFromNode(const wxXmlNode* node, const char* attr, int def_val = 0);
	float getFloatAttrFromNode(const wxXmlNode* node, const char* attr, float def_val = 0.f);

private:
	wxXmlDocument doc;
	wxXmlNode* root;
	wxString path;
};

#endif // !XMLSCENEIMOPRTER_H
