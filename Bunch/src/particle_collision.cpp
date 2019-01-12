#include <particle_collision.h>

using namespace bunch;

/*
Functions declarations. Definitions bellow.
*/
void resolve_velocity(ParticleCollisionData& data);
void resolve_penetration(ParticleCollisionData& data);

real bunch::separating_velocity(const ParticleCollisionData& data)
{
	real sepVelocity = (data.particle1->velocity).dot(data.collisionNormal);  // compute particle1 separating velocity
	if (data.particle2)
		sepVelocity -= (data.particle2->velocity).dot(data.collisionNormal);  // compute particle2 separating velocity if it exist

	return sepVelocity;
}

void bunch::resolve_collision(ParticleCollisionData& data)
{
	resolve_velocity(data);
	resolve_penetration(data);
}

/*
We resolve velocity by change just components in collisionNormal direction (denoted by n).
Components orthogonal to n (denoted by t1 and t2) are hold. To find t1 and t2 we use some
linear algebra: t1 = (n.cross(e_i)).get_unit(), where e_i is (1, 0, 0) or (0, 1, 0); and
t2 = n.cross(t1).

In the collisionNormal directions the new velocities are
v1_f = (m1-r*m2)*v1_i/(m1+m2) + m2*(1+r)*v2_i/(m1+m2)
v2_f = m1*(1+r)*v1_i/(m1+m2) + (m2-r*m1)*v2_i/(m1+m2)
where r -> restitution. The mass m2 can be infinite (scnery), in which case v1_f = -r*v1_i.

We work here with two base: the canonical, {x, y, z}, and the {n, t1, t2}. Any vector v can
be write as v = ax + by + cz = An + Bt1 + Ct2 ---- a, b, c, A, B and C are numbers! And then,
a = <v, x> = A*<n, x> + B*<t1, x> + C*<t2, x> and so on ---- < , > is the dot product.
We will use a1, b1, c1, A1... as particle1's components in the right base and
we will use a2, b2, c2, A2... as particle2's components in the right base.

Now the code bellow can make sense.
*/
void resolve_velocity(ParticleCollisionData& data)
{
	// Compute n, t1 and t2
	Vector3 n = data.collisionNormal;  // n is just collisionNormal
	Vector3 t1 = n.cross(X_DIR); // we first try with X_DIR = Vector3(1, 0, 0)
	if (t1.length_square() == 0) {
		t1 = n.cross(Y_DIR);  // if X_DIR isn't good, we use Y_DIR = Vector3(0, 1, 0)
	}
	t1.to_unit();  // make t1 unitary
	Vector3 t2 = n.cross(t1);  // compute t2

	// Define the canonical base {x, y, z} for simplicity
	Vector3 x = X_DIR;
	Vector3 y = Y_DIR;
	Vector3 z = Z_DIR;

	// We first consider scnery collisions
	if (!data.particle2) {
		// compute particle1's velocity components in the base {n, t1, t2}
		real A1 = n.dot(data.particle1->velocity);  // this change
		real B1 = t1.dot(data.particle1->velocity);  // this don't change
		real C1 = t2.dot(data.particle1->velocity);  // this don't change
		
		// Change the collisionNormal component
		A1 = data.restitution * A1 * (-1);

		// Compute the new components in base {x, y, z}
		real a1 = A1 * n.dot(x) + B1 * t1.dot(x) + C1 * t2.dot(x);
		real b1 = A1 * n.dot(y) + B1 * t1.dot(y) + C1 * t2.dot(y);
		real c1 = A1 * n.dot(z) + B1 * t1.dot(z) + C1 * t2.dot(z);


		// Change the velocity of particle1
		data.particle1->velocity = Vector3(a1, b1, c1);

		return;
	}


	// If theres a particle2...
	// compute the velocity components of particle1 and particle2 in the base {n, t1, t2}
	real A1 = n.dot(data.particle1->velocity);  // this change
	real B1 = t1.dot(data.particle1->velocity);  // this don't change
	real C1 = t2.dot(data.particle1->velocity);  // this don't change
	real A2 = n.dot(data.particle2->velocity);  // this change
	real B2 = t1.dot(data.particle2->velocity);  // this don't change
	real C2 = t2.dot(data.particle2->velocity);  // this don't change

	// Change the collisionNormal components
	real m1 = data.particle1->get_mass();
	real m2 = data.particle2->get_mass();
	real r = data.restitution;
	real A1_new = (m1 - r * m2)*A1 / (m1 + m2) + m2 * (1 + r)*A2 / (m1 + m2);
	real A2_new = m1 * (1 + r)*A1 / (m1 + m2) + (m2 - r * m1)*A2 / (m1 + m2);
	A1 = A1_new;
	A2 = A2_new;

	// Compute the new components in base {x, y, z}
	real a1 = A1 * n.dot(x) + B1 * t1.dot(x) + C1 * t2.dot(x);
	real b1 = A1 * n.dot(y) + B1 * t1.dot(y) + C1 * t2.dot(y);
	real c1 = A1 * n.dot(z) + B1 * t1.dot(z) + C1 * t2.dot(z);
	real a2 = A2 * n.dot(x) + B2 * t1.dot(x) + C2 * t2.dot(x);
	real b2 = A2 * n.dot(y) + B2 * t1.dot(y) + C2 * t2.dot(y);
	real c2 = A2 * n.dot(z) + B2 * t1.dot(z) + C2 * t2.dot(z);

	// Change the velocities of particle1 and particle2
	data.particle1->velocity = Vector3(a1, b1, c1);
	data.particle2->velocity = Vector3(a2, b2, c2);
}

void resolve_penetration(ParticleCollisionData& data)
{

}