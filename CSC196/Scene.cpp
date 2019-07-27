#include "Scene.h"
#include "Player.h"
#include "Missile.h"
#include "Enemy.h"
#include "Emitter.h"
#include "..\\particles\particle_system.h"

void Scene::Startup()
{
	m_actorFactory = new ActorFactory;
	m_particleSystem = new ParticleSystem(200);

	m_actorFactory->Register("Player", new Creator<Player, Actor>());
	m_actorFactory->Register("Missile", new Creator<Missile, Actor>());
	m_actorFactory->Register("Enemy", new Creator<Enemy, Actor>());
	m_actorFactory->Register("Emitter", new Creator<Emitter, Actor>());
}

void Scene::Shutdown()
{
	delete m_actorFactory;
	for (Actor* actor : m_actors) {
		delete actor;
	}
}

void Scene::Update(float dt) {
	m_spawnTimer = m_spawnTimer + dt;
	if (m_spawnTimer >= 2.0f)
	{
		m_spawnTimer = 0.0f;
		Actor* actor = m_actorFactory->Create("Enemy_Spawner");

		random_real_t random;
		actor->m_transform.translation = vector2(random(800.0f), random(600.0f));
		actor->m_transform.rotation = random(math::TWO_PI);
		AddActor(actor);
	}

	for (Actor* actor : m_actors)	 {
		actor->Update(dt);
	}
	
	auto iter = m_actors.begin();
	while (iter != m_actors.end()) {
		if (((*iter)->m_destroy)) {
			delete *iter;
			iter = m_actors.erase(iter);
		}
		else {
			iter++;
		}
	}
}

void Scene::Draw(Core::Graphics& graphics)
{
	for (Actor* actor : m_actors) {
		actor->Draw(graphics);
	}
}

bool Scene::Load(const char* filename)
{
	rapidjson::Document document;
	json::load(filename, document);
	const rapidjson::Value& actors = document["actors"];
	if (actors.IsArray()) {
		LoadActors(actors);
	}

	const rapidjson::Value& spawners = document["spawners"];
	if (spawners.IsArray()) {
		LoadSpawners(spawners);
	}
	return true;
}

void Scene::AddActor(Actor* actor) {
	actor->SetScene(this);
	m_actors.push_back(actor);
}

Actor* Scene::GetActorByName(const std::string name)
{
	Actor* result = nullptr;
	for (Actor* actor : m_actors) {
		if (actor->GetName() == name) {
			result = actor;
			break;
		}
	}
	return result;
}

std::vector<Actor*> Scene::GetActorsByTag(const std::string tag)
{
	std::vector<Actor*> result;

	for (Actor* actor : m_actors) {
		if (actor->GetTag() == tag) {
			result.push_back(actor);
		}
	}

	return result;
}

bool Scene::LoadActors(const rapidjson::Value& value)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& actor_value = value[i];
		if (actor_value.IsObject()) {
			std::string type;
			if (json::get_string(actor_value, "type", type)) {
				Actor* actor = m_actorFactory->Create(type);
				if (actor && actor->Load(actor_value)) {
					AddActor(actor);
				}
			}
		}
	}
	return true;
}

bool Scene::LoadSpawners(const rapidjson::Value& value)
{
	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& actor_value = value[i];
		if (actor_value.IsObject()) {
			std::string type;
			if (json::get_string(actor_value, "type", type)) {
				Actor* actor = m_actorFactory->Create(type);
				if (actor && actor->Load(actor_value)) {
					Spawner<Actor>* spawner = new Spawner<Actor>(actor);
					m_actorFactory->Register(actor->GetName(), spawner);
				}
			}
		}
	}
	return true;
}
