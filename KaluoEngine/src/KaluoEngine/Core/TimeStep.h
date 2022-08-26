#pragma once

namespace KaluoEngine{

	class TimeStep
	{
	public:
		TimeStep(float time = 0.0f)
			: m_Time(time)
		{

		}

		//cast operator
		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		//Get ms/msec
		float GetMillseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;

	};


}