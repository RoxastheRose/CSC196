#pragma once

#include "..//core/Core.h"
#include "..//math/Transform.h"
#include "..//renderer/color.h"
#include "..//external/core/include/core.h"

class Scene;

class Actor {
public:
	Actor() {}
	virtual ~Actor() {}

	virtual void Update(float dt);
	virtual void Draw(Core::Graphics& graphics);

	virtual bool Load(const rapidjson::Value& value);

	void SetScene(Scene* scene) { m_scene = scene; }
	const std::string& GetName() { return m_name; }
	const std::string& GetTag() { return m_tag; }
	virtual Actor* Clone() { return new Actor(*this); }

public:
	bool m_destroy = false;
	Transform m_transform;
	std::string m_name;
	std::string m_tag;
	float m_rotate;
	Scene* m_scene;
	color m_color;
	std::vector<vector2> m_vertices;
};