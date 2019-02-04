#pragma once

#include <vector>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "primitive.h"
#include "object.h"
#include "frameRate.h"
#include "camera.h"

class World3D
{
public:
	World3D();
	~World3D();

	void main_loop();

	bool should_close() const;
	void update();
	void set_frame_rate(float frameRateToKeep);
	float delta_time();

private:
	static FrameRate m_frameRate;
	static Camera m_camera;
	GLFWwindow* m_window;
	std::vector<Object> m_objects;

	void draw() const;

	// particles stuff --------------------------------------------------------
	// ------------------------------------------------------------------------
public:
	void add_particle(float x, float y, float z, unsigned int* particleId);
	void set_particle_position(float x, float y, float z, unsigned int particleId);

private:
	struct Particle
	{
		Particle(float x, float y, float z, Object obj);
		float x, y, z;
		Object obj;
	};
	std::vector<Particle> m_particles;

	// callback functions -----------------------------------------------------
	// ------------------------------------------------------------------------
private:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};