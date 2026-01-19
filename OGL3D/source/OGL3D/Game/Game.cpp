#include <OGL3D/Game/Game.h>
#include <OGL3D/Math/Vec4.h>
#include <OGL3D/Window/GWindow.h>
#include <OGL3D/Graphics/GraphicsEngine.h>
#include <OGL3D/Graphics/ShaderProgram.h>
#include <OGL3D/Graphics/UniformBuffer.h>
#include <OGL3D/Math/Mat4.h>
#include <windows.h>

struct UniformData
{
	Mat4 world;
	Mat4 view;
	Mat4 projection;
	//float scale;
	/*
	Mat4 model;
	Mat4 view;
	Mat4 projection;
	*/
};

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
	/*
	const float triangleVertices[] = {
		 -0.5f,  -0.5f,  0.0f,
		  1.0f,   0.0f,  0.0f,

		  0.5f,  -0.5f,  0.0f,
		  0.0f,   1.0f,  0.0f,

		  0.0f,   0.5f,  0.0f,
		  0.0f,   0.0f,  1.0f
	};
	*/

	const float polygonVertices[] = {
		 -0.5f,  -0.5f,  0.0f,
		  1.0f,   0.0f,  0.0f,
		  
		 -0.5f,   0.5f,  0.0f,
		  0.0f,   1.0f,  0.0f,
		  
		  0.5f,  -0.5f,  0.0f,
		  0.0f,   0.0f,  1.0f,
		 
		  0.5f,   0.5f,  0.0f,
		  1.0f,   1.0f,  0.0f
	};

	VertexAttribute polyAttributes[] = {
		3, // Position
		3  // Color
	};

	m_polygonVAO = m_graphicsEngine->createVertexArrayObject({
		(void*)polygonVertices, 
		sizeof(float) * (3 + 3) /*3 position elements, 3 color*/,
		4,
		polyAttributes,
		2
	});

	m_uniformBuffer = m_graphicsEngine->createUniformBuffer({
		sizeof(UniformData)
	});

	m_shaderProgram = m_graphicsEngine->createShaderProgram({L"Assets/Shaders/BasicShader.vert", L"Assets/Shaders/BasicShader.frag"});
	//m_graphicsEngine->setShaderProgram(m_shaderProgram);
	m_shaderProgram->setUniformBufferSlot("UniformData", 0);

	auto windowSize = m_display->getInnerSize();
	float aspect = 1.0f;
	if(windowSize.height != 0)
	{
		aspect = static_cast<float>(windowSize.width) / static_cast<float>(windowSize.height);
	}

	float fovRadians = 45.0f * (3.1415927f / 180.0f);
	m_projectionMatrix.setPerspective(fovRadians, aspect, 0.01f, 100.0f);
	
	m_viewMatrix.setLookAt(
		Vec4(2.0f, 0.0f, 3.0f, 1.0f), // Eye
		Vec4(0.0f, 0.0f, 0.0f, 1.0f), // Center
		Vec4(0.0f, 1.0f, 0.0f, 1.0f)  // Up
	);
}

void Game::onUpdate()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto elapsedSeconds = std::chrono::duration<double>();
	if (m_previousTime.time_since_epoch().count())
	{
		elapsedSeconds = currentTime - m_previousTime;
	}
	
	m_previousTime = currentTime;

	auto deltaTime = static_cast<float>(elapsedSeconds.count());

	m_scale += 3.1415927f * deltaTime;
	auto sineScale = abs(sinf(m_scale));
	
	Mat4 worldMatrix, trans;

	trans.setIdentity();
	trans.setScale(Vec4(1.0f, 1.0f, 1.0f, 1.0f)); //sineScale
	worldMatrix *= trans;

	trans.setIdentity();
	trans.setTranslation(Vec4(0.0f, 0.0f, 0.0f, 1.0f));
	worldMatrix *= trans;
	/*
	trans.setIdentity();
	trans.setRotationX(m_scale);
	worldMatrix *= trans;
	*/
	//worldMatrix.setScale(Vec4(sineScale, sineScale, sineScale, 1.0f));
	
	UniformData data = { worldMatrix, m_viewMatrix, m_projectionMatrix};
	m_uniformBuffer->setData(&data);

	m_graphicsEngine->clear(Vec4(0.0f, 0.0f, 0.0f, 0.0f));
	
	m_graphicsEngine->setVertexArrayObject(m_polygonVAO);
	m_graphicsEngine->setUniformBuffer(m_uniformBuffer, 0);
	m_graphicsEngine->setShaderProgram(m_shaderProgram);
	m_graphicsEngine->drawTriangles(TriangleStrip, 4, 0);
	
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
