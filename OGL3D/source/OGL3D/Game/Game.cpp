#include <OGL3D/Game/Game.h>
#include <OGL3D/Math/Vec4.h>
#include <OGL3D/Window/GWindow.h>
#include <OGL3D/Graphics/GraphicsEngine.h>
#include <windows.h>

Game::Game()
{
	m_graphicsEngine = std::make_unique<GraphicsEngine>();
	m_display = std::make_unique<GWindow>();

	m_display->makeCurrentContext();

	m_graphicsEngine->setViewport(m_display->getInnerSize());
}

Game::~Game()
{
}

void Game::onCreate()
{
	//m_graphicsEngine->clear(Vec4(1.0f, 0.0f, 0.0f, 1.0f));

	//m_display->present(false);
	const float triangleVertices[] = {
		 -0.5f,  -0.5f, 0.0f,
		 0.5f,  -0.5f, 0.0f,
		  0.0f,   0.5f, 0.0f
	};

	m_triangleVAO = m_graphicsEngine->createVertexArrayObject({(void*)triangleVertices, sizeof(float) * 3, 3});
}

void Game::onUpdate()
{
	m_graphicsEngine->clear(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	m_graphicsEngine->setVertexArrayObject(m_triangleVAO);

	m_graphicsEngine->drawTriangles(3, 0);
	
	m_display->present(true);
}

void Game::onQuit()
{
}

void Game::Run()
{
	onCreate();
	MSG msg;

	while(m_isRunning)
	{
		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				m_isRunning = false;
				continue;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		
		onUpdate();
	}

	onQuit();
}

void Game::Quit()
{
	m_isRunning = false;
}
