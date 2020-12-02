#pragma once

#include "xenospch.h"

#include "Core.h"
#include "Xenos/Events/Events.h"

namespace Xenos {

	//Properties for the window
	struct WindowProperties
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		//Default settings for the window
		WindowProperties(
			const std::string& title = "Xenos",
			uint32_t width = 1280,
			uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	// Pure virtual class. Members will be defined in children.
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& props = WindowProperties());
	};

}
