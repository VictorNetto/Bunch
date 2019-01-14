#include <particle.h>

using namespace bunch;

/*
The mass can be infinite. In this case m_inverseMass == 0
and the value return will be INFINITE_MASS.
*/
real Particle::get_mass()
{
	if (m_inverseMass == 0)
		return INFINITE_MASS;

	return 1 / m_inverseMass;
}

void Particle::set_mass(real mass)
{
	if (mass == INFINITE_MASS)  // mass can't be 0 or negative
		m_inverseMass = 0;
	
	m_inverseMass = 1 / mass;
}

Particle::Particle()
	: position(Vector3()), velocity(Vector3()), acceleration(GRAVITY), dragging(1), friction(0)
{
	set_mass(1);
}

Particle::Particle(real mass, const Vector3& pos, const Vector3& vel, const Vector3& acc = GRAVITY,
	real dragging = 1, real friction = 0, real bouncing = 1)
	: position(pos), velocity(vel), acceleration(acc), dragging(dragging), friction(friction), bouncing(bouncing)
{
	set_mass(mass);
}

void Particle::add_force(const Vector3& force)
{
	m_forces += force;
}

void Particle::integrate(real dt)
{
	Vector3 totalAcceleration = acceleration;  // acceleration is treated differently of position and velocity
	                                           // to permit hold some special value such the gravity

	totalAcceleration += m_forces * m_inverseMass;  // compute the acceleration of the particle
	clear_forces();  // don't need the forces anymore, so we clear it to be update in the next integration step

	position += velocity * dt;  // compute the new position (dt can't be too big)
	velocity += totalAcceleration * dt;  // compute the new velocity
}

void Particle::clear_forces()
{
	m_forces.x = 0;
	m_forces.y = 0;
	m_forces.z = 0;
}