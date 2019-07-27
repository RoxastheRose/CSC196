#include "Player.h"
#include "Scene.h"

void Player::Warp(float dt)
{
	AudioSystem::Instance()->PlaySound("dash");
	vector2 dashPoint = vector2::rotate(vector2(0.0f, 1.0f), m_transform.rotation) * (m_speed * 75) * dt;
	m_transform.translation += dashPoint;
	m_dashUsed = true;
	m_dashCountDown = 5.0f;

}

void Player::Update(float dt)
{
	if (m_shootCountDown > 0.0f) {
		m_shootCountDown -= dt;
	}
	if (!(m_dashCountDown > 0.0f)) {
		m_dashUsed = false;
	}
	else {
		m_dashCountDown -= dt;
	}

	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { m_transform.rotation -= m_rotate * dt; }
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { m_transform.rotation += m_rotate * dt; }
	
	vector2 forward = vector2::rotate(vector2(0.0f, 1.0f), m_transform.rotation);
	if (Core::Input::IsPressed(Core::Input::KEY_SHIFT) && !m_dashUsed) {
		Warp(dt);
	} else if (Core::Input::IsPressed(Core::Input::KEY_UP))
	{
		m_transform.translation += forward * m_speed * dt;
	}

	if (Core::Input::IsPressed(Core::Input::KEY_SPACE) && m_shootCountDown <= 0.0f) {
		AudioSystem::Instance()->PlaySound("missile");
		Actor* actor = m_scene->GetActorFactory()->Create("Missile_Spawner");
		actor->m_transform.translation = m_transform.translation;
		actor->m_transform.rotation = m_transform.rotation;
		m_scene->AddActor(actor);
		m_shootCountDown = 0.2f;
	}

	// Screen Wrap
	if (m_transform.translation.x > 800.0f) m_transform.translation.x = 0.0f;
	if (m_transform.translation.x < 0.0f) m_transform.translation.x = 800.0f;
	if (m_transform.translation.y > 600.0f) m_transform.translation.y = 0.0f;
	if (m_transform.translation.y < 0.0f) m_transform.translation.y = 600.0f;
}

bool Player::Load(const rapidjson::Value& value)
{
	Actor::Load(value);

	json::get_float(value, "speed", m_speed);
	json::get_float(value, "rotate", m_rotate);

	return true;
}
