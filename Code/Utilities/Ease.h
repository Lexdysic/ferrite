
//*****************************************************************************
//
// TEase
//
//*****************************************************************************

template <typename T>
class TEase
{
public:

	inline TEase () :
        m_source(),
        m_target(),
        m_velocity(),
        m_omega(1.0f)
    {

    }

	void SetCurvature (float32 curvature)
	{
		m_omega = 2.0f / curvature;
	}

	void Update (Time::Delta timeDelta)
	{
		const float32 x = m_omega * timeDelta;
		const float32 exp = Inverse(1.0f + x + 0.48f * x * x + 0.235f * x * x * x);
		const auto change = m_source - m_target;
		// float maxChange = maxSpeed * smoothTime;
		// change = clamp(change, -maxChange, maxChange);
		const auto temp = (m_velocity + m_omega * change) * timeDelta;
		m_velocity = (m_velocity - m_omega * temp) * exp;
		m_source = m_target + (change + temp) * exp;
	}

private:

	T m_source;
	T m_target;
	T m_velocity;
	float32 m_omega;
};
