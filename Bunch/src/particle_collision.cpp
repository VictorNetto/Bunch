#include <particle_collision.h>

using namespace bunch;

Particle* NOT_A_PARTICLE = nullptr;

/*
Functions declarations. Definitions bellow.
*/
void resolve_velocity(ParticleCollisionData& data);
void resolve_penetration(ParticleCollisionData& data);
real separating_velocity(const ParticleCollisionData& data);  // Compute the separating velocity in collisionNormal direction

/*
Instance of this class is used to sort by penetration.
*/
struct CompareByPenetration {
	bool operator()(const ParticleCollisionData& data1, const ParticleCollisionData& data2)
	{
		return (data1.penetration > data2.penetration);
	}
};

/*
Instance of this class is used to sort by separating velocity.
*/
struct CompareBySepVelocity {
	bool operator()(const ParticleCollisionData& data1, const ParticleCollisionData& data2)
	{
		return (separating_velocity(data1) < separating_velocity(data2));
	}
};

std::vector<ParticleCollisionData> ParticleCollisionDetector::get_collisions(int importance)
{
	if (importance == m_currentImportance) return m_collisions;  // we already have the correct data
	m_currentImportance = static_cast<Importance>(importance);

	if (importance == Importance::by_penetration) {  // sort by penetration: more positives came first
		std::sort(m_collisions.begin(), m_collisions.end(), CompareByPenetration());
	}
	else if (importance == Importance::by_sep_velocity) {  // sort by separanting velocity: more negatives came first
		std::sort(m_collisions.begin(), m_collisions.end(), CompareBySepVelocity());
	}

	return m_collisions;
}

void bunch::resolve_collision(ParticleCollisionData& data)
{
	resolve_velocity(data);
	resolve_penetration(data);
}

/*
We resolve velocity by change just components in collisionNormal direction (denoted by n).

In the collisionNormal directions the new velocities are
v1_f = (m1-r*m2)*v1_i/(m1+m2) + m2*(1+r)*v2_i/(m1+m2)
v2_f = m1*(1+r)*v1_i/(m1+m2) + (m2-r*m1)*v2_i/(m1+m2)
where r -> restitution. The mass m2 can be infinite (scnery), in which case v1_f = -r*v1_i.
This is the solution for v1_f and v2_f of the system
v1_f - v2_f = -r(v1_i - v2_i)
m1*v1_f + m2*v2_f = m1*v1_i + m2*v2_i

In the code bellow A1 and A2 denotes the velocity component in collisionNormal direction.
*/
void resolve_velocity(ParticleCollisionData& data)
{
	Vector3 n = data.collisionNormal;  // n is just collisionNormal

	// We first consider scnery collisions
	if (!data.particle2) {
		// compute particle1's velocity in collisionNormal direction
		real A1 = n.dot(data.particle1->velocity);  // this change
		
		// Compute new collisionNormal component of velocity
		real A1_new = data.restitution * A1 * (-1);

		// Change particle1's velocity
		data.particle1->velocity += data.collisionNormal * (A1_new - A1);

		return;
	}

	// If theres a particle2...
	// compute the velocity components of particle1 and particle2 in collisionNormal direction
	real A1 = n.dot(data.particle1->velocity);  // this change
	real A2 = n.dot(data.particle2->velocity);  // this change

	// Compute new collisionNormal component of velocity
	real m1 = data.particle1->get_mass();
	real m2 = data.particle2->get_mass();
	real r = data.restitution;
	real A1_new = (m1 - r * m2)*A1 / (m1 + m2) + m2 * (1 + r)*A2 / (m1 + m2);
	real A2_new = m1 * (1 + r)*A1 / (m1 + m2) + (m2 - r * m1)*A2 / (m1 + m2);

	// Change the velocities of particle1 and particle2
	data.particle1->velocity += data.collisionNormal * (A1_new - A1);
	data.particle2->velocity += data.collisionNormal * (A2_new - A2);
}


/*
Remove penetration by moving the particles. Big mass move less.
*/
void resolve_penetration(ParticleCollisionData& data)
{
	if (data.penetration < 0) return;  // exit if theres no penetration

	// We first consider scnery collisions
	if (!data.particle2) {
		data.particle1->position += data.collisionNormal * data.penetration;
	}

	// If theres a particle2...
	real m1 = data.particle1->get_mass();
	real m2 = data.particle2->get_mass();
	data.particle1->position += data.collisionNormal * data.penetration * (m2 / (m1 + m2));
	data.particle2->position += data.collisionNormal * data.penetration * (m1 / (m1 + m2)) * (-1);

}

real separating_velocity(const ParticleCollisionData& data)
{
	real sepVelocity = (data.particle1->velocity).dot(data.collisionNormal);  // compute particle1 separating velocity
	if (data.particle2)
		sepVelocity -= (data.particle2->velocity).dot(data.collisionNormal);  // compute particle2 separating velocity if it exist

	return sepVelocity;
}
