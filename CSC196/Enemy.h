#pragma once
#include "Actor.h"
#include "..//math/Transform.h"

class Enemy : public Actor {
public:
	Enemy() {}
	virtual ~Enemy() {}

	const char* GetType() { return "Enemy"; }

	void Update(float dt) override;

	virtual bool Load(const rapidjson::Value& value);
	virtual Enemy* Clone() { return new Enemy(*this); }

private:
	float m_speed;
	float spawn_timer;
};