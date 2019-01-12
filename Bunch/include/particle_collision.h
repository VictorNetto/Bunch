#pragma once

#include <precision.h>
#include <vector3.h>
#include <particle.h>

namespace bunch {
	const Particle* NOT_A_PARTICLE = nullptr;

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
		Vector3 collisionNormal;
		real penetration;
		real restitution;
	};

	/*
	Compute the separating velocity in collisionNormal direction.
	*/
	real separating_velocity(const ParticleCollisionData& data);

	/*
	Resolve a single collision. This functions must be called several times
	to achieve good results for multiples particles.
	*/
	void resolve_collision(ParticleCollisionData& data);

}