#include "Actor.h"

void Actor::Update(float dt)
{

}

void Actor::Draw(Core::Graphics& graphics)
{
	m_transform.Update();

	graphics.SetColor(m_color);
	for (size_t i = 0; i < m_vertices.size() - 1; i++) {
		vector2 v1 = m_vertices[i] * m_transform.mxWorld;
		vector2 v2 = m_vertices[i + 1] * m_transform.mxWorld;
		graphics.DrawLine(v1.x, v1.y, v2.x, v2.y);
	}
}

bool Actor::Load(const rapidjson::Value& value)
{
	json::get_string(value, "name", m_name);
	json::get_string(value, "tag", m_tag);
	
	const rapidjson::Value& tvalue = value["transform"];
	if (tvalue.IsObject()) {
		m_transform.Load(tvalue);
	}

	json::get_color(value, "color", m_color);
	const rapidjson::Value& vvalue = value["vertex"];
	if (vvalue.IsArray()) {
		json::get_vector2(vvalue, "v", m_vertices);
	}

	return false;
}
