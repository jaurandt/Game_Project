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

	void setTranslation(const Vec4& translation)
	{
		m_values[3][0] = translation.x;
		m_values[3][1] = translation.y;
		m_values[3][2] = translation.z;
	}

	void setRotationX(float angle)
	{
		float c = cosf(angle);
		float s = sinf(angle);
		m_values[1][1] = c;
		m_values[1][2] = s;
		m_values[2][1] = -s;
		m_values[2][2] = c;
	}

	void operator *=(const Mat4& other)
	{
		Mat4 result;
		for (int row = 0; row < 4; ++row)
		{
			for (int col = 0; col < 4; ++col)
			{
				result.m_values[row][col] = 0.0f;
				for (int k = 0; k < 4; ++k)
				{
					result.m_values[row][col] += m_values[row][k] * other.m_values[k][col];
				}
			}
		}
		::memcpy(m_values, result.m_values, sizeof(float) * 16);
	}

	// <-- 17:12 #6 -->

	~Mat4()
	{

	}

private:
	float m_values[4][4] = {};
};