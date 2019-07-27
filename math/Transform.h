#pragma once

#include "../core/Core.h"
//#include "vector2.h"
#include "Matrix33.h"

struct Transform {
	vector2 translation;
	float rotation;
	vector2 scale;
	vector2 position;

	Matrix33 mxWorld;

	Transform() {}
	Transform(vector2& translation, float rotation, vector2 scale, vector2 position) :
		translation(translation),
		rotation(rotation),
		scale(scale),
		position(position) {}

	bool Load(const rapidjson::Value& value);
	void Update();
};