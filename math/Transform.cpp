#include "Transform.h"

bool Transform::Load(const rapidjson::Value& value)
{
	json::get_vector2(value, "position", translation);
	json::get_float(value, "rotation", rotation);
	json::get_vector2(value, "scale", scale);

	return true;
}

void Transform::Update()
{
	Matrix33 mxs;
	mxs.Scale(scale);

	Matrix33 mxr;
	mxr.Rotate(rotation);

	Matrix33 mxt;
	mxt.Translate(translation);

	// SRT - Scale Rotate Translate
	mxWorld = mxs * mxr * mxt;
}
