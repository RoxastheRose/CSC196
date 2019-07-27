#pragma once
#include "Actor.h"
#include "..//math/Transform.h"
#include "..\\audio\audiosystem.h"

class Missile : public Actor {
public:
	Missile() {
		AudioSystem::Instance()->AddSound("death", "audio\\death.wav");
	}
	virtual ~Missile() {}

	const char* GetType() { return "Missile"; }

	void Update(float dt) override;

	virtual bool Load(const rapidjson::Value& value);
	virtual Missile* Clone() { return new Missile(*this); }

private:
	float m_speed;
	float m_lifetime = 3.0f;
};