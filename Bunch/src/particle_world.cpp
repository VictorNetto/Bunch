#include <particle_world.h>

using namespace bunch;

ParticleWorld::ParticleWorld(int maxCollisionDetections)
	: m_maxCollisionDetections(maxCollisionDetections) {}


/*
Add particle to m_particles and return the index where the particle is.
A pointer of this particle is send to all collision detectors.
*/
unsigned int ParticleWorld::add_particle(Particle particle)
{
	unsigned int index = m_particles.size();
	m_particles.push_back(particle);

	Particle* particle_ptr = &m_particles[index];  // send this particle to all detectors
	for (auto detector : m_collisionDetectors) {
		detector->add_collisible_particle(particle_ptr);
	}

	return index;  // return the particle index for latter access
}

/*
Just add a pointer of a detector to the list of collision detectors
*/
void ParticleWorld::add_collision_detector(ParticleCollisionDetector* detector)
{
	m_collisionDetectors.push_back(detector);
}

/*
Just add a pointer of a force to the list of forces
*/
void ParticleWorld::add_force(ParticleForce* force)
{
	m_forces.push_back(force);
}

/*
Integrate the world by an amount of time dt. This is done by resolving collisions,
computing the new forces and then integrating the particles.
*/
void ParticleWorld::integrate(real dt)
{
	// we first handle collisions
	for (int i = 0; i < m_maxCollisionDetections; i++) {
		for (auto detector : m_collisionDetectors) {
			detector->detect();
			std::vector<ParticleCollisionData>& collisions = detector->get_collisions();
			if (collisions.size() > 0) {
				resolve_collision(collisions);
			}
		}
	}

	// then we apply the forces
	for (ParticleForce* force : m_forces) {
		force->apply_force();
	}

	// finally we integrate the particles
	for (Particle particle : m_particles) {
		particle.integrate(dt);
	}

}