#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement
// Used as abstraction to stay away from window-system specific input methods
// --------------------------------------------------------------------------
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

enum Mouse_Button {
	BUTTON_LEFT,
	BUTTON_RIGHT
};

class Camera
{
public:
	Camera();

	glm::mat4 view();
	glm::mat4 projection();

	glm::vec3 position();
	
	void process_keyboard(Camera_Movement direction, float deltaTime);
	void update_mouse(float x, float y);
	void zoom(float dy);
	
	bool mouseButtonState[2];

private:
	float m_phy, m_theta;
	float m_fov;
	glm::vec3 m_position;
	glm::vec3 m_cameraDirection, m_cameraRight, m_cameraUp;

	void set_direction(float new_phy, float new_theta);
	void set_fov(float new_fov);

	// Members variable/functions to deal with mouse events
	struct MouseEvent
	{
		float x, y;
	};
	MouseEvent m_mousePosition;
	MouseEvent m_buttonLeftPressed;
	MouseEvent m_buttonRightPressed;
	glm::vec3 m_positionWhenLeftWasPressed;
	float m_phyWhenRightWasPressed, m_thetaWhenRightWasPressed;

	void process_mouse_left(float dx, float dy);
	void process_mouse_right(float dx, float dy);
};