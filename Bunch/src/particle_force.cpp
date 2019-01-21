#include <particle_force.h>

using namespace bunch;

/*
--------------------------------------------------------------------------------
---------- ParticleGravity -----------------------------------------------------
--------------------------------------------------------------------------------
*/
ParticleGravity::ParticleGravity(const Vector3& gravity)
	: m_gravity(gravity) {}

void ParticleGravity::add_particle(Particle* particle)
{
	m_particles.push_back(particle);
}

void ParticleGravity::apply_force()
{
	for (Particle* particle : m_particles) {
		particle->add_force(m_gravity * particle->get_mass());
	}
}


/*
--------------------------------------------------------------------------------
---------- TwoParticlesSpring --------------------------------------------------
--------------------------------------------------------------------------------
*/

TwoParticlesSpring::TwoParticlesSpring(real restLength, real springConstant, Particle* particle1, Particle* particle2)
	: m_restLength(restLength), m_springConstant(springConstant)
{
	m_particles.push_back(particle1);
	m_particles.push_back(particle2);
}

void TwoParticlesSpring::apply_force()
{
	Vector3 displacement = m_particles[0]->position - m_particles[1]->position;  // vector from particle2 to particle1
	real delta_L = displacement.length() - m_restLength;  // how much the spring is pressed or stretched

	m_particles[0]->add_force(displacement.get_unit() * delta_L * (-1));  // apply force to particle1
	m_particles[0]->add_force(displacement.get_unit() * delta_L * (+1));  // apply force to particle2
}

/*
--------------------------------------------------------------------------------
---------- Other Forces ... ----------------------------------------------------
--------------------------------------------------------------------------------
*/