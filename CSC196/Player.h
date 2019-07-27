#pragma once
#include "Actor.h"
#include "..//math/Transform.h"
#include "..//audio/audiosystem.h"

class Player : public Actor {
public:
	Player() { 
		AudioSystem::Instance()->AddSound("missile", "audio\\Laser_Shoot.wav");  
		AudioSystem::Instance()->AddSound("dash", "audio\\Dash.wav");  
	}
	virtual ~Player() {}
	const char* GetType() { return "Player"; }

	float GetCountdown() { return m_dashCountDown; }

	void  Warp(float);
	void Update(float dt) override;

	virtual bool Load(const rapidjson::Value& value);
	virtual Player* Clone() { return new Player(*this); }

private:
	float m_speed;
	bool m_dashUsed = false;
	float m_dashCountDown = 0.0f;
	float m_shootCountDown = 0.0f;
};