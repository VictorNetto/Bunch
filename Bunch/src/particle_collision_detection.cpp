#include <particle_collision_detection.h>

using namespace bunch;

/*
--------------------------------------------------------------------------------
---------- ParticleCollisionWithGroundDetector ---------------------------------
--------------------------------------------------------------------------------
*/

ParticleCollisionWithGroundDetector::ParticleCollisionWithGroundDetector(real y_height, real bouncing)
	: m_yHeight(y_height), m_bouncing(bouncing) {}

void ParticleCollisionWithGroundDetector::detect()
{
	m_collisions.clear();  // remove all old collision data
	
	for (Particle* p : m_collisibleParticles) {
		if (p->position.y < m_yHeight) {
			ParticleCollisionData data;
			data.collisionNormal = UP_VECTOR;  // UP_VECTOR == (0, 1, 0)
			data.particle1 = p;
			data.particle2 = NOT_A_PARTICLE;
			data.penetration = m_yHeight - p->position.y;
			data.restitution = m_bouncing * p->bouncing;

			m_collisions.push_back(data);
		}
	}
}

/*
--------------------------------------------------------------------------------
---------- ParticleCable -------------------------------------------------------
--------------------------------------------------------------------------------
*/
ParticleCable::ParticleCable(Particle* particle1, Particle* particle2, real cableLength, real bouncing)
	: m_cableLength(cableLength), m_bouncing(bouncing)
{
	m_collisibleParticles.push_back(particle1);
	m_collisibleParticles.push_back(particle2);
}

void ParticleCable::detect()
{
	m_collisions.clear();  // remove all old collision data

	Vector3 displacement = m_collisibleParticles[0]->position - m_collisibleParticles[1]->position;

	if (displacement.length() > m_cableLength) {  // if the particle are too far
		ParticleCollisionData data;
		data.collisionNormal = displacement.get_unit() * (-1);  // the (-1) factor make particles to join into one another
		data.particle1 = m_collisibleParticles[0];
		data.particle2 = m_collisibleParticles[1];
		data.penetration = displacement.length() - m_cableLength;
		data.restitution = m_bouncing;  // we just set restitution this way to keep it simple

		m_collisions.push_back(data);
	}
}

/*
--------------------------------------------------------------------------------
---------- ParticleRod ---------------------------------------------------------
--------------------------------------------------------------------------------
*/
ParticleRod::ParticleRod(Particle* particle1, Particle* particle2, real rodLength)
	: m_rodLength(rodLength)
{
	m_collisibleParticles.push_back(particle1);
	m_collisibleParticles.push_back(particle2);
}

void ParticleRod::detect()
{
	m_collisions.clear();  // remove all old collision data

	Vector3 displacement = m_collisibleParticles[0]->position - m_collisibleParticles[1]->position;

	if (displacement.length() > m_rodLength) {
		ParticleCollisionData data;
		data.collisionNormal = displacement.get_unit() * (-1);  // the (-1) factor make particles to join into one another
		data.particle1 = m_collisibleParticles[0];
		data.particle2 = m_collisibleParticles[1];
		data.penetration = displacement.length() - m_rodLength;
		data.restitution = 0;  // no bouciness

		m_collisions.push_back(data);
	}
	else if (displacement.length() < m_rodLength) {
		ParticleCollisionData data;
		data.collisionNormal = displacement.get_unit();  // no (-1) factor anymore
		data.particle1 = m_collisibleParticles[0];
		data.particle2 = m_collisibleParticles[1];
		data.penetration = m_rodLength - displacement.length();  // penetration now changes
		data.restitution = 0;  // no bouciness

		m_collisions.push_back(data);
	}
}