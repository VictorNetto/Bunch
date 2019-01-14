#pragma once

#include <precision.h>
#include <vector3.h>

namespace bunch {
	const real INFINITE_MASS = -1;
	const Vector3 GRAVITY = DOWN_VECTOR * 10;

	/*
	A Particle is a object with mass (a real number),
	position, velocity an acceleration (all are Vector3),
	dragging and friction coefficients (real numbers) and
	a bouncing coefficient (real number) for restitution calculation

	Particles can interact among themselves by forces and
	impulses, and with the scnery by impulses. Forces and
	impulses are generated by constraints between particles
	as well by collisions between particles and scnery.
	*/
	class Particle {
	public:
		real get_mass();  // mass is kept as its inverse to handle easily infinite mass
		void set_mass(real mass);

		Vector3 position;
		Vector3 velocity;
		Vector3 acceleration;

		real dragging;
		real friction;

		real bouncing;  // used to compute restitution

	public:
		Particle();
		Particle(real mass, const Vector3& pos, const Vector3& vel, const Vector3& acc = GRAVITY,
			real dragging = 1, real friction = 0, real bouncing = 1);

		void add_force(const Vector3& force);  // add a force to act in the next integration step
		void integrate(real dt);  // update particle's position, velocity and acceleration

	private:
		real m_inverseMass;
		Vector3 m_forces;

		void clear_forces();
	};

}