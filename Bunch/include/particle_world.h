#pragma once

#include <vector3.h>
#include <particle.h>
#include <particle_collision.h>

#include <vector>

namespace bunch {

	/*
	All simulations of particles are performed by this class.
	Particles must be added to this and are kept here. For collision
	detectors, we just keep their address. The actual simulation
	is done by the function integrate.
	*/
	class ParticleWorld {
	public:
		ParticleWorld(int maxCollisionDetections = 10);

		unsigned int add_particle(Particle particle);  // add particle to the list of particles and return an identifier
		void add_collision_detector(ParticleCollisionDetector* detector);  // add a detector of collision to the world

		void integrate(real dt);  // update the whole world by an amont of time dt

	private:
		int m_maxCollisionDetections;

		std::vector<Particle> m_particles;  // list of particles of the world
		std::vector<ParticleCollisionDetector*> m_collisionDetectors;
	};

}