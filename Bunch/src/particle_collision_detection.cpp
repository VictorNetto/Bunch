#include <particle_collision_detection.h>

using namespace bunch;

ParticleCollisionWithGroundDetector::ParticleCollisionWithGroundDetector(real y_height, real bouncing = 1)
	: m_yHeight(y_height), m_bouncing(bouncing) {}

void ParticleCollisionWithGroundDetector::add_particle(Particle* particle)
{
	m_particles.push_back(particle);
}

void ParticleCollisionWithGroundDetector::detect()
{
	m_collisions.clear();  // remove all old collision data
	
	for (Particle* p : m_particles) {
		if (p->position.y < m_yHeight) {
			ParticleCollisionData data;
			data.collisionNormal = UP_VECTOR;  // UP_VECTOR == (0, 1, 0)
			data.particle1 = p;
			data.particle2 = NOT_A_PARTICLE;
			data.penetration = m_yHeight - p->position.y;
			data.restituion = m_bouncing * p->bouncing;

			m_collisions.push_back(data);
		}
	}
}