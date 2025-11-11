#pragma once
#include <OGL3D/Graphics/VertexArrayObject.h>
#include <memory>

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

	VertexArrayObjectPtr m_triangleVAO;
};
