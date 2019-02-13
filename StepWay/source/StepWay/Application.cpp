#include "StepWayPCH.h"
#include "Application.h"
#include "Events/KeyEvent.h"
#include "Events/WindowEvent.h"
#include "Memory/Memory.h"
#include "Graphics/API/Context.h"

//for test rendering
#include "../../vendor/glad/include/glad/glad.h"


bool StepWay::Application::Init()
{
	m_IsRunning = false;

	m_MemoryManager.Init();

	StepWay::graphics::API::Context::CreateNew(StepWay::graphics::GraphicsAPIType::OPENGL);

	m_MainWindow = Window::Create();

	//main window initialization
	WindowProp prop;
	prop.height = 600;
	prop.width = 1000;
	prop.luX = 100;
	prop.luY = 100;
	prop.title = L"Main App Window";

	if (!m_MainWindow->Init(prop))
	{
		SW_CORE_ERROR("failed to Init Window");
		return false;
	}
	m_MainWindow->SetEventCallback(SW_BIND_METH_1(Application::OnEvent));
	m_MainWindow->MakeContextCurrent();

	m_IsRunning = ImplInit();
	return m_IsRunning;
}


void StepWay::Application::ShutDown()
{
	ImplShutDown();

	m_MainWindow->Destroy();
	//make static method for window deletion
	SW_DELETE m_MainWindow;

	StepWay::graphics::API::Context::ReleaseGlobal();

	m_MemoryManager.Destroy();
	SW_TRACE("Successful App Destruction");
}


void StepWay::Application::Run()
{
	SW_CORE_TRACE("Entering Main Loop");
	while (m_IsRunning)
	{
		//update layers
		for(auto it = m_layers.begin(); it != m_layers.end(); ++it)
		{
			(*it)->OnUpdate();
		}

		//update overlays
		for (auto it = m_overlays.begin(); it != m_overlays.end(); ++it)
		{
			(*it)->OnUpdate();
		}

		//some test rendering here
		glClear(GL_COLOR_BUFFER_BIT);
		GLuint buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_VERTEX_ARRAY, buffer);

		struct vec2
		{
			float x, y;
		};
		vec2 pos[3] =
		{
			-0.5f,-0.5f,
			0.5f,-0.5f,
			0.0f,0.5f,
		};

		glBufferData(GL_VERTEX_ARRAY, sizeof(float) * 2 * 3, pos, GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		

		m_MainWindow->OnUpdate();
	}
}

void StepWay::Application::OnEvent(Event & e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowDestroyEvent>(SW_BIND_METH_1(Application::OnMainWindowClose));

	//Messaging overlays
	for (auto it = m_overlays.end(); it != m_overlays.begin();)
	{
		--it;
		(*it)->OnEvent(e);
	}

	//Messaging layers
	for (auto it = m_layers.end(); it != m_layers.begin();)
	{
		--it;
		(*it)->OnEvent(e);
	}

}

void StepWay::Application::PushLayer(Layer * layer)
{
	SW_CORE_TRACE("(Layer)");
	m_layers.PushLayer(layer);
}

void StepWay::Application::PopLayer(Layer * layer)
{
	m_layers.PopLayer(layer);
}

void StepWay::Application::PushOverLay(Layer * overlay)
{
	SW_CORE_TRACE("(Overlay)");
	m_overlays.PushLayer(overlay);
}

void StepWay::Application::PopOverlay(Layer * overlay)
{
	m_overlays.PopLayer(overlay);
}


StepWay::Application::~Application()
{
}

void StepWay::Application::OnMainWindowClose(WindowDestroyEvent & e)
{
	SW_CORE_INFO("Main window closed");
	m_IsRunning = false;
}
