#include "materials/mirror.h"

#include "brdf/reflection.h"
#include "brdf/lambert.h"
#include "brdf/flat.h"
#include "brdf/specular.h"

ReflectivePhong::ReflectivePhong(const RGBColor& baseColor, const RGBColor& specularColor, 
			   float ca, float cd, float cr, float exp)
	: cr(cr), reflectionColor(baseColor), 
	  Phong(baseColor, specularColor, ca, cd, exp)
{}

ReflectivePhong::ReflectivePhong(const RGBColor& baseColor, const RGBColor& specularColor, 
			   const RGBColor& reflectionColor, float ca, float cd, float cr, float exp)
	: cr(cr), reflectionColor(reflectionColor),
	  Phong(baseColor, specularColor, ca, cd, exp)
{}

ReflectivePhong::ReflectivePhong(const ReflectivePhong& mat)
	: cr(mat.cr), reflectionColor(mat.reflectionColor),
	  Phong(mat.baseColor, mat.specularColor, mat.ca, mat.cd, mat.exp)
{}

Material* ReflectivePhong::Clone() const
{
	return new ReflectivePhong(*this);
}

BSDF* ReflectivePhong::GetBSDF(const Vector& normal, const Vector& incident) const
{
	BSDF* bsdf = new BSDF();

	bsdf->Add(new Ambient(baseColor * ca));
	bsdf->Add(new Lambert(cd, baseColor));
	bsdf->Add(new Specular(exp, specularColor));
	bsdf->Add(new Reflection(reflectionColor * cr));

	return bsdf;
}