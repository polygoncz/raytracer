#include "import/xmlsceneimporter.h"

XmlSceneImporter::XmlSceneImporter(const char* path)
	: path(path)
{
	if (!doc.Load(path))
		throw exception("Nenacten soubor");

	root = doc.GetRoot();
	if (root->GetName() != "scene")
		throw exception("Nejedna se o soubor sceny");
}

XmlSceneImporter::~XmlSceneImporter()
{}

wxXmlNode* XmlSceneImporter::findNode(const wxXmlNode* parent, const char* name)
{
	if (parent)	{
		wxXmlNode* child = parent->GetChildren();
		while (child) {
			if (child->GetName() == name)
				return child;
			else
				child = child->GetNext();
		}
	}

	return NULL;
}

RGBColor XmlSceneImporter::getRGBFromNode(const wxXmlNode* node)
{
	if (node) {
		float r, g, b;
		r = getFloatAttrFromNode(node, "r");
		g = getFloatAttrFromNode(node, "g");
		b = getFloatAttrFromNode(node, "b");

		return RGBColor(r, g, b);
	} else return RGBColor();
}

template<typename T>
T XmlSceneImporter::getVectorTypeFromNode(const wxXmlNode* node)
{
	if (node) {
		float x, y, z;
		x = getFloatAttrFromNode(node, "x");
		y = getFloatAttrFromNode(node, "y");
		z = getFloatAttrFromNode(node, "z");

		return T(x, y, z);
	} else return T();
}

int XmlSceneImporter::getIntAttrFromNode(const wxXmlNode* node, const char* attr, int def_val /* = 0 */)
{
	if (node) {
		wxString defStr = wxString::Format("%i", def_val);
		return wxAtoi(node->GetAttribute(attr, defStr));
	} else return def_val;
}

float XmlSceneImporter::getFloatAttrFromNode(const wxXmlNode* node, const char* attr, float def_val /* = 0.f */)
{
	if (node) {
		wxString defStr = wxString::Format("%f", def_val);
		return static_cast<float>(wxAtof(node->GetAttribute(attr, "0.0")));
	} else return def_val;
}

RGBColor XmlSceneImporter::loadBackground(void)
{
	wxXmlNode* background = findNode(root, "background");

	RGBColor c = getRGBFromNode(background);
	return c;
}

Light* XmlSceneImporter::loadAmbient()
{
	wxXmlNode* node = findNode(root, "ambient");

	float intensity = getFloatAttrFromNode(node, "intensity");
	RGBColor c = getRGBFromNode(node);

	return new AmbientLight(intensity, c);
}

Film* XmlSceneImporter::loadFilm()
{
	wxXmlNode* node = findNode(root, "film");

	int w = getIntAttrFromNode(node, "width", 640);
	int	h = getIntAttrFromNode(node, "height", 480);
	float size = getFloatAttrFromNode(node, "size", 0.1f);
	float gamma = getFloatAttrFromNode(node, "gamma", 1.f);

	return new Film(w, h, size, gamma, 1.f / gamma);
}

Camera* XmlSceneImporter::loadCamera(Film* f)
{
	wxXmlNode* cameraNode = findNode(root, "camera");
	
	float d = getFloatAttrFromNode(cameraNode, "d");
	float exp = getFloatAttrFromNode(cameraNode, "exposure");

	Point eye = getVectorTypeFromNode<Point>(findNode(cameraNode, "eye"));
	Point target = getVectorTypeFromNode<Point>(findNode(cameraNode, "target"));
	Vector up = getVectorTypeFromNode<Vector>(findNode(cameraNode, "up"));

	return new PerspectiveCamera(eye, target, up, f, d, exp);
}

void XmlSceneImporter::loadLights(vector<Light*>& lights)
{
	wxXmlNode* lightsNode = findNode(root, "lights");

	if (lightsNode)	{
		wxXmlNode* lightNode = lightsNode->GetChildren();
		while (lightNode) {
			if (lightNode->GetName().Cmp("point") == 0) {
				float intesity = getFloatAttrFromNode(lightNode, "intensity");
				RGBColor c = getRGBFromNode(findNode(lightNode, "color"));
				Point p = getVectorTypeFromNode<Point>(findNode(lightNode, "position"));
				lights.push_back(new PointLight(intesity, c, p));
			}

			lightNode = lightNode->GetNext();
		}
	} else {
		throw exception("Nejsou svetla k nacteni");
	}
}

void XmlSceneImporter::loadModels(vector<Reference<Primitive> >& models)
{
	wxXmlNode* objects = findNode(root, "objects");

	if (objects) {
		wxXmlNode* object = objects->GetChildren();
		while (object) {
			if (object->GetName().Cmp("triangle_mesh") == 0) {
				wxString file = wxPathOnly(path);
				file += "/";
				file += object->GetAttribute("src");
				if (file.Cmp(wxPathOnly(path)) != 0) {
					ObjImporter imp;
					models.push_back(imp.LoadObj(file.mb_str(), new Matte(GREY, 0.1f, 0.9f)));
				}
			}

			object = object->GetNext();
		}
	} else {
		throw exception("Nejsou modely k nacteni");
	}
}

Agreggate* XmlSceneImporter::loadAggregate(vector<Reference<Primitive> >& models)
{
	wxXmlNode* agrNode = findNode(root, "aggregate");

	wxString type = agrNode->GetAttribute("type", "grid");

	if (type.Cmp("brute") == 0)	{
		return new BruteForce(models);
	} else {
		return new Grid(models);
	}
}