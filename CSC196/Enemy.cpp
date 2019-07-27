#include "Enemy.h"
#include "Scene.h"
#include "..//math/math.h"

#include "Game.h"

void Enemy::Update(float dt)
{
	Actor* target = m_scene->GetActorByName("Player");
	if (target) {
		vector2 direction = target->m_transform.translation - m_transform.translation;
		float angle = vector2::get_angle(direction);
		m_transform.rotation = angle - math::HALF_PI;
		vector2 forward = vector2::rotate(vector2::up, m_transform.rotation);
		m_transform.translation += forward * m_speed * dt;
	}

	vector2 forward = vector2::rotate(vector2::up, m_transform.rotation);
	m_transform.translation += forward - m_speed * dt;

	float distance = vector2::distance(target->m_transform.translation, m_transform.translation);
	if (distance <= 15) {
		int lives = m_scene->GetGame()->GetLives();
		m_scene->GetGame()->SetLives(lives - 1);
		
		std::vector<Actor*> actors = m_scene->GetActorsByTag("Missile");
		for (Actor* actor : actors) {
			actor->m_destroy = true;
		}

		actors = m_scene->GetActorsByTag("Enemy");
		for (Actor* actor : actors) {
			actor->m_destroy = true;
		}

		target->m_transform.translation.x = 400;
		target->m_transform.translation.y = 300;
	}
}

bool Enemy::Load(const rapidjson::Value& value)
{
	Actor::Load(value);

	json::get_float(value, "speed", m_speed);
	json::get_float(value, "rotate", m_rotate);

	return true;
}
