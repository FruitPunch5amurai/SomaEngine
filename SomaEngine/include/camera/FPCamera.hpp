#pragma once


#include "core/common.hpp"
#include "math/Transform.hpp"
#include "core/Window.hpp"
#include "InputControl.hpp"
#include "InputHandler.hpp"

class SOMA_API FPCamera {

public:
	FPCamera(Window& window, InputHandler& eventHandler, bool ortho = false);
	~FPCamera() {};
		
	Transform transform;
	
	Matrix GetViewMatrix();
	Matrix GetProjection() { return m_projection; }
	Matrix CalculatePerspectiveProjection();
	Matrix CalculateOrthoProjection();

	void ProcessKeyboard(float dt);
	void ProcessMouse();

private:
	NULL_COPY_AND_ASSIGN(FPCamera);

	InputControl m_movementX;
	InputControl m_movementY;
	InputControl m_movementZ;

	bool m_Ortho;
	Matrix m_projection;
	Window* m_window;

};