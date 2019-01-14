#pragma once

#include <precision.h>
#include <vector3.h>
#include <particle.h>

#include <vector>
#include <algorithm>

namespace bunch {
	extern Particle* NOT_A_PARTICLE;
	/*
	Data to represent a collision between two particles
	or between a particle and the scnery (in this case particle2 = NOT_A_PARTICLE).
	The collisionNormal is in the particle1's point of view.

	Collision Detection Algorithms will create instances of this class
	to be precessed later by resolve_collision function.
	*/
	struct ParticleCollisionData {
		Particle* particle1;
		Particle* particle2;
		Vector3 collisionNormal;  // this must be an unit vector
		real penetration;
		real restitution;
	};


	/*
	Base class for collision detection. The collision data is kept in m_collisions
	and can be quered via get_collisions() with the appropiate importance.
	Put information in the m_collisions is job for the childs of this class
	*/
	class ParticleCollisionDetector {
	public:
		std::vector<ParticleCollisionData> get_collisions(int importance);

	protected:
		virtual void detect() = 0;  // detect all collisions and put them in m_collisions

		std::vector<ParticleCollisionData> m_collisions;  // collisions data

		enum Importance
		{
			none, by_sep_velocity, by_penetration
		};
		Importance m_currentImportance = Importance::none;
	};

	/*
	Resolve a single collision. This functions must be called several times
	to achieve good results for multiples particles.
	*/
	void resolve_collision(ParticleCollisionData& data);

}