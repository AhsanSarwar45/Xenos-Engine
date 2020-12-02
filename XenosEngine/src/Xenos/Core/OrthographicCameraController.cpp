#include "xenospch.h"
#include "OrthographicCameraController.h"
#include "Xenos/Input/Input.h"
#include "Xenos/Input/KeyCodes.h"

namespace Xenos
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }), m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top), m_Rotation(rotation)
	{

	}
	void OrthographicCameraController::OnUpdate(TimeStep timeStep)
	{
		XS_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(Key::A)) m_CameraPosition.x -= m_CameraTranslationSpeed * timeStep;
		else if (Input::IsKeyPressed(Key::D)) m_CameraPosition.x += m_CameraTranslationSpeed * timeStep;
		if (Input::IsKeyPressed(Key::W)) m_CameraPosition.y += m_CameraTranslationSpeed * timeStep;
		else if (Input::IsKeyPressed(Key::S)) m_CameraPosition.y -= m_CameraTranslationSpeed * timeStep;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(Key::Q)) m_CameraRotation += m_CameraRotationSpeed * timeStep;
			if (Input::IsKeyPressed(Key::A)) m_CameraRotation -= m_CameraRotationSpeed * timeStep;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}
	void OrthographicCameraController::OnEvent(Event& event)
	{
		XS_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(XS_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(XS_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}
	void OrthographicCameraController::OnResize(float width, float height)
	{
		XS_PROFILE_FUNCTION();
		m_AspectRatio = width / height;
		CalculateView();
	}
	void OrthographicCameraController::CalculateView()
	{
		XS_PROFILE_FUNCTION();

		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		XS_PROFILE_FUNCTION();

		//m_ZoomSpeed = m_ZoomLevel * m_ZoomLevel;
		//m_ZoomSpeed= std::min(m_ZoomSpeed, 1.25f);
		m_ZoomLevel -= event.GetYOffset() * 0.5f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		CalculateView();
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
	{
		XS_PROFILE_FUNCTION();
		OnResize((float)event.GetWidth(), (float) event.GetHeight());
		return false;
	}
}