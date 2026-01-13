#pragma once

#include <OGL3D/Math/Rect.h>

class GWindow
{
public:
	GWindow();
	~GWindow();

	Rect getInnerSize();

	void makeCurrentContext();
	void present(bool vsync);

private:
	void* m_handle = nullptr;
	void* m_deviceContext = nullptr;
};

