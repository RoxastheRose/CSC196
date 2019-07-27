#pragma once

#include "actor.h"

class Emitter : public Actor
{
public:
	Emitter() {}
	virtual ~Emitter() {}

	const char* GetType() { return "Emitter"; }

	void Update(float dt) override;
	void Draw(Core::Graphics& graphics) override {}

	virtual bool Load(const rapidjson::Value& value);

	virtual Emitter* Clone() { return new Emitter(*this); }

private:
	float m_lifetime = 2.0f;
	float m_spawn_rate = 0.0f;
	float m_spawn_timer = 0.0f;

	vector2 m_lifetime_range;
	vector2 m_velocity_range;
	vector2 m_angle_range;

	float m_damping;
	std::vector<color> m_colors;

};