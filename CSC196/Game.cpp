#include "Game.h"
#include "..//math/math.h"
#include "..//renderer/color.h"
#include "Player.h"
#include "..//audio/audiosystem.h"

void Game::StartUp()
{
	m_state = eState::INIT;
}

void Game::ShutDown()
{
	AudioSystem::Instance()->Shutdown();
	if (m_scene) {
		m_scene->Shutdown();
		delete m_scene;
	}
}

void Game::Update(float dt)
{
	AudioSystem::Instance()->Update();
	switch (m_state) {
	case Game::INIT:
		AudioSystem::Instance()->Startup();
		m_state = eState::TITLE;
		break;
	case Game::TITLE:
		if (Core::Input::IsPressed(Core::Input::KEY_SPACE)) {
			m_state = eState::START_GAME;
		}
		break;
	case Game::START_GAME:
		m_lives = 3;
		m_score = 0;

		m_scene = new Scene(this);
		m_scene->Startup();
		m_scene->Load("scene01.txt");

		m_state = eState::UPDATE_GAME;
		break;
	case Game::UPDATE_GAME:
		if (m_lives <= 0) {
			m_stateTimer = 3.0f;
			m_state = eState::GAME_OVER;
		}
		m_scene->Update(dt);
		break;
	case Game::GAME_OVER:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0.0f) {
			m_state = eState::RESET;
		}
		m_scene->Update(dt);
		break;
	case Game::RESET:
		m_scene->Shutdown();
		delete m_scene;

		m_state = eState::TITLE;
	default:
		break;
	}
}

void Game::Draw(Core::Graphics& graphics)
{
	color textcolor = color::white;
	graphics.SetColor(textcolor);
	
	switch (m_state)
	{
	case Game::TITLE:
		graphics.DrawString(400, 300, "Graboids");
		break;
	case Game::UPDATE_GAME:
		{
			Player* temp = (Player*)(m_scene->GetActorByName("Player"));
			float timer = temp->GetCountdown();
			int strTimer = timer == 0 ? 0 : timer + 1;
			
			std::string score = "Score: " + std::to_string(m_score);
			std::string lives = "Lives: " + std::to_string(m_lives);
			std::string countdown = "Hyperdash (Shift): " + std::to_string(strTimer);
			graphics.DrawString(20, 20, score.c_str());
			graphics.DrawString(20, 40, lives.c_str()); 
			graphics.DrawString(20, 60, countdown.c_str());
		}
		m_scene->Draw(graphics);
		break;
	case Game::GAME_OVER:
		graphics.DrawString(400, 300, "Game Over");
		m_scene->Draw(graphics);
		break;
	case Game::RESET:
		break;
	default:
		break;
	}

	
}
