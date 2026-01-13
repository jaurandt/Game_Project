#pragma once
#include <OGL3D/Prerequisites.h>
#include <OGL3D/Math/Vec4.h>

class Mat4
{
public:
	Mat4()
	{
		setIdentity();
	}

	void setIdentity()
	{
		::memset(m_values, 0, sizeof(float) * 16);
		for (int i = 0; i < 4; ++i)
		{
			m_values[i][i] = 1.0f;
		}
	}

	void setScale(const Vec4& scale)
	{
		m_values[0][0] = scale.x;
		m_values[1][1] = scale.y;
		m_values[2][2] = scale.z;
	}

	~Mat4()
	{

	}

private:
	float m_values[4][4] = {};
};