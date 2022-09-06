#pragma once


#include "KaluoEngine/Core/Input.h"

namespace KaluoEngine {

	class WindowsInput : public Input
	{
	protected:
		//implement key input per interface. in here we are windows
		virtual bool IsKeyPressedImpl(int KeyCode) override;
		virtual bool IsMouseButtonPressedImpl(int Button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}