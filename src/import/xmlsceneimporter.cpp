#include "import/xmlsceneimporter.h"

#include "materials/phong.h"
#include "materials/mirror.h"
#include "materials/glass.h"

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

wxXmlNode* XmlSceneImporter::FindNode(const wxXmlNode* parent, const char* name)
{
	if (parent)
	{
		wxXmlNode* child = parent->GetChildren();
		while (child)
		{
			if (child->GetName() == name)
				return child;
			else
				child = child->GetNext();
		}
	}

	return NULL;
}

RGBColor XmlSceneImporter::GetRGBFromNode(const wxXmlNode* node, const RGBColor& def /*= BLACK*/)
{
	if (node)
	{
		float r, g, b;
		r = GetFloatAttrFromNode(node, "r");
		g = GetFloatAttrFromNode(node, "g");
		b = GetFloatAttrFromNode(node, "b");

		return RGBColor(r, g, b);
	}
	else return def;
}

template<typename T>
T XmlSceneImporter::GetVectorTypeFromNode(const wxXmlNode* node)
{
	if (node)
	{
		float x, y, z;
		x = GetFloatAttrFromNode(node, "x");
		y = GetFloatAttrFromNode(node, "y");
		z = GetFloatAttrFromNode(node, "z");

		return T(x, y, z);
	}
	else return T();
}

int XmlSceneImporter::GetIntAttrFromNode(const wxXmlNode* node, const char* attr, int def_val /* = 0 */)
{
	if (node)
	{
		wxString defStr = wxString::Format("%i", def_val);
		return wxAtoi(node->GetAttribute(attr, defStr));
	}
	else return def_val;
}

float XmlSceneImporter::GetFloatAttrFromNode(const wxXmlNode* node, const char* attr, float def_val /* = 0.f */)
{
	if (node)
	{
		wxString defStr = wxString::Format("%f", def_val);
		return static_cast<float>(wxAtof(node->GetAttribute(attr, "0.0")));
	}
	else return def_val;
}

RGBColor XmlSceneImporter::LoadBackground(void)
{
	wxXmlNode* background = FindNode(root, "background");

	RGBColor c = GetRGBFromNode(background);
	return c;
}

Light* XmlSceneImporter::LoadAmbient()
{
	wxXmlNode* node = FindNode(root, "ambient");

	float intensity = GetFloatAttrFromNode(node, "intensity");
	RGBColor c = GetRGBFromNode(node);

	return new AmbientLight(intensity, c);
}

Film* XmlSceneImporter::LoadFilm()
{
	wxXmlNode* node = FindNode(root, "film");

	int w = GetIntAttrFromNode(node, "width", 640);
	int	h = GetIntAttrFromNode(node, "height", 480);
	float size = GetFloatAttrFromNode(node, "size", 0.1f);
	float gamma = GetFloatAttrFromNode(node, "gamma", 1.f);

	return new Film(w, h, size, gamma, 1.f / gamma);
}

Camera* XmlSceneImporter::LoadCamera(Film* f)
{
	wxXmlNode* cameraNode = FindNode(root, "camera");
	
	float d = GetFloatAttrFromNode(cameraNode, "d");
	float exp = GetFloatAttrFromNode(cameraNode, "exposure");

	Point eye = GetVectorTypeFromNode<Point>(FindNode(cameraNode, "eye"));
	Point target = GetVectorTypeFromNode<Point>(FindNode(cameraNode, "target"));
	Vector up = GetVectorTypeFromNode<Vector>(FindNode(cameraNode, "up"));

	return new PerspectiveCamera(eye, target, up, f, d, exp);
}

void XmlSceneImporter::LoadLights(vector<Light*>& lights)
{
	wxXmlNode* lightsNode = FindNode(root, "lights");

	if (lightsNode)
	{
		wxXmlNode* lightNode = lightsNode->GetChildren();
		while (lightNode)
		{
			if (lightNode->GetName().Cmp("point") == 0)
			{
				float intesity = GetFloatAttrFromNode(lightNode, "intensity");
				RGBColor c = GetRGBFromNode(FindNode(lightNode, "color"));
				Point p = GetVectorTypeFromNode<Point>(FindNode(lightNode, "position"));
				lights.push_back(new PointLight(intesity, c, p));
			}

			lightNode = lightNode->GetNext();
		}
	}
	else throw exception("Nejsou svetla k nacteni");
}

