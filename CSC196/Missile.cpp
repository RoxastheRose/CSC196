#include "Missile.h"
#include "Scene.h"
#include "Game.h"
void Missile::Update(float dt)
{
	vector2 forward = vector2::rotate(vector2::up, m_transform.rotation);
	m_transform.translation += forward * m_speed * dt;

	m_lifetime -= dt;
	if (m_lifetime <= 0.0f) {
		m_destroy = true;
	}

	std::vector<Actor*> actors = m_scene->GetActorsByTag("Enemy");
	for (Actor* actor : actors) {
		float distance = vector2::distance(actor->m_transform.translation, m_transform.translation);
		if (distance <= 15.0f) {
			/*Actor* particle = m_scene->GetActorFactory()->Create("Explosion_Spawner");
			particle->m_transform.rotation = m_transform.rotation;
			particle->m_transform.translation = m_transform.translation;
			m_scene->AddActor(particle);*/

			AudioSystem::Instance()->PlaySound("death");
			int score = m_scene->GetGame()->GetScore();
			m_scene->GetGame()->SetScore(score + 100);
			m_destroy = true;
			actor->m_destroy = true;
			break;
		}
	}
}

bool Missile::Load(const rapidjson::Value& value)
{
	Actor::Load(value);

	json::get_float(value, "speed", m_speed);
	json::get_float(value, "rotate", m_rotate);

	return true;
}
