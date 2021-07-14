#include "somapch.hpp"

#include "camera/FPCamera.hpp"
#include "input/input.hpp"

const float CAMERA_SENSITIVITY = 0.01f;
const float CAMERA_SPEED = 10.0f;

FPCamera::FPCamera(Window& window, InputHandler& eventHandler, bool ortho) :m_window(&window), m_Ortho(ortho) {
	if (m_Ortho)
		CalculateOrthoProjection();
	else
		CalculatePerspectiveProjection();
    eventHandler.addKeyControl(Input::KEY_W, m_movementZ, -1.0f);
    eventHandler.addKeyControl(Input::KEY_S, m_movementZ, 1.0f);

    eventHandler.addKeyControl(Input::KEY_A, m_movementX, -1.0f);
    eventHandler.addKeyControl(Input::KEY_D, m_movementX, 1.0f);

    eventHandler.addKeyControl(Input::KEY_Q, m_movementY, -1.0f);
    eventHandler.addKeyControl(Input::KEY_E, m_movementY, 1.0f);
}

Matrix FPCamera::GetViewMatrix()
{
    Vector3f position = transform.getTranslation();
    Quaternion rotation = transform.getRotation();

    Vector3f center = position + rotation.getAxisZRev();
    Vector3f up = rotation.getAxisY();

    return Matrix::lookAt(position,center,up);
}

Matrix FPCamera::CalculatePerspectiveProjection()
{
    m_projection = Matrix::perspective(Math::toRadians(45.0f), m_window->getWidth() / m_window->getHeight(), 0.1f, 1000.0f);

    return m_projection;
}

Matrix FPCamera::CalculateOrthoProjection()
{
    m_projection = Matrix::ortho(0.0f,(float)m_window->getWidth(),0.0f,(float)m_window->getHeight(),-1000.0f, 1000.0f);

    return m_projection;
}

void FPCamera::ProcessKeyboard(float dt)
{
	float velocity = CAMERA_SPEED * dt;

	Vector3f tr = transform.getTranslation();
	tr += Vector3f(m_movementX.GetAmt() * velocity, m_movementY.GetAmt() * velocity, m_movementZ.GetAmt() * velocity);
    transform.setTranslation(tr);
}

void FPCamera::ProcessMouse()
{
}