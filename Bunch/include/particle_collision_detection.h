#pragma once

#include <precision.h>
#include <vector3.h>
#include <particle>
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
		void add_particle(Particle* particle);  // add particle to m_particles

		virtual void detect();  // create a collision for all particle with position.y < m_yHeight

	private:
		real m_yHeight;
		real m_bouncing;
		std::vector<Particle*> m_particles;
	};

}