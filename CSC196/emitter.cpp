#include "emitter.h"
#include "scene.h"
#include "..\\particles\particle_system.h"

void Emitter::Update(float dt)
{
	m_spawn_timer = m_spawn_timer + dt;
	if (m_spawn_timer >= m_spawn_rate)
	{
		m_spawn_timer = 0.0f;

		float lifetime = g_random(m_lifetime_range[0], m_lifetime_range[1]);
		float velocity = g_random(m_velocity_range[0], m_velocity_range[1]);
		float angle = g_random(m_angle_range[0], m_angle_range[1]);

		color c = m_colors[g_random_int() % m_colors.size()];
		vector2 random_direction = vector2::rotate(vector2::up, m_transform.rotation + angle * math::DEG_TO_RAD);
		vector2 v = random_direction * velocity;

		m_scene->GetParticleSystem()->Create(m_transform.translation, v, c, m_damping, lifetime);

	}

	m_lifetime = m_lifetime - dt;

	if (m_lifetime <= 0.0f)
	{
		m_destroy = true;
	}
}

bool Emitter::Load(const rapidjson::Value& value)
{
	Actor::Load(value);

	json::get_float(value, "lifetime", m_lifetime);
	json::get_float(value, "spawn_rate", m_spawn_rate);

	json::get_vector2(value, "lifetime_range", m_lifetime_range);
	json::get_vector2(value, "velocity_range", m_velocity_range);
	json::get_vector2(value, "angle_range", m_angle_range);
	json::get_float(value, "damping", m_damping);

	const rapidjson::Value& color_value = value["colors"];
	if (color_value.IsArray())
	{
		json::get_color(color_value, "c", m_colors);
	}

	return true;
}