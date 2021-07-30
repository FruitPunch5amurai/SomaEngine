#pragma once
#include "core/common.hpp"
#include "events/Event.hpp"
#include <glm/glm.hpp>

struct WindowProps {
	std::string title;
	uint32 width;
	uint32 height;

	WindowProps(const std::string& t = "Soma Engine",
		uint32 w = 1280,
		uint32 h = 730) :title(t), width(w), height(h){}

};

class  GenericWindow {
public:
	using EventCallbackFn = std::function<void(SOMA_ENGINE::Event&)>;

	virtual ~GenericWindow() {}
	
	virtual void update() = 0;
	
	virtual uint32 getWidth() const = 0;
	virtual uint32 getHeight() const = 0;

	virtual void setWidth(uint32 w) = 0;
	virtual void setHeight(uint32 h) = 0;

	virtual bool IsKeyPressed(uint32 key) const =0;
	virtual bool IsMouseButtonPressed(uint32 key) const = 0;
	virtual glm::vec2 GetMousePosition() const = 0;
	virtual void KeyPress(uint32 keyId) = 0;
	virtual void KeyRelease(uint32 keyId) = 0;
	virtual void SetMouseCoords(float x, float y) = 0;
	virtual void UpdateInput() =0;

	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	static GenericWindow* create(const WindowProps& props = WindowProps());
	void* windowHandle;
	void* context;
	
private:
};

class PlatformWindow {
	using EventCallbackFn = std::function<void(SOMA_ENGINE::Event&)>;

};