void XmlSceneImporter::LoadModels(vector<Reference<Primitive> >& models)
{
	wxXmlNode* objects = FindNode(root, "objects");

	if (objects)
	{
		wxXmlNode* object = objects->GetChildren();
		while (object)
		{
			if (object->GetName().Cmp("triangle_mesh") == 0)
			{
				wxString file = wxPathOnly(path);
				file += "/";
				file += object->GetAttribute("src");
				if (file.Cmp(wxPathOnly(path)) != 0)
				{
					ObjImporter imp;
					models.push_back(imp.LoadObj(file.mb_str(), LoadMaterial(object)));
					//models.push_back(imp.LoadObj(file.mb_str(), Reference<Material>(new Glass())));
				}
			}

			if (object->GetName().Cmp("sphere") == 0)
			{
				//TODO
			}

			object = object->GetNext();
		}
	}
	else throw exception("Nejsou modely k nacteni");
}

Reference<Material> XmlSceneImporter::LoadMaterial(const wxXmlNode* parent)
{
	wxXmlNode* materialNode = FindNode(parent, "material");
	if (materialNode != NULL)
	{
		wxString type = materialNode->GetAttribute("type");
		if (type.Cmp("matte") == 0)
			return LoadMatte(materialNode);

		if (type.Cmp("phong") == 0)
			return LoadPhong(materialNode);

		if (type.Cmp("reflective") == 0)
			return LoadReflective(materialNode);

		if (type.Cmp("glass") == 0)
			return Reference<Material>(new Glass());
	}

	return Reference<Material>(new Matte(GREY, 0.2f, 0.8f));
}

Reference<Material> XmlSceneImporter::LoadMatte(const wxXmlNode* node)
{
	RGBColor baseColor = GetRGBFromNode(FindNode(node, "base_color"));
	float ca = GetFloatAttrFromNode(node, "c_ambient");
	float cd = GetFloatAttrFromNode(node, "c_diffuse");

	return Reference<Material>(new Matte(baseColor, ca, cd));
}

Reference<Material> XmlSceneImporter::LoadPhong(const wxXmlNode* node)
{
	RGBColor baseColor = GetRGBFromNode(FindNode(node, "base_color"));
	RGBColor specColor = GetRGBFromNode(FindNode(node, "specular_color"));
	float ca = GetFloatAttrFromNode(node, "c_ambient");
	float cd = GetFloatAttrFromNode(node, "c_diffuse");
	float exp = GetFloatAttrFromNode(node, "exp");

	return Reference<Material>(new Phong(baseColor, specColor, ca, cd, exp));
}

Reference<Material> XmlSceneImporter::LoadReflective(const wxXmlNode* node)
{
	RGBColor baseColor = GetRGBFromNode(FindNode(node, "base_color"));
	RGBColor specColor = GetRGBFromNode(FindNode(node, "specular_color"));
	RGBColor reflectiveColor = GetRGBFromNode(FindNode(node, "reflective_color"), baseColor);
	float ca = GetFloatAttrFromNode(node, "c_ambient");
	float cd = GetFloatAttrFromNode(node, "c_diffuse");
	float cr = GetFloatAttrFromNode(node, "c_reflectance");
	float exp = GetFloatAttrFromNode(node, "exp");

	return Reference<Material>(new ReflectivePhong(baseColor, specColor, reflectiveColor, ca, cd, cr, exp));
}

Agreggate* XmlSceneImporter::LoadAggregate(vector<Reference<Primitive> >& models)
{
	wxXmlNode* agrNode = FindNode(root, "aggregate");

	wxString type = agrNode->GetAttribute("type", "grid");

	if (type.Cmp("brute") == 0)	{
		return new BruteForce(models);
	} else {
		return new Grid(models);
	}
}

int XmlSceneImporter::LoadPerPixelSamples()
{
	wxXmlNode* raytracerNode = FindNode(root, "renderer");

	return GetIntAttrFromNode(raytracerNode, "aa_samples", 1);
}

int XmlSceneImporter::LoadNumberOfThreads()
{
	wxXmlNode* raytracerNode = FindNode(root, "renderer");

	return GetIntAttrFromNode(raytracerNode, "num_threads", 1);
}