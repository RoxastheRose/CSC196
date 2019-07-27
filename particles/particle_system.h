#pragma once

#include "particles.h"
#include "..\\core\pool_allocator.h"
#include "..\\external\core\include\graphics.h"

#include <list>

class ParticleSystem
{
public:
	ParticleSystem(size_t size);
	~ParticleSystem();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

	void Create(const vector2& postition, const vector2& velocity, const color& color_, float damping, float lifetime);

private:
	PoolAllocator<Particle>* m_particle_pool;
	std::list<Particle*> m_particles;
};