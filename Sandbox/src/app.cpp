#include "World3D.h"

#include <particle.h>
#include <particle_world.h>
#include <particle_collision_detection.h>
#include <particle_force.h>


int main()
{
	// World3D setup
	World3D world;
	world.set_frame_rate(60.0f);

	// World3D main loop
	while (!world.should_close())
	{
		world.update();
	}

	return 0;
}