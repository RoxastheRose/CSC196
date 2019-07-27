#include "Json.h"
#include "filesystem.h"
#include <iostream>

bool json::load(const char* filename, rapidjson::Document& document)
{
	bool result = false;

	char* buffer;
	size_t size;
	
	if (filesystem::read_file(filename, (void**)& buffer, size)) {
		buffer[size - 1] = 0;
		std::cout << buffer << std::endl;
		document.Parse(buffer);
		result = document.IsObject();

		filesystem::free_file(buffer);
	}

	return result;
}

bool json::get_int(const rapidjson::Value& value, const char* property_name, int& _int)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsInt()) {
		return false;
	}

	_int = property.GetInt();

	return true;
}

bool json::get_float(const rapidjson::Value& value, const char* property_name, float& _float)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsDouble()) {
		return false;
	}

	_float = property.GetFloat();

	return true;
}

bool json::get_string(const rapidjson::Value& value, const char* property_name, std::string& _string)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsString()) {
		return false;
	}

	_string = property.GetString();

	return true;
}

bool json::get_bool(const rapidjson::Value& value, const char* property_name, bool& _bool)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsBool()) {
		return false;
	}

	_bool = property.GetBool();

	return true;
}


bool json::get_vector2(const rapidjson::Value& value, const char* property_name, vector2& _vector2)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsArray() || property.Size() != 2) {
		return false;
	}

	for (rapidjson::SizeType i = 0; i < 2; i++) {
		if (!property[i].IsDouble()) {
			return false;
		}

		_vector2.x = property[0].GetFloat();
		_vector2.y = property[1].GetFloat();
	}
	return true;
}

bool json::get_vector2(const rapidjson::Value& value, const char* property_name, std::vector<vector2>& _vector2)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		
		const rapidjson::Value& vertex = value[i];
		if (vertex.IsObject()) {
			vector2 v2;
			get_vector2(vertex, property_name, v2);
			_vector2.push_back(v2);
		}
	}

	return true;
}

bool json::get_color(const rapidjson::Value& value, const char* property_name, color& color)
{
	auto iter = value.FindMember(property_name);
	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsArray() || property.Size() != 3) {
		return false;
	}

	for (rapidjson::SizeType i = 0; i < 3; i++) {
		if (!property[i].IsDouble()) {
			return false;
		}

		color.r = property[0].GetFloat();
		color.g = property[1].GetFloat();
		color.b = property[2].GetFloat();
	}
	return true;
}

bool json::get_color(const rapidjson::Value& value, const char* property_name, std::vector<color>& _colors) {
	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& color_value = value[i];
		if (color_value.IsObject()) {
			color c;
			get_color(color_value, property_name, c);
			_colors.push_back(c);
		}
	}

	return false;
 }