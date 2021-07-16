#pragma once
#include "core/common.hpp"
#include "events/Event.hpp"

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

	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	static GenericWindow* create(const WindowProps& props = WindowProps());
	void* windowHandle;
	void* context;
	
private:
};