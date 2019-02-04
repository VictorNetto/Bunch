#pragma once

#include <precision.h>
#include <vector3.h>
#include <particle.h>
#include <particle_collision.h>

#include <vector>

namespace bunch {


	/*
	Detector for collision with ground (y = const). This is too simple for general use and a better
	approach is necessary for a full detector collision with a complex scnery.
	Collision is created for all particles with position.y less than a specified value (m_yHeight).
	Penetration is just (m_yHeight - position.y). The member m_bouncing is used for restitution math.
	*/
	class ParticleCollisionWithGroundDetector : public ParticleCollisionDetector {
	public:
		ParticleCollisionWithGroundDetector(real y_height, real bouncing = 1);

		virtual void detect();  // create a collision for all particle with position.y < m_yHeight

	private:
		real m_yHeight;
		real m_bouncing;
	};

	/*
	Keep two particle connect via a cable. Collisions are generated only if the distance between the
	particle is greater than the clable's length.
	*/
	class ParticleCable : public ParticleCollisionDetector {
	public:
		ParticleCable(Particle* particle1, Particle* particle2, real cableLength, real bouncing = 0);

		virtual void add_collisible_particle(Particle* particle) {}  // do nothing
		virtual void detect();

	private:
		real m_cableLength;
		real m_bouncing;
	};

	/*
	Keep two particle connect via a rod: the distance between the particle is always the rod's length
	*/
	class ParticleRod : public ParticleCollisionDetector {
	public:
		ParticleRod(Particle* particle1, Particle* particle2, real rodLength);

		virtual void add_collisible_particle(Particle* particle) {}  // do nothing
		virtual void detect();

	private:
		real m_rodLength;
	};
}