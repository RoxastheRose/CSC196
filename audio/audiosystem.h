#pragma once
#include "..//external/fmod/api/core/inc/fmod.hpp"
#include "..//framework/Singleton.h"
#include "../core/assert.h"

#include <iostream>
#include <map>

class AudioSystem : public Singleton<AudioSystem> {
public:
	bool Startup() {
		FMOD_RESULT result = FMOD::System_Create(&m_system);
		ASSERT_MSG(result == FMOD_OK, "Error creating FMOD system.");
	
		void* extradriverdata = nullptr;
		result = m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		return true;
	}
	void Shutdown() {
		for (auto& sound : m_sounds) {
			sound.second->release();
		}
		m_sounds.clear();
		m_system->close();
		m_system->release();
	}
	void Update() {
		m_system->update();
	}
	
	void AddSound(const std::string& key, const char* filename) {
		if (m_sounds.find(key) == m_sounds.end()) {
			FMOD::Sound* sound = nullptr;
			FMOD_RESULT result = m_system->createSound(filename, FMOD_DEFAULT, 0, &sound);
			if (result == FMOD_OK) {
				m_sounds[key] = sound;
			}
		}
	}
	void PlaySound(const std::string& key, bool loop = false) {
		auto iter = m_sounds.find(key);
		if (iter != m_sounds.end()) {
			FMOD_MODE mode = (loop) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
			FMOD::Sound* sound = iter->second;
			sound->setMode(mode);
			FMOD::Channel* channel;
			FMOD_RESULT result = m_system->playSound(sound, 0, false, &channel);
			ASSERT_MSG(result == FMOD_OK, "Error playing sound.");
		}
	}
	void RemoveSound(const std::string& id) {
		auto iter = m_sounds.find(id);
		if (iter != m_sounds.end()) {
			FMOD::Sound* sound = iter->second;
			sound->release();
			m_sounds.erase(id);
		}
	}

private:
	FMOD::System* m_system = nullptr;
	std::map<std::string, FMOD::Sound*> m_sounds;
};