#pragma once

#include <precision.h>
#include <vector3.h>
#include <particle.h>

#include <vector>

namespace bunch {

	/*
	Base class to represent a force. The actual force must implement
	the virtual function apply_force() which calls add_force() for each
	relevent particle. The addresses of this particles are kept in m_particles.
	*/
	class ParticleForce {
	public:
		virtual void apply_force() = 0;

	protected:
		std::vector<Particle*> m_particles;
	};

	/*
	A force to apply gravity to particle with finite mass.
	*/
	class ParticleGravity : public ParticleForce {
	public:
		ParticleGravity(const Vector3& gravity = GRAVITY);

		void add_particle(Particle* particle);  // gravity affect all particles then all particles must be added

		virtual void apply_force();

	private:
		Vector3 m_gravity;
	};

	class TwoParticlesSpring : public ParticleForce {
	public:
		TwoParticlesSpring(real restLength, real springConstant, Particle* particle1, Particle* particle2);

		virtual void apply_force();

	private:
		real m_restLength;
		real m_springConstant;
	};

}