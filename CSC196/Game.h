#pragma once
#include "../external/core/include/core.h"
#include "..//core/Core.h"
#include "Actor.h"
#include "Scene.h"

class Game {
public:
	enum eState {
		INIT,
		TITLE,
		START_GAME,
		UPDATE_GAME,
		GAME_OVER,
		RESET
	};

public:
	Game() {}

	void StartUp();
	void ShutDown();
	
	void Update(float dt);
	void Draw(Core::Graphics& graphics);

	int GetScore() { return m_score; }
	void SetScore(int score) { m_score = score; }
	int GetLives() { return m_lives; }
	void SetLives(int lives) { m_lives = lives; }

private: 
	random_real_t m_random;
	Scene* m_scene;

	int m_score;
	int m_lives;

	eState m_state;
	float m_stateTimer;
};
