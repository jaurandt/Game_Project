#pragma once

#include <OGL3D/Graphics/VertexArrayObject.h>
#include <OGL3D/Math/Mat4.h>
#include <memory>
#include <chrono>

class GraphicsEngine;
class GWindow;

class Game
{
public:
	Game();
	~Game();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onQuit();

	void Run();
	void Quit();

protected:
	bool m_isRunning = true;
	
	std::unique_ptr <GraphicsEngine> m_graphicsEngine;
	std::unique_ptr<GWindow> m_display;

	std::chrono::high_resolution_clock::time_point m_previousTime;
	float m_scale = 0.0f;

	Mat4 m_projectionMatrix;
	Mat4 m_viewMatrix;

	VertexArrayObjectPtr m_polygonVAO;
	UniformBufferPtr m_uniformBuffer;
	ShaderProgramPtr m_shaderProgram;
};